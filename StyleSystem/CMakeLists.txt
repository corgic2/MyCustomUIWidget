# StyleSystem 项目配置
project(StyleSystem)
# 收集源文件
file(GLOB_RECURSE STYLE_SYSTEM_SOURCES
    "*.h"
    "*.cpp"
)

# 创建共享库
add_library(${PROJECT_NAME} SHARED
    ${STYLE_SYSTEM_SOURCES}
    ${RESOURCE_SOURCES}
)

# 链接Qt库
target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)

# 定义导出宏
target_compile_definitions(${PROJECT_NAME} PRIVATE
    STYLESYSTEM_LIBRARY
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
source_group("StyleSystem" FILES ${STYLE_SYSTEM_SOURCES})
source_group("Generated Files" FILES ${RESOURCE_SOURCES})

