file(GLOB srcs
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QP_database/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QP_Evaluator/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QP_Evaluator/Query/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QP_Evaluator/ClauseEvaluators/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QP_Parser/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SourceProcessor/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/TNode/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/TNode/CFG/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QP_database/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/Entity/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/Relationship/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/Statement/*.cpp"
        )
file(GLOB headers
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QP_database/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QP_Evaluator/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QP_Evaluator/Query/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QP_Evaluator/ClauseEvaluators/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QP_Parser/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SourceProcessor/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/TNode/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/TNode/CFG/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QP_database/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/Entity/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/Relationship/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/Statement/*.h"
        )
add_library(spa ${srcs} ${headers} src/SourceProcessor/SemanticsVerifier.cpp src/SourceProcessor/SemanticsVerifier.h src/SourceProcessor/GraphNode.cpp src/SourceProcessor/GraphNode.h src/SourceProcessor/EntityExtractor.cpp src/SourceProcessor/EntityExtractor.h src/SourceProcessor/DesignExtractor.h)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


