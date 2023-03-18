cmake_minimum_required(VERSION 3.14)
project(PacmanSFML)

set(CMAKE_CXX_STANDARD 17)

if(WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)
SET(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
include(${CMAKE_CURRENT_LIST_DIR}/src/CMakeLists.txt)

set(SOURCE_FILES
        src/main.cpp src/Game.cpp src/Game.h src/ResourceHandler.cpp src/ResourceHandler.h src/FreeFuncs.cpp
        src/ImageLayer.cpp src/LayerGroup.cpp src/Map.cpp src/miniz.c src/miniz.h src/Object.cpp src/ObjectGroup.cpp
        src/ObjectTypes.cpp src/Property.cpp src/TileLayer.cpp src/Tileset.cpp src/detail/pugixml.cpp src/Entity/Entity.cpp src/Entity/Entity.h src/GameObject.cpp src/GameObject.h src/Entity/Direction.h src/Entity/Pacman.cpp src/Entity/Pacman.h src/Entity/EntityState.h src/Entity/Ghost/Ghost.cpp src/Entity/Ghost/Ghost.h src/Entity/Ghost/Blinky.cpp src/Entity/Ghost/Blinky.h src/Entity/Ghost/Pinky.cpp src/Entity/Ghost/Pinky.h src/Collectible/Collectible.cpp src/Collectible/Collectible.h src/GameData.h src/Collectible/CollectibleType.h src/Entity/Ghost/Inky.cpp src/Entity/Ghost/Inky.h src/Entity/Ghost/Clyde.cpp src/Entity/Ghost/Clyde.h src/Gamestate/Gameplay.cpp src/Gamestate/Gameplay.h src/Gamestate/Gamestate.h src/Gamestate/States.h src/Audio/AudioManager.cpp src/Audio/AudioManager.h src/Tiles/Tilemap.cpp src/Tiles/Tilemap.h src/Tiles/Tile.cpp src/Tiles/Tile.h src/Gamestate/Title.cpp src/Gamestate/Title.h src/Gamestate/Gamestate.cpp src/GameObject/Button.cpp src/GameObject/Button.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(PacmanSFML ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

target_link_libraries (PacmanSFML sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data/)