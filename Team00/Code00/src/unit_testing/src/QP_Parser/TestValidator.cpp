#include "catch.hpp"
#include "QP_Parser/Validator.h"


#include <vector>
#include <string>
#include <iostream>

using namespace qp;

TEST_CASE ("VALIDATION") {
    std::string firstQuery = "variable v1; \n assign a; Select v";
    Validator validator = Validator();
    validator.validateQueryStructure(firstQuery);
}
