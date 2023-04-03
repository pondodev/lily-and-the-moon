
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

#### compile_commands.json generation ####

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

#### project settings ####

project         (lily-and-the-moon VERSION 0.1 LANGUAGES C)
set_property    (GLOBAL PROPERTY USE_FOLDERS ON)
set             (CMAKE_BUILD_TYPE Debug)
set             (CMAKE_C_STANDARD 17)

add_compile_options(-Wall -Wextra -pedantic)

#### project files ####

file(GLOB_RECURSE PROJECT_SOURCES src/*.c)

set(PROJECT_INCLUDE_DIRS
    ${PROJECT_INCLUDE_DIRS}
    src/)

#### project libraries ####

find_package(SDL2 REQUIRED)
set(PROJECT_LIBRARIES ${PROJECT_LIBRARIES} ${SDL2_LIBRARIES})

#### targets ####

add_executable              (${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories  (${PROJECT_NAME} PUBLIC ${PROJECT_INCLUDE_DIRS})
target_link_libraries       (${PROJECT_NAME} PUBLIC ${PROJECT_LIBRARIES})
target_compile_definitions  (${PROJECT_NAME} PUBLIC ${PROJECT_COMPILE_DEFINITIONS})
target_compile_options      (${PROJECT_NAME} PUBLIC ${PROJECT_COMPILE_OPTIONS})
set_target_properties       (${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C)
add_custom_target           (run COMMAND ${PROJECT_BINARY_DIR}/${PROJECT_NAME})

