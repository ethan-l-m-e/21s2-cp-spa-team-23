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
        src/QP_Parser/QueryParser.cpp
        src/QP_Parser/Tokenizer.cpp
        src/QP_Parser/Validator.cpp
        )
set(headers ${headers}
        src/QP_Parser/QueryParser.h
        src/QP_Parser/Tokenizer.h
        src/QP_Parser/Validator.h
        src/QP_Parser/Exception.h
        src/pql/QueryEvaluator.h
        )
add_library(spa ${srcs} ${headers} src/SourceProcessor/Parser.cpp src/SourceProcessor/Parser.h
        src/SourceProcessor/Identifier.cpp src/SourceProcessor/Identifier.h
        src/SourceProcessor/Extractor.cpp src/SourceProcessor/Extractor.h
        src/StringFormatter.cpp src/StringFormatter.h
        src/SourceProcessor/SourceTokenizer.cpp src/SourceProcessor/SourceTokenizer.h
        )
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


