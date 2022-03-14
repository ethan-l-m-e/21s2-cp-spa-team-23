file(GLOB srcs
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QP_Evaluator/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QP_Parser/*.cpp"
        )
file(GLOB headers
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QP_Evaluator/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QP_Parser/*.h"
        )

add_executable(unit_testing ${srcs} ${headers})

target_link_libraries(unit_testing spa)

