# DesignerPlugin 项目配置
project(DesignerPlugin)
# 获取Qt插件目录
get_target_property(QT_QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)
execute_process(
    COMMAND ${QT_QMAKE_EXECUTABLE} -query QT_INSTALL_PLUGINS
    OUTPUT_VARIABLE QT_PLUGINS_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# 获取Qt bin目录
execute_process(
    COMMAND ${QT_QMAKE_EXECUTABLE} -query QT_INSTALL_BINS
    OUTPUT_VARIABLE QT_BIN_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# 收集源文件
file(GLOB_RECURSE PLUGIN_SRC 
    "*.cpp"
    "*.h"
)

# 其他文件
set(PLUGIN_OTHER_FILES
    customwidgetplugin.json
)

# 排除生成的文件
list(FILTER PLUGIN_SRC EXCLUDE REGEX "moc_|qrc_|ui_")

# 创建插件库
add_library(${PROJECT_NAME} MODULE
    ${PLUGIN_SRC}
    ${PLUGIN_OTHER_FILES}
)

# 设置输出目录
set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/${PLATFORM_CPU}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/${PLATFORM_CPU}"
)

# 包含目录
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/MyCustomUiWidget
    ${CMAKE_SOURCE_DIR}/MyCustomUiWidget/CommonDefine
    ${CMAKE_SOURCE_DIR}/MyCustomUiWidget/CoreWidget
    ${CMAKE_SOURCE_DIR}/MyCustomUiWidget/UtilsWidget
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

# 链接库
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Designer
    Qt5::UiPlugin
    MyCustomUiWidget
)

# 定义导出宏
target_compile_definitions(${PROJECT_NAME} PRIVATE
    QT_PLUGIN
    CUSTOMWIDGETPLUGIN_LIBRARY
    QT_DEPRECATED_WARNINGS
)

# 为MSVC设置编译选项
if(MSVC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        _UNICODE
        UNICODE
    )
endif()

# VS过滤器
source_group_by_dir(PLUGIN_SRC)

# 复制插件和依赖到Qt Designer插件目录
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    # 复制插件DLL到Qt插件目录
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:${PROJECT_NAME}>
        "${QT_PLUGINS_DIR}/designer/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
    
    # 复制主库DLL到Qt bin目录
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:MyCustomUiWidget>
        "${QT_BIN_DIR}/$<TARGET_FILE_NAME:MyCustomUiWidget>"
)