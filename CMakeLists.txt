cmake_minimum_required(VERSION 3.16)

project(Project3)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)

add_executable(Project3 main.cc ${sources} ${headers})

target_link_libraries(Project3 ${Geant4_LIBRARIES})

configure_file(${PROJECT_SOURCE_DIR}/init_vis.mac
               ${PROJECT_BINARY_DIR}/init_vis.mac
               COPYONLY)
