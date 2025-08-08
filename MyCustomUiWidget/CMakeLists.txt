# MyCustomUiWidget 项目配置
project(MyCustomUiWidget)
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

# 收集资源定义文件
file(GLOB_RECURSE RESOURCE_SRC
    "*.qss"
    "*.qrc"
    "*.ini"
    "*.json"
)

# 为UI文件生成头文件
qt5_wrap_ui(UI_HEADERS ${UI_FILES})
# 创建共享库
add_library(${PROJECT_NAME} SHARED
    ${UI_SRC}
    ${COMMON_SRC}
    ${RESOURCE_SRC}
    ${UI_FILES}
    ${UI_HEADERS}
)

# 设置输出目录
set(PublishDir "${CMAKE_SOURCE_DIR}/x64/$<CONFIG>")

# 包含目录
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/CommonDefine
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/StyleSystem"
)

# 链接Qt库和SDK库
target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    StyleSystem
    "${PublishDir}/SDK.lib"
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
source_group_by_dir(RESOURCE_SRC)
source_group("Generated Files" FILES ${UI_HEADERS})
source_group("Form Files" FILES ${UI_FILES})
source_group("Resources Files" FILES ${RESOURCE_SRC})

