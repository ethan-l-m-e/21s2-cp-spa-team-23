file(GLOB srcs
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/pql/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/pql/query_obj/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/pql/ClauseEvaluators/*.cpp"
        )
file(GLOB headers
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/pql/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/pql/query_obj/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/pql/ClauseEvaluators/*.h"
        )
set(srcs ${srcs}
        src/QP_Parser/PreProcessor.cpp
        src/QP_Parser/Tokenizer.cpp
        src/QP_Parser/Validator.cpp
        )
set(headers ${headers}
        src/QP_Parser/PreProcessor.h
        src/QP_Parser/Tokenizer.h
        src/QP_Parser/Validator.h
        src/pql/QueryEvaluator.h
        )
add_library(spa ${srcs} ${headers} src/Parser.cpp src/Parser.h
        src/Identifier.cpp src/Identifier.h
        src/Extractor.cpp src/Extractor.h
        src/StringFormatter.cpp src/StringFormatter.h
        src/Partition.cpp src/Partition.h
        src/SourceTokenizer.cpp src/SourceTokenizer.h
        )
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


