# CMakeList.txt: my_thread 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#

# 将源代码添加到此项目的可执行文件。
add_executable (my_thread "my_thread.cpp" "my_thread.h")

# target_sources(${PROJECT_NAME} PUBLIC my_thread.cpp)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET my_thread PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
