#include "catch.hpp"
#include "QP_Parser/QueryParser.h"
#include "QP_Parser/Tokenizer.h"
#include "pql/query_obj/Query.h"
#include <string>
#include <iostream>

using namespace qp;

TEST_CASE ("PREPROCESSOR") {
    string firstQuery = "variable v; assign a;\nSelect v";
    QueryParser preProcessor = QueryParser();
    Query query = preProcessor.getQuery(firstQuery);
    cout << query.getSelectedSynonym();
    CHECK(query.getSelectedSynonym() == "v");
}
