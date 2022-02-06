file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
set(srcs ${srcs}
        src/QP_Parser/PreProcessor.cpp
        src/QP_Parser/Tokenizer.cpp)
set(headers ${headers}
        src/QP_Parser/PreProcessor.h
        src/QP_Parser/Tokenizer.h)
add_library(spa ${srcs} ${headers} src/Extractor.cpp src/Extractor.h src/StringFormatter.cpp src/StringFormatter.h src/Partition.cpp src/Partition.h)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


