CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
SET(CMAKE_BUILD_TYPE debug)

SET(CMAKE_CXX_COMPILER clang++)


PROJECT(
    Breakout
    LANGUAGES CXX
)

FILE(GLOB INCLUDE_FILES src/include/*.hpp)
FILE(GLOB SOURCE_FILES src/source/*.cpp)

# message("INCLUDES: ${INCLUDE_FILES}\n SOURCES: ${SOURCE_FILES}")

ADD_EXECUTABLE(
    ${PROJECT_NAME}
    src/main.cpp
    ${INCLUDE_FILES}
    ${SOURCE_FILES}
)

target_compile_options(
    ${PROJECT_NAME}
    PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

TARGET_INCLUDE_DIRECTORIES(
    ${PROJECT_NAME}
    PUBLIC
    src/include/
)

find_package(SDL3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

find_package(box2d CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE box2d::box2d)
