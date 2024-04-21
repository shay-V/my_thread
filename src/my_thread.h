#pragma once
#include <memory>
#include <process.h>
#include <tuple>
#include <type_traits>
#include <windows.h>
namespace my_thread {
    struct thread_state {
        HANDLE _handle;
        uint32_t _id;
    };
    class thread {
    private:
        template <class Tuple, std::size_t... N>
        static std::uint32_t __stdcall run(void *args) noexcept {
            // 请使用智能指针实例化对象，或者包裹裸指针
            // 所有权已经转移到了这里
            std::unique_ptr<Tuple> ptr(reinterpret_cast<Tuple *>(args));
            Tuple &tuple = *ptr.get();
            std::invoke(std::move(std::get<N>(tuple))...);
            return 0;
        }
        // std::make_index_sequence<1 +
        // sizeof...(Args)>{}这个值没办法通过模板传递<param>
        // 因此需要通过函数参数传递(param),对应的函数声明和模板声明也需要加上
        template <class Tuple, std::size_t... N>
        static constexpr auto _invoke(std::index_sequence<N...>) noexcept {
            return &run<Tuple, N...>;
        }

        // 对参数进行type decay,效率高避免复制问题、兼容C
        template <class Fn, class... Args> void start(Fn &&fn, Args &&...args) {
            using _tuple = std::tuple<std::decay_t<Fn>, std::decay_t<Args>...>;
            auto ptr = std::make_unique<_tuple>(std::forward<Fn>(fn),
                                                std::forward<Args>(args)...);

            // +1 : function
            constexpr auto fnc = _invoke<_tuple>(
                std::make_index_sequence<1 + sizeof...(Args)>{});
            _state._handle = reinterpret_cast<void *>(
                ::_beginthreadex(nullptr, 0, fnc, ptr.get(), 0, &_state._id));
            // 通过get将所有权转移给线程函数,手动释放所有权,而不是释放资源
            ptr.release();
            //  TODO
        }

    public:
        // 默认构造函数
        thread() noexcept : _state{} {}

        template <class Fn, class... Args> thread(Fn &&fn, Args &&...args) {
            start(std::forward<Fn>(fn), std::forward<Args>(args)...);
        }

    private:
        thread_state _state;
    };
} // namespace my_thread
