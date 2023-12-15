CMAKE_MINIMUM_REQUIRED(VERSION 3.15)
project(TestRealsense)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(OpenCV REQUIRED)
find_package(realsense2 REQUIRED)

# add_subdirectory(src/Realsense)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC
        ${OpenCV_LIBS}
        realsense2
        )
