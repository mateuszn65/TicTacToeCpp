cmake_minimum_required(VERSION 3.21)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)
# raylib
add_subdirectory(raylib-master)


#list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
#find_package(raylib REQUIRED)
#find_package(raylib QUIET)
#if (NOT raylib_FOUND)
#    include(FetchContent)
#    FetchContent_Declare(
#            raylib
#            GIT_REPOSITORY https://github.com/raysan5/raylib.git
#            GIT_TAG 4.0.0
#    )
#    FetchContent_MakeAvailable(raylib)
#endif()

# make setup
set(SOURCES main.cpp cell.h cell.cpp game.h game.cpp utils.h)
add_executable(${PROJECT_NAME} ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
target_link_libraries(${PROJECT_NAME} raylib)
