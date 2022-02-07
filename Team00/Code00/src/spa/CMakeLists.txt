file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
set(srcs ${srcs}
        src/QP_Parser/PreProcessor.cpp
        src/QP_Parser/Tokenizer.cpp
        src/pql/query_obj/Query.cpp
        src/pql/QueryEvaluator.cpp
        src/pql/evaluator/ClauseEvaluator.cpp
        src/pql/evaluator/SelectClauseEvaluator.cpp
        src/pql/evaluator/FollowsClauseEvaluator.cpp
        )
set(headers ${headers}
        src/QP_Parser/PreProcessor.h
        src/QP_Parser/Tokenizer.h
        src/pql/query_obj/Query.h
        src/pql/QueryEvaluator.h
        src/pql/evaluator/ClauseEvaluator.h
        src/pql/evaluator/SelectClauseEvaluator.h
        src/pql/evaluator/FollowsClauseEvaluator.h

        )
add_library(spa ${srcs} ${headers} src/Parser.cpp src/Parser.h
        src/Identifier.cpp src/Identifier.h
        src/Validator.cpp src/Validator.h
        src/Extractor.cpp src/Extractor.h
        src/StringFormatter.cpp src/StringFormatter.h
        src/Partition.cpp src/Partition.h
        src/SourceTokenizer.cpp src/SourceTokenizer.h
        )
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


