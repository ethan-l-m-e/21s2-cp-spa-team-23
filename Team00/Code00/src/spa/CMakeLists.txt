file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} src/Parser.cpp src/Parser.h src/Identifier.cpp src/Identifier.h src/Validator.cpp src/Validator.h src/RelationshipExtractor.cpp src/RelationshipExtractor.h src/Extractor.cpp src/Extractor.h src/StringFormatter.cpp src/StringFormatter.h src/Partition.cpp src/Partition.h

# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


