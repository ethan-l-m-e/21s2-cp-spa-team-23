#include "TNode/Node.h"
#include "catch.hpp"
using namespace std;

string Sample_Program = "procedure NestedWithOtherConditions {\n"
                        "    entryPoint = 1;\n"
                        "    while (A < a) {\n"
                        "        mainWhileLoop = a;\n"
                        "        while (A > a) {\n"
                        "            while (A =< a) {\n"
                        "                while (A >= a) {\n"
                        "                    nestWithOnlyWhileLoops = 1;\n"
                        "                }\n"
                        "            }\n"
                        "        }\n"
                        "        if (A != a) then {\n"
                        "            while (A == 1) {\n"
                        "                while ((A == 1) || (B == 1)) {\n"
                        "                    nestedWhileInWhileInIf = 1;\n"
                        "                }\n"
                        "            }\n"
                        "        } else {\n"
                        "            while ((A == 1) && (B == 1)) {\n"
                        "                if ((A != 1) && ((B <= 1) != (C == 1))) then {\n"
                        "                    while () {\n"
                        "                        if (((A != 1) && !(1 < 2)) || !((longVariableName > 123456789) >= !(0 <= var123))) then {\n"
                        "                            nestedAlternateIfAndWhile = 1;\n"
                        "                        } else {\n"
                        "                            X = a%b;\n"
                        "                        }\n"
                        "                    }\n"
                        "                } else {\n"
                        "                    print doNothing;\n"
                        "                }\n"
                        "            }\n"
                        "        }\n"
                        "        endOfMainWhileLoop = 1;\n"
                        "    }\n"
                        "}"

void require(bool b) {
    REQUIRE(b);
}

TEST_CASE("1st Test") {

    cout<< Sample_Program;
    require(1 == 1);
}

