# 指定CMake的最低版本
cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(TestWidget)

# 设置目标名称
set(TARGET_NAME TestWidget)

# 设置生成文件的输出目录
set(CMAKE_AUTOMOC_OUTPUT_DIR "${CMAKE_BINARY_DIR}/moc")

# 设置输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${PLATFORM_CPU})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${PLATFORM_CPU})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${PLATFORM_CPU})
# 设置GUI项目
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
# 所有源文件
file(GLOB_RECURSE SRC_FILE "*.cpp" "*.cxx" "*.cc" "*.C" "*.c++" "*.h" "*.hpp" "*.H" "*.hxx" "*.ui" "*.qrc" "*.ts")

# 排除生成的moc、qrc和ui文件
foreach(file ${SRC_FILE})
    list(APPEND TARGET_SRC ${file})
endforeach(file ${SRC_FILE})
list(FILTER TARGET_SRC EXCLUDE REGEX "moc_|qrc_|ui_")
list(FILTER TARGET_SRC EXCLUDE REGEX "build/.*")
# 添加VS过滤器
source_group_by_dir(TARGET_SRC)

add_executable(${TARGET_NAME} ${TARGET_SRC})

# 链接主目录
target_link_libraries(${TARGET_NAME} PRIVATE MuCustomUiWidget)
