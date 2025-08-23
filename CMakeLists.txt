cmake_minimum_required(VERSION 3.10)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

# SFML config BEFORE fetching
set(SFML_BUILD_GRAPHICS ON)
set(SFML_BUILD_WINDOW ON)
set(SFML_BUILD_SYSTEM ON)
set(SFML_BUILD_AUDIO OFF)
set(SFML_BUILD_NETWORK OFF)
set(BUILD_SHARED_LIBS OFF)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.5.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main
    src/main.cpp
    src/Core.cpp
    src/SfmlWindow.cpp
    src/Map.cpp
    src/AEntity.cpp
    src/Warrior.cpp
    src/Pawn.cpp
    src/Archer.cpp
    src/Torch.cpp
    src/TNT.cpp
    src/Utils.cpp
    src/Collisions.cpp
    src/Menu.cpp
)

target_compile_features(main PRIVATE cxx_std_20)
target_link_libraries(main PRIVATE sfml-graphics sfml-window sfml-system)

set_target_properties(main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_SOURCE_DIR}
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_SOURCE_DIR}
)