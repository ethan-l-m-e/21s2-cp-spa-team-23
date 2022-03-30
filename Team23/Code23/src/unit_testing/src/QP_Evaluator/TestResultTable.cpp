//
// Created by Tianyi Wang on 18/2/22.
//

#include "QP_Evaluator/ClauseEvaluators/ResultTable.h"
#include "catch.hpp"
#include <unordered_set>

using std::make_pair;

TEST_CASE("Add result to empty synonym relations") {
    auto* rt = new ResultTable();
    Result result1 = {
            ResultType::BOOLEAN,
            true,
    };
    rt->mergeResultToTable(result1);
    REQUIRE(rt->isEmpty() == true);

    rt->clearTable();
    Result result2 = {
            ResultType::SINGLE,
            true,
            "a",
            std::unordered_set<string>{"1", "2", "3", "4", "5"}
    };
    rt->mergeResultToTable(result2);
    
    REQUIRE(*(rt->getHeader()) == std::vector<std::string>{"a"});
    REQUIRE(*(rt->getList()) == String2DVector{{"1", "2", "3", "4", "5"}});

    rt->clearTable();
    Result result3 = {
            ResultType::PAIR,
            true,
            make_pair("a", "b"),
            std::unordered_set<pair<string, string>> {
                make_pair("1", "x"),
                make_pair("1", "y"),
                make_pair("1", "z"),
                make_pair("2", "x"),
                make_pair("2", "y")
            }
    };
    rt->mergeResultToTable(result3);

    REQUIRE(*(rt->getHeader()) == std::vector<std::string>{"a", "b"});
    REQUIRE(*(rt->getList()) == String2DVector{{ "1", "1", "1", "2", "2" }, { "x", "y", "z", "y", "x" } });
    delete rt;
}

TEST_CASE("Add result to existing synonym relations") {
    auto* rt = new ResultTable();
    rt->setResultTable({"x"},{{"1", "2", "3", "4"}});
    Result result1 = {
            ResultType::BOOLEAN,
            true,
    };
    rt->mergeResultToTable(result1);

    REQUIRE(*(rt->getHeader()) == std::vector<std::string>{"x"});
    REQUIRE(*(rt->getList()) == String2DVector{{"1", "2", "3", "4"}});

    rt->setResultTable({"x"}, {{"1", "2", "3", "4"}});

    Result result2 = {
            ResultType::SINGLE,
            true,
            "a",
            std::unordered_set<string>{"1", "2"}
    };
    rt->mergeResultToTable(result2);
    
    REQUIRE(*(rt->getHeader()) == std::vector<std::string>{"x", "a"});
    REQUIRE(*(rt->getList()) == String2DVector {
        {"1", "2", "3", "4", "1", "2", "3", "4"},
        {"1", "1", "1", "1", "2", "2", "2", "2"}
        });

    rt->setResultTable({"x"},{{"1", "2", "3", "4"}});

    Result result3 = {
            ResultType::PAIR,
            true,
            make_pair("a", "b"),
            std::unordered_set<pair<string, string>>{
                    make_pair("1", "x"),
                    make_pair("1", "y"),
                    make_pair("1", "z"),
                    make_pair("2", "x"),
                    make_pair("2", "y")
            }
    };
    rt->mergeResultToTable(result3);

    REQUIRE(*(rt->getHeader()) == std::vector<std::string>{"x", "a", "b"});
    REQUIRE(*(rt->getList()) ==  String2DVector {
    { "1", "2", "3", "4", "1", "2", "3", "4", "1", "2", "3", "4", "1", "2", "3", "4", "1", "2", "3", "4" },
    { "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "2", "2", "2", "2", "2", "2", "2", "2" },
    { "x", "x", "x", "x", "y", "y", "y", "y", "z", "z", "z", "z", "x", "x", "x", "x", "y", "y", "y", "y" }});
    delete rt;
}

TEST_CASE("Add result to existing synonym relations, join required") {

    // merge string into rt
    auto* rt = new ResultTable();
    rt->setResultTable({"a", "c"},{{"1", "2", "3", "4"},{"w", "w", "w", "r"}});

    Result result1 = {
            ResultType::SINGLE,
            true,
            "a",
            std::unordered_set<string>{"1", "2"}
    };
    rt->mergeResultToTable(result1);

    REQUIRE(*(rt->getHeader()) == std::vector<std::string>{"a", "c"});
    REQUIRE(*(rt->getList()) == String2DVector {{"1", "2"},{"w", "w"}});

    // merge tuple into rt, one common s
    rt->setResultTable({"a", "c"},{{"1", "1", "2", "3", "4"},{"w", "r", "w", "w", "r"}});

    Result result3 = {
            ResultType::PAIR,
            true,
            make_pair("a", "b"),
            std::unordered_set<pair<string, string>>{
                    make_pair("1", "x"),
                    make_pair("1", "y"),
                    make_pair("1", "z"),
                    make_pair("2", "x"),
                    make_pair("2", "y")
            }
    };
    rt->mergeResultToTable(result3);

    REQUIRE(*(rt->getHeader()) == std::vector<std::string>{"a", "c", "b"});
    REQUIRE(*(rt->getList()) ==  String2DVector {
            {"1", "1", "1", "1", "1", "1", "2", "2"},
            {"w", "w", "w", "r", "r", "r", "w", "w"},
            {"x", "y", "z", "x", "y", "z", "x", "y"}
        });

    // merge tuple into rt, two common s
    rt->setResultTable({"a", "c"},{
        {"1", "1", "2", "3", "4"},
        {"w", "r", "w", "w", "r"}}
        );

    Result result4 = {
            ResultType::PAIR,
            true,
            make_pair("a", "c"),
            std::unordered_set<pair<string, string>>{
                    make_pair("1", "x"),
                    make_pair("1", "y"),
                    make_pair("1", "z"),
                    make_pair("2", "w"),
                    make_pair("2", "r")
            }
    };
    rt->mergeResultToTable(result4);

    REQUIRE(*(rt->getHeader()) == std::vector<std::string>{"a", "c"});
    REQUIRE(*(rt->getList()) ==  String2DVector {{"2"},{"w"}});
    delete rt;
}

TEST_CASE("Multi-steps") {
    // merge string into rt
    auto* rt = new ResultTable();

    Result result1 = {
            ResultType::SINGLE,
            true,
            "s3",
            std::unordered_set<string>{"6", "5", "7"}
    };
    rt->mergeResultToTable(result1);

    Result result2 = {
            ResultType::PAIR,
            true,
            make_pair("s3", "v1"),
            std::unordered_set<pair<string, string>>{
                    make_pair("5", "y"),
                    make_pair("5", "z"),
                    make_pair("7", "x"),
                    make_pair("8", "y"),
                    make_pair("2", "y")
            }
    };
    rt->mergeResultToTable(result2);

    Result result3 = {
            ResultType::PAIR,
            true,
            make_pair("s2", "v1"),
            std::unordered_set<pair<string, string>>{
                    make_pair("11", "y"),
                    make_pair("20", "x"),
                    make_pair("4", "x"),
                    make_pair("20", "y"),
                    make_pair("11", "z"),
                    make_pair("10", "z")
            }
    };
    rt->mergeResultToTable(result3);

    Result result4 = {
            ResultType::PAIR,
            true,
            make_pair("s3", "s1"),
            std::unordered_set<pair<string, string>>{
                    make_pair("5", "6"),
                    make_pair("5", "8"),
                    make_pair("2", "7"),
                    make_pair("2", "3"),
                    make_pair("7", "6"),
            }
    };
    rt->mergeResultToTable(result4);

    Result result5 = {
            ResultType::PAIR,
            true,
            make_pair("s1", "s2"),
            std::unordered_set<pair<string, string>>{
                    make_pair("6", "20"),
                    make_pair("3", "4"),
                    make_pair("10", "15"),
                    make_pair("8", "11"),
            }
    };
    rt->mergeResultToTable(result5);

    REQUIRE(*(rt->getHeader()) == std::vector<std::string>{"s3", "v1", "s2", "s1"});
    REQUIRE(*(rt->getList()) ==  String2DVector {
            { "5", "5", "5", "7" }, { "y", "y", "z", "x" }, { "11", "20", "11", "20" }, { "8", "6", "8", "6" }
    });
    delete rt;

}