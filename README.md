# my_thread


## 智能指针
请使用智能指针实例化对象，或者**包裹裸指针**,然后转为引用

## const
如果可以，尽量加上const

## 可调用对象
C++中存在多种可以调用的对象，而不只是函数，因此我们不能只能单纯传入地址，还要支持仿函数、闭包等等

## C风格函数
前面尽量加上::

## index_sequence
	std::make_index_sequence<1 +
	sizeof...(Args)>{}这个值没办法通过模板传递< param >
	因此需要通过函数参数传递(param),对应的函数声明和模板声明也需要加上

ctrl + p打开文件、函数
ctrl + \ + \隐藏一切窗口
ctrl + \ + e错误窗口
ctrl + shift + space 函数参数描述