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

add_executable(MyRPG
    src/main.cpp
    src/core/Core.cpp
    src/core/window/SfmlWindow.cpp
    src/core/Map.cpp
    src/core/Collisions.cpp
    src/entities/AEntity.cpp
    src/entities/Warrior.cpp
    src/entities/Torch.cpp
    src/common/Animation.cpp
    src/common/Clock.cpp
    src/interface/Button.cpp
    src/interface/menu/Menu.cpp
    src/interface/menu/MainMenu.cpp
    src/interface/menu/PauseMenu.cpp
    src/interface/menu/MenuManager.cpp
)

target_include_directories(MyRPG PRIVATE
    src/
    src/core/
    src/core/window/
    src/entities/
    src/common/
    src/interface/
    src/interface/menu/
)

target_compile_features(MyRPG PRIVATE cxx_std_20)
target_link_libraries(MyRPG PRIVATE sfml-graphics sfml-window sfml-system)

set_target_properties(MyRPG PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_SOURCE_DIR}
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_SOURCE_DIR}
)
