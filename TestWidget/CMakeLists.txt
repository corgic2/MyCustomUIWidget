# TestWidget 项目配置
project(TestWidget)
# 收集源文件
file(GLOB_RECURSE TEST_SRC 
    "*.cpp"
    "*.h"
)

# 收集UI文件
file(GLOB_RECURSE TEST_UI
    "*.ui"
)

# 为UI文件生成头文件
qt5_wrap_ui(TEST_UI_HEADERS ${TEST_UI})

# 创建可执行文件
add_executable(${PROJECT_NAME}
    ${TEST_SRC}
    ${TEST_UI}
    ${TEST_UI_HEADERS}
)

# 包含目录
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/MyCustomUiWidget
    ${CMAKE_SOURCE_DIR}/MyCustomUiWidget/CommonDefine
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

# 链接库
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    MyCustomUiWidget
)

# VS过滤器
source_group_by_dir(TEST_SRC)
source_group("Generated Files" FILES ${TEST_UI_HEADERS})
source_group("Form Files" FILES ${TEST_UI})

# 复制依赖DLL到输出目录
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:MyCustomUiWidget>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)