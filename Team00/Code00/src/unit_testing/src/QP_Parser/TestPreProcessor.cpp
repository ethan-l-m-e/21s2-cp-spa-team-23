#include "catch.hpp"
#include "QP_Parser/PreProcessor.h"
#include "QP_Parser/Tokenizer.h"
#include "pql/query_obj/Query.h"
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

TEST_CASE ("GET ARGUMENT TYPE - SYNONYM") {
    PreProcessor preProcessor = PreProcessor();
   ArgumentType argumentType = preProcessor.getArgumentType("v", "v");
    CHECK(argumentType == ArgumentType::SYNONYM);
}

TEST_CASE ("GET ARGUMENT TYPE - STMT_NO SINGLE DIGIT") {
    PreProcessor preProcessor = PreProcessor();
    ArgumentType argumentType = preProcessor.getArgumentType("1", "v");
    CHECK(argumentType == ArgumentType::STMT_NO);
}

TEST_CASE ("GET ARGUMENT TYPE - STMT_NO DOUBLE DIGIT") {
    PreProcessor preProcessor = PreProcessor();
    ArgumentType argumentType = preProcessor.getArgumentType("10", "v");
    CHECK(argumentType == ArgumentType::STMT_NO);
}

TEST_CASE ("GET ARGUMENT TYPE - STMT_NO IDENT:ONLY LETTERS") {
    PreProcessor preProcessor = PreProcessor();
    ArgumentType argumentType = preProcessor.getArgumentType("Sample", "v");
    CHECK(argumentType == ArgumentType::IDENT);
}
