#include "catch.hpp"
#include "QP_Parser/PreProcessor.h"
#include "QP_Parser/Tokenizer.h"
#include "pql/query_obj/Query.h"
#include <vector>
#include <string>
#include <iostream>

using namespace qp;

TEST_CASE ("PREPROCESSOR") {
    std::string firstQuery = "variable v; assign a;\nSelect v";
    PreProcessor preProcessor = PreProcessor();
    Query query = preProcessor.getQuery(firstQuery);
    cout << query.getSelectedSynonym();
    CHECK(query.getSelectedSynonym() == "v");
}
