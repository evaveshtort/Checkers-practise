cmake_minimum_required(VERSION 3.21)
project(Checkers LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)
add_subdirectory(checkers)

add_executable(Checkers main.cpp)
target_link_libraries(Checkers PRIVATE sfml-graphics checkers)
target_compile_features(Checkers PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET Checkers POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:Checkers> $<TARGET_FILE_DIR:Checkers> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS Checkers)