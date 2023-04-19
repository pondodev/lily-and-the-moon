
cmake_minimum_required(VERSION 3.11 FATAL_ERROR) # 3.11+ for FetchContent

#### compile_commands.json generation ####

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

#### project settings ####

project         (lily-and-the-moon VERSION 0.1 LANGUAGES C)
set             (GAME_NAME game)
set_property    (GLOBAL PROPERTY USE_FOLDERS ON)
set             (CMAKE_BUILD_TYPE Debug)
set             (CMAKE_C_STANDARD 17)

add_compile_options(-Wall -Wextra -pedantic)

#### project files ####

file(GLOB_RECURSE PLATFORM_SOURCES src/platform/*.c)
file(GLOB_RECURSE GAME_SOURCES src/game/*.c)

set(PROJECT_INCLUDE_DIRS src/)
set(PLATFORM_INCLUDE_DIRS ${PROJECT_INCLUDE_DIRS} src/platform)
set(GAME_API_HEADER src/game/api/game_interface.h)
set(GAME_PRIVATE_INCLUDE_DIRS ${PROJECT_INCLUDE_DIRS} src/game)

#### project libraries ####

set(RAYLIB_VERSION 4.2.0)
find_package(raylib ${RAYLIB_VERSION} QUIET)
if (NOT raylib_FOUND) # download raylib if not present
  include(FetchContent)
  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # is raylib downloaded yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

set(PROJECT_LIBRARIES ${PROJECT_LIBRARIES} raylib)
if (APPLE)
    set(PROJECT_LIBRARIES ${PROJECT_LIBRARIES}
        "-framework IOKit"
        "-framework Cocoa"
        "-framework OpenGL")
endif()

#### targets ####

# game
add_library                 (${GAME_NAME} SHARED ${GAME_SOURCES})

target_include_directories  (${GAME_NAME} PRIVATE ${GAME_PRIVATE_INCLUDE_DIRS})
target_compile_definitions  (${GAME_NAME} PUBLIC ${PROJECT_COMPILE_DEFINITIONS})
target_compile_options      (${GAME_NAME} PUBLIC ${PROJECT_COMPILE_OPTIONS})
set_target_properties       (${GAME_NAME} PROPERTIES PUBLIC_HEADER ${GAME_API_HEADER})
set_target_properties       (${GAME_NAME} PROPERTIES LINKER_LANGUAGE C)
set_target_properties       (${GAME_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

# platform
add_executable              (${PROJECT_NAME} ${PLATFORM_SOURCES})

target_include_directories  (${PROJECT_NAME} PUBLIC ${PROJECT_INCLUDE_DIRS})
target_link_libraries       (${PROJECT_NAME} PUBLIC ${PROJECT_LIBRARIES})
target_compile_definitions  (${PROJECT_NAME} PUBLIC ${PROJECT_COMPILE_DEFINITIONS})
target_compile_options      (${PROJECT_NAME} PUBLIC ${PROJECT_COMPILE_OPTIONS})
set_target_properties       (${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C)

if (APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        XCODE_GENERATE_SCHEME TRUE
        XCODE_SCHEME_WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
endif()

add_custom_target           (run COMMAND ${PROJECT_BINARY_DIR}/${PROJECT_NAME})
add_custom_command          (TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/res" "${PROJECT_BINARY_DIR}/res")

