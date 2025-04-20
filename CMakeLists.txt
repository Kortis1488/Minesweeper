cmake_minimum_required(VERSION 3.16)
project(Mine)



set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(DSDLIMAGE_VENDORED=OFF)


add_subdirectory(lib/SDL EXCLUDE_FROM_ALL)
add_subdirectory(lib/SDL_image EXCLUDE_FROM_ALL)

file(COPY "${CMAKE_SOURCE_DIR}/assets"
     DESTINATION "${CMAKE_BINARY_DIR}/Debug")

add_executable(Mine 
                    src/main.cpp

                    src/renderLogic/vertexexCreators.cpp 
                    src/renderLogic/coordinateTransformator.cpp
                    src/renderLogic/filler.cpp
                    src/renderLogic/shapeAssembler.cpp
                    src/renderLogic/Image.cpp
                    
                    src/gameLogic/cell.cpp
                    src/gameLogic/field.cpp 
                    )

target_link_libraries(Mine PRIVATE SDL3_image::SDL3_image SDL3::SDL3)