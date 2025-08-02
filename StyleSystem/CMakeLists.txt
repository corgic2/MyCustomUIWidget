# StyleSystem CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

project(StyleSystem)

# 收集源文件
set(STYLE_SYSTEM_SOURCES
    StyleSystemGlobal.h
    SkinManager.h
    SkinManager.cpp
    SkinInfo.h
    SkinInfo.cpp
    SkinResource.h
    SkinResource.cpp
)

# 收集资源文件
set(RESOURCE_FILES
    Resource/default_skin.qrc
    Resource/dark_skin.qrc
)

# 处理资源文件
qt5_add_resources(RESOURCE_SOURCES ${RESOURCE_FILES})

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
source_group("Header Files" FILES ${STYLE_SYSTEM_SOURCES})
source_group("Resource Files" FILES ${RESOURCE_FILES})
source_group("Generated Files" FILES ${RESOURCE_SOURCES})

