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
    SkinSystemUsage.h
    SkinSystemUsage.cpp
)

# 示例和测试文件
set(EXAMPLE_SOURCES
    SkinManagerExample.cpp
    StyleSystemTest.cpp
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

# 创建测试程序
add_executable(StyleSystemTest
    StyleSystemTest.cpp
    ${RESOURCE_SOURCES}
)

# 设置输出目录
set(PublishDir "${CMAKE_SOURCE_DIR}/x64/$<CONFIG>")

# 包含目录
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_include_directories(StyleSystemTest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

# 链接Qt库
target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)

target_link_libraries(StyleSystemTest PRIVATE
    ${PROJECT_NAME}
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
    
    target_compile_definitions(StyleSystemTest PRIVATE
        _UNICODE
        UNICODE
    )
endif()

# VS过滤器
source_group("Header Files" FILES ${STYLE_SYSTEM_SOURCES})
source_group("Example Files" FILES ${EXAMPLE_SOURCES})
source_group("Resource Files" FILES ${RESOURCE_FILES})
source_group("Generated Files" FILES ${RESOURCE_SOURCES}) 