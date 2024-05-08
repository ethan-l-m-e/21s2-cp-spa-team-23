# Constant destination variable.
OUT_PATH=../Code23/tests/

# Helper function.
function autotest() {
  ../Code23/cmake-build-debug/src/autotester/autotester $1 $2 $3
}

# Run demo.
autotest demo_source.txt demo_queries.txt ${OUT_PATH}demo_out.xml