# 指定CMake的最低版本
cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(MuCustomUiWidget)

# 收集源文件
file(GLOB_RECURSE UI_SRC 
    "CoreWidget/*.cpp"
    "CoreWidget/*.h"
    "UtilsWidget/*.cpp"
    "UtilsWidget/*.h"
    "DomainWidget/*.cpp"
    "DomainWidget/*.h"
)

# 收集UI文件
file(GLOB_RECURSE UI_FILES
    "CoreWidget/*.ui"
    "UtilsWidget/*.ui"
    "DomainWidget/*.ui"
)

# 收集通用定义文件
file(GLOB_RECURSE COMMON_SRC
    "CommonDefine/*.cpp"
    "CommonDefine/*.h"
)

# 为UI文件生成头文件
qt5_wrap_ui(UI_HEADERS ${UI_FILES})

# 创建共享库
add_library(${PROJECT_NAME} SHARED
    ${UI_SRC}
    ${COMMON_SRC}
    ${UI_FILES}
    ${UI_HEADERS}
)

# 包含目录
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/CommonDefine
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

# 链接Qt库
target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)

# 定义导出宏
target_compile_definitions(${PROJECT_NAME} PRIVATE
    CUSTOMUIGLOBAL_LIBRARY
    QT_DEPRECATED_WARNINGS
)

# 为MSVC设置导出宏
if(MSVC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        _WINDLL
        _UNICODE
        UNICODE
    )
endif()

# VS过滤器
source_group_by_dir(UI_SRC)
source_group_by_dir(COMMON_SRC)
source_group("Generated Files" FILES ${UI_HEADERS})
source_group("Form Files" FILES ${UI_FILES})

