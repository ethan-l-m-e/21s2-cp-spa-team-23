file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_executable(unit_testing ${srcs} src/TestIdentifier.cpp src/TestIdentifier.cpp src/TestRelationshipExtractor.cpp src/TestSourceTokenizer.cpp src/TestTNode.cpp src/TestParser.cpp)

target_link_libraries(unit_testing spa)

