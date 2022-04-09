function autotest() {
  ../Code23/cmake-build-debug-/src/autotester/autotester $1 $2 $3
}
OUT_PATH=../Code23/tests/
autotest affects_source.txt affects_queries.txt ${OUT_PATH}affects_out.xml
autotest attributes_source.txt attributes_queries.txt ${OUT_PATH}attributes_out.xml
autotest boolean_source.txt boolean_queries.txt ${OUT_PATH}boolean_out.xml
autotest follows_source.txt follows_queries.txt ${OUT_PATH}follows_out.xml
autotest main_source.txt main_queries.txt ${OUT_PATH}main_out.xml
autotest modifies_source.txt modifies_queries.txt ${OUT_PATH}modifies_out.xml
autotest multiclause_source.txt multiclause_queries.txt ${OUT_PATH}multiclause_out.xml
autotest nested_source.txt nested_queries.txt ${OUT_PATH}nested_out.xml
autotest next_source.txt next_queries.txt ${OUT_PATH}next_out.xml
autotest parent_source.txt parent_queries.txt ${OUT_PATH}parent_out.xml
autotest pattern_source.txt pattern_queries.txt ${OUT_PATH}pattern_out.xml
autotest patternifwhile_source.txt patternifwhile_queries.txt ${OUT_PATH}patternifwhile_out.xml
autotest procedures_source.txt procedures_queries.txt ${OUT_PATH}procedures_out.xml
autotest select_source.txt select_queries.txt ${OUT_PATH}select_out.xml
autotest test_source.txt test_queries.txt ${OUT_PATH}test_out.xml
autotest tuples_source.txt tuples_queries.txt ${OUT_PATH}tuples_out.xml
autotest uses_source.txt uses_queries.txt ${OUT_PATH}uses_out.xml

##Notes
#original command example:
#../Code23/cmake-build-debug/src/autotester/autotester uses_source.txt uses_queries.txt ../Code23/tests/uses_out.xml
#OUT_PATH must have no spaces before and after = sign
