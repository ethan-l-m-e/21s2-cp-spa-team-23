file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} src/pql/QueryPreprocessor.cpp src/pql/QueryPreprocessor.h src/pql/query_obj/Query.cpp src/pql/query_obj/Query.h src/pql/QueryEvaluator.cpp src/pql/QueryEvaluator.h src/pql/query_obj/Result.cpp src/pql/evaluator/Result.h src/pql/evaluator/ClauseEvaluator.cpp src/pql/evaluator/ClauseEvaluator.h src/pql/evaluator/PatternClauseEvaluator.h src/pql/evaluator/SuchThatClauseEvaluator.h src/pql/query_obj/Argument.h src/pql/evaluator/SuchThatClauseEvaluator.cpp src/pql/evaluator/Utility.cpp src/pql/evaluator/Utility.h)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


