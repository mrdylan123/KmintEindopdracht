# Author: Jeroen de Haas <jah.dehaas@avans.nl>
cmake_minimum_required(VERSION 3.1.3)
project(pigisland)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
    add_compile_options(/W3)
else()
    add_compile_options(-Wall -Wpedantic)#  -Werror)
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
endif()

  
add_executable(pigisland
  src/kmint/pigisland/main.cpp
  src/kmint/pigisland/node_algorithm.cpp
  src/kmint/pigisland/rectangle.cpp
  src/kmint/pigisland/resources.cpp
  src/kmint/pigisland/shark.cpp
  src/kmint/pigisland/boat.cpp
  src/kmint/pigisland/pig.cpp
  src/kmint/pigisland/distance.cpp
  src/kmint/pigisland/fsm/state.cpp
  src/kmint/pigisland/fsm/sharkState.cpp
  src/kmint/pigisland/fsm/sharkWanderState.cpp
  src/kmint/pigisland/fsm/sharkRestState.cpp
  src/kmint/pigisland/fsm/sharkPursuitState.cpp
  src/kmint/pigisland/fsm/sharkScaredState.cpp
  src/kmint/pigisland/fsm/boatState.cpp
  src/kmint/pigisland/fsm/boatWanderState.cpp
  src/kmint/pigisland/fsm/boatRepairState.cpp
  src/kmint/pigisland/genetics.cpp
  src/kmint/pigisland/geneticAlgorithm.cpp)

target_compile_features(pigisland PUBLIC cxx_std_17)
target_link_libraries(pigisland PRIVATE kmint)
target_include_directories(pigisland PRIVATE 
  src
  include)

add_custom_target(pigisland-resources ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/resources" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources")
