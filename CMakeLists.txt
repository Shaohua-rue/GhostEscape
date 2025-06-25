cmake_minimum_required(VERSION 3.10.0)
project(GHOSTESCAPE)


#指定使用C++17 编译器
set(CMAKE_CXX_STANDARD 17) 
#若编译器不支持C++17，则构建失败
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
# 构建类型设为 Debug，生成带调试信息的可执行文件

set(CMAKE_BUILD_TYPE Debug)
#设置编译输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

#设置目标名称
set(TARGET GHOSTESCAPE)

#添加包含头文件
include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(${TARGET}
    src/main.cpp
    src/Game.cpp
)

target_link_directories(${TARGET} PUBLIC
    ${PROJECT_SOURCE_DIR}/lib/glm
    ${PROJECT_SOURCE_DIR}/lib/spdlog
    ${PROJECT_SOURCE_DIR}/lib/SDL3
    ${PROJECT_SOURCE_DIR}/lib/SDL3_image
    ${PROJECT_SOURCE_DIR}/lib/SDL3_mixer
    ${PROJECT_SOURCE_DIR}/lib/SDL3_ttf
)

target_link_libraries(${TARGET} PUBLIC
                          glm
                          spdlog
                          SDL3
                          SDL3_ttf
                          SDL3_image
                          SDL3_mixer
)
