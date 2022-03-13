//
// Created by Tianyi Wang on 18/2/22.
//

#include "QP_Evaluator/ClauseEvaluators/ResultTable.h"
#include "catch.hpp"
#include <set>

using namespace std;

TEST_CASE("Add result to empty synonym relations") {
    auto* sr = new ResultTable();
    Result result1 = {
            ResultType::BOOLEAN,
            true,
    };
    sr->mergeResultToTable(result1);
    REQUIRE(sr->isEmpty() == true);
    delete sr;

    sr = new ResultTable();
    Result result2 = {
            ResultType::STRING,
            true,
            "a",
            {"1", "2", "3", "4", "5"}
    };
    sr->mergeResultToTable(result2);
    
    REQUIRE(*(sr->getHeader()) == std::vector<std::string>{"a"});
    REQUIRE(*(sr->getList()) == String2DVector{{"1", "2", "3", "4", "5"}});
    delete sr;

    sr = new ResultTable();
    Result result3 = {
            ResultType::TUPLES,
            true,
            make_tuple("a", "b"),
            {
                make_tuple("1", "x"),
                make_tuple("1", "y"),
                make_tuple("1", "z"),
                make_tuple("2", "x"),
                make_tuple("2", "y")
            }
    };
    sr->mergeResultToTable(result3);

    REQUIRE(*(sr->getHeader()) == std::vector<std::string>{"a", "b"});
    REQUIRE(*(sr->getList()) == String2DVector{{ "1", "1", "1", "2", "2" }, { "x", "y", "z", "x", "y" } });
    delete sr;
}

TEST_CASE("Add result to existing synonym relations") {
    auto* sr = new ResultTable(
            {"x"},
            {{"1", "2", "3", "4"}});
    Result result1 = {
            ResultType::BOOLEAN,
            true,
    };
    sr->mergeResultToTable(result1);

    REQUIRE(*(sr->getHeader()) == std::vector<std::string>{"x"});
    REQUIRE(*(sr->getList()) == String2DVector{{"1", "2", "3", "4"}});
    delete sr;

    sr = new ResultTable(
            {"x"},
            {{"1", "2", "3", "4"}});

    Result result2 = {
            ResultType::STRING,
            true,
            "a",
            {"1", "2"}
    };
    sr->mergeResultToTable(result2);
    
    REQUIRE(*(sr->getHeader()) == std::vector<std::string>{"x", "a"});
    REQUIRE(*(sr->getList()) == String2DVector {
        {"1", "2", "3", "4", "1", "2", "3", "4"},
        {"1", "1", "1", "1", "2", "2", "2", "2"}
        });
    delete sr;

    sr = new ResultTable(
            {"x"},
            {{"1", "2", "3", "4"}});

    Result result3 = {
            ResultType::TUPLES,
            true,
            make_tuple("a", "b"),
            {
                    make_tuple("1", "x"),
                    make_tuple("1", "y"),
                    make_tuple("1", "z"),
                    make_tuple("2", "x"),
                    make_tuple("2", "y")
            }
    };
    sr->mergeResultToTable(result3);

    REQUIRE(*(sr->getHeader()) == std::vector<std::string>{"x", "a", "b"});
    REQUIRE(*(sr->getList()) ==  String2DVector {
    { "1", "2", "3", "4", "1", "2", "3", "4", "1", "2", "3", "4", "1", "2", "3", "4", "1", "2", "3", "4" },
    { "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "2", "2", "2", "2", "2", "2", "2", "2" },
    { "x", "x", "x", "x", "y", "y", "y", "y", "z", "z", "z", "z", "x", "x", "x", "x", "y", "y", "y", "y" }});
    delete sr;
}

TEST_CASE("Add result to existing synonym relations, join required") {

    // merge string into sr
    auto* sr = new ResultTable({"a", "c"},{{"1", "2", "3", "4"},{"w", "w", "w", "r"}});

    Result result1 = {
            ResultType::STRING,
            true,
            "a",
            {"1", "2"}
    };
    sr->mergeResultToTable(result1);

    REQUIRE(*(sr->getHeader()) == std::vector<std::string>{"a", "c"});
    REQUIRE(*(sr->getList()) == String2DVector {{"1", "2"},{"w", "w"}});
    delete sr;

    // merge tuple into sr, one common s
    sr = new ResultTable({"a", "c"},{{"1", "1", "2", "3", "4"},{"w", "r", "w", "w", "r"}});

    Result result3 = {
            ResultType::TUPLES,
            true,
            make_tuple("a", "b"),
            {
                    make_tuple("1", "x"),
                    make_tuple("1", "y"),
                    make_tuple("1", "z"),
                    make_tuple("2", "x"),
                    make_tuple("2", "y")
            }
    };
    sr->mergeResultToTable(result3);

    REQUIRE(*(sr->getHeader()) == std::vector<std::string>{"a", "c", "b"});
    REQUIRE(*(sr->getList()) ==  String2DVector {
            {"1", "1", "1", "1", "1", "1", "2", "2"},
            {"w", "w", "w", "r", "r", "r", "w", "w"},
            {"x", "y", "z", "x", "y", "z", "x", "y"}
        });
    delete sr;

    // merge tuple into sr, two common s
    sr = new ResultTable({"a", "c"},{
        {"1", "1", "2", "3", "4"},
        {"w", "r", "w", "w", "r"}}
        );

    Result result4 = {
            ResultType::TUPLES,
            true,
            make_tuple("a", "c"),
            {
                    make_tuple("1", "x"),
                    make_tuple("1", "y"),
                    make_tuple("1", "z"),
                    make_tuple("2", "w"),
                    make_tuple("2", "r")
            }
    };
    sr->mergeResultToTable(result4);

    REQUIRE(*(sr->getHeader()) == std::vector<std::string>{"a", "c"});
    REQUIRE(*(sr->getList()) ==  String2DVector {{"2"},{"w"}});
    delete sr;
}


TEST_CASE("Multi-steps") {
    // merge string into sr
    auto* sr = new ResultTable();

    Result result1 = {
            ResultType::STRING,
            true,
            "s3",
            {"6", "5", "7"}
    };
    sr->mergeResultToTable(result1);

    Result result2 = {
            ResultType::TUPLES,
            true,
            make_tuple("s3", "v1"),
            {
                    make_tuple("5", "y"),
                    make_tuple("5", "z"),
                    make_tuple("7", "x"),
                    make_tuple("8", "y"),
                    make_tuple("2", "y")
            }
    };
    sr->mergeResultToTable(result2);

    Result result3 = {
            ResultType::TUPLES,
            true,
            make_tuple("s2", "v1"),
            {
                    make_tuple("11", "y"),
                    make_tuple("20", "x"),
                    make_tuple("4", "x"),
                    make_tuple("20", "y"),
                    make_tuple("11", "z"),
                    make_tuple("10", "z")
            }
    };
    sr->mergeResultToTable(result3);

    Result result4 = {
            ResultType::TUPLES,
            true,
            make_tuple("s3", "s1"),
            {
                    make_tuple("5", "6"),
                    make_tuple("5", "8"),
                    make_tuple("2", "7"),
                    make_tuple("2", "3"),
                    make_tuple("7", "6"),
            }
    };
    sr->mergeResultToTable(result4);

    Result result5 = {
            ResultType::TUPLES,
            true,
            make_tuple("s1", "s2"),
            {
                    make_tuple("6", "20"),
                    make_tuple("3", "4"),
                    make_tuple("10", "15"),
                    make_tuple("8", "11"),
            }
    };
    sr->mergeResultToTable(result5);

    REQUIRE(*(sr->getHeader()) == std::vector<std::string>{"s3", "v1", "s2", "s1"});
    REQUIRE(*(sr->getList()) ==  String2DVector {
            { "5", "5", "5", "7" }, { "y", "y", "z", "x" }, { "11", "20", "11", "20" }, { "8", "6", "8", "6" }
    });
    delete sr;

}