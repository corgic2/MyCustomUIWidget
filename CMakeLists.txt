# 指定CMake的最低版本
cmake_minimum_required(VERSION 3.10)

# 设置解决方案名称
project(MyCustomUIWidgetSolution)

# 设置使用到的Qt模块
set(QT_MODULES Core Gui Widgets Designer UiPlugin)

# 查找Qt库
find_package(Qt5 COMPONENTS ${QT_MODULES} REQUIRED)

# Qt自动生成设置
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC_OUTPUT_DIR "${CMAKE_BINARY_DIR}/moc")

# 启用C++17并设置UTF-8
if(MSVC)
    add_compile_options(/std:c++17 /utf-8 /bigobj /FS)
else()
    add_compile_options(-std=c++17)
endif()

# 检测平台
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(PLATFORM_CPU "x64")
else()
    set(PLATFORM_CPU "x86")
endif()

# 设置输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${PLATFORM_CPU})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${PLATFORM_CPU})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${PLATFORM_CPU})
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")

# VS过滤器宏
macro(source_group_by_dir source_files)
    if(MSVC)
        set(cur_dir ${CMAKE_CURRENT_SOURCE_DIR})
        foreach(file ${${source_files}})
            string(REGEX REPLACE ${cur_dir}/\(.*\) \\1 file_path ${file})
            string(REGEX REPLACE "\(.*\)/.*" \\1 sgbd_group_name ${file_path})
            string(COMPARE EQUAL ${file_path} ${sgbd_group_name} nogroup)
            string(REPLACE "/" "\\" sgbd_group_name ${sgbd_group_name})
            get_filename_component(file_extension ${file} EXT)
            if(file_extension STREQUAL ".ui")
                source_group("Form Files" FILES ${file})
            elseif(file_extension STREQUAL ".qrc")
                source_group("Resource Files" FILES ${file})
            elseif(file_extension STREQUAL ".ts")
                source_group("Language" FILES ${file})
            elseif(NOT nogroup)
                source_group(${sgbd_group_name} FILES ${file})
            endif()
        endforeach(file)
    endif(MSVC)
endmacro(source_group_by_dir)

# 设置Boost库的根目录（应指向 Boost 的安装根目录）
set(BOOST_ROOT "D:/WorkSpace/boost_1_88_0")

# 禁用搜索系统路径
set(Boost_NO_SYSTEM_PATHS ON) # 非常重要，否则会导致找不到 Boost 库

# 查找Boost库，指定需要的组件
set(SDKThirdPartylib "${CMAKE_SOURCE_DIR}/SDKThirdPartylib.txt")
file(STRINGS ${SDKThirdPartylib} LIBRARIES)

# 设置Boost组件
set(BOOST_COMPONENTS ${LIBRARIES})

# 查找Boost库
find_package(Boost REQUIRED COMPONENTS ${BOOST_COMPONENTS})

if(Boost_FOUND)
    # 输出 Boost 的相关信息
    message(STATUS "Boost version: ${Boost_VERSION}")
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
else()
    message(FATAL_ERROR "Boost not found!")
endif()

# 包含各项目的CMake配置
add_subdirectory(StyleSystem)
add_subdirectory(MyCustomUiWidget)
add_subdirectory(DesignerPlugin)