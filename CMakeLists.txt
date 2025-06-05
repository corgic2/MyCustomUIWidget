# 指定CMake的最低版本
cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(MuCustomUiWidgetRoot)

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
    add_compile_options(/std:c++17 /utf-8 /bigobj)
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

# 添加子项目（按依赖顺序）
add_subdirectory(MuCustomUiWidget)
add_subdirectory(DesignerPlugin)
add_subdirectory(TestWidget)