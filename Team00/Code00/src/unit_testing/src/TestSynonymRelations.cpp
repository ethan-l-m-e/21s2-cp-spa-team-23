//
// Created by Tianyi Wang on 18/2/22.
//

#include "pql/ClauseEvaluators/SynonymRelations.h"
#include "catch.hpp"
#include <set>

using namespace std;
using ValueSet = std::set<std::vector<std::string>>;

ValueSet generateValueSet(std::vector<std::vector<std::string>> values) {
    return {std::begin(values),std::end(values)};
}

TEST_CASE("Add result to empty synonym relations") {
    auto* sr = new SynonymRelations();
    Result result1 = {
            ResultType::BOOLEAN,
            true,
    };
    sr->mergeResultToSynonymsRelations(result1);
    REQUIRE(sr->isEmpty() == true);
    delete sr;

    sr = new SynonymRelations();
    Result result2 = {
            ResultType::STRING,
            true,
            "a",
            {"1", "2", "3", "4", "5"}
    };
    sr->mergeResultToSynonymsRelations(result2);
    
    REQUIRE(*(sr->getHeader()) == std::vector<std::string>{"a"});
    REQUIRE(generateValueSet(*(sr->getList())) == ValueSet{{"1"}, {"2"}, {"3"}, {"4"}, {"5"}});
    delete sr;

    sr = new SynonymRelations();
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
    sr->mergeResultToSynonymsRelations(result3);

    REQUIRE(*(sr->getHeader()) == std::vector<std::string>{"a", "b"});
    REQUIRE(generateValueSet(*(sr->getList())) ==  ValueSet {
        {"1", "x"},{"1", "y"},{"1", "z"},{"2", "x"},{"2", "y"}});
    delete sr;
}

TEST_CASE("Add result to existing synonym relations") {
    auto* sr = new SynonymRelations(
            {"x"},
            {{"1"}, {"2"}, {"3"}, {"4"}});
    Result result1 = {
            ResultType::BOOLEAN,
            true,
    };
    sr->mergeResultToSynonymsRelations(result1);

    REQUIRE(*(sr->getHeader()) == std::vector<std::string>{"x"});
    REQUIRE(generateValueSet(*(sr->getList())) == ValueSet{{"1"}, {"2"}, {"3"}, {"4"}});
    delete sr;

    sr = new SynonymRelations(
            {"x"},
            {{"1"}, {"2"}, {"3"}, {"4"}});

    Result result2 = {
            ResultType::STRING,
            true,
            "a",
            {"1", "2"}
    };
    sr->mergeResultToSynonymsRelations(result2);
    
    REQUIRE(*(sr->getHeader()) == std::vector<std::string>{"x", "a"});
    REQUIRE(generateValueSet(*(sr->getList())) == ValueSet {
        {"1", "1"}, {"2", "1"}, {"3", "1"}, {"4", "1"},
        {"1", "2"}, {"2", "2"}, {"3", "2"}, {"4", "2"},
        });
    delete sr;

    sr = new SynonymRelations(
            {"x"},
            {{"1"}, {"2"}, {"3"}, {"4"}});

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
    sr->mergeResultToSynonymsRelations(result3);

    REQUIRE(*(sr->getHeader()) == std::vector<std::string>{"x", "a", "b"});
    REQUIRE(generateValueSet(*(sr->getList())) ==  ValueSet {
        {"1", "1", "x"}, {"1", "1", "y"}, {"1", "1", "z"},
        {"2", "1", "x"}, {"2", "1", "y"}, {"2", "1", "z"},
        {"3", "1", "x"}, {"3", "1", "y"}, {"3", "1", "z"},
        {"4", "1", "x"}, {"4", "1", "y"}, {"4", "1", "z"},
        {"1", "2", "x"}, {"1", "2", "y"}, {"2", "2", "x"},
        {"2", "2", "y"}, {"3", "2", "x"}, {"3", "2", "y"},
        {"4", "2", "x"}, {"4", "2", "y"}});
    delete sr;

}

TEST_CASE("Add result to existing synonym relations, join required") {

    // merge string into sr
    auto* sr = new SynonymRelations(
            {"a", "c"},
            {{"1", "w"}, {"2", "w"}, {"3", "w"}, {"4", "r"}});

    Result result1 = {
            ResultType::STRING,
            true,
            "a",
            {"1", "2"}
    };
    sr->mergeResultToSynonymsRelations(result1);

    REQUIRE(*(sr->getHeader()) == std::vector<std::string>{"a", "c"});
    REQUIRE(generateValueSet(*(sr->getList())) == ValueSet {{"1", "w"}, {"2", "w"}});
    delete sr;

    // merge tuple into sr, one common s
    sr = new SynonymRelations(
            {"a", "c"},
            {{"1", "w"}, {"1", "r"}, {"2", "w"}, {"3", "w"}, {"4", "r"}});

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
    sr->mergeResultToSynonymsRelations(result3);

    REQUIRE(*(sr->getHeader()) == std::vector<std::string>{"a", "c", "b"});
    REQUIRE(generateValueSet(*(sr->getList())) ==  ValueSet {
        {"1", "w", "x"}, {"1", "w", "y"}, {"1", "w", "z"},
        {"1", "r", "x"}, {"1", "r", "y"}, {"1", "r", "z"},
        {"2","w", "x"}, {"2","w", "y"},
        });
    delete sr;

    // merge tuple into sr, two common s
    sr = new SynonymRelations(
            {"a", "c"},
            {{"1", "w"}, {"1", "r"}, {"2", "w"}, {"3", "w"}, {"4", "r"}});

    Result result4 = {
            ResultType::TUPLES,
            true,
            make_tuple("a", "c"),
            {
                    make_tuple("1", "x"),
                    make_tuple("1", "y"),
                    make_tuple("1", "z"),
                    make_tuple("2", "x"),
                    make_tuple("2", "y")
            }
    };
    sr->mergeResultToSynonymsRelations(result4);

    REQUIRE((*(sr->getHeader())).empty());
    REQUIRE((generateValueSet(*(sr->getList()))).empty());
    delete sr;

}


TEST_CASE("Multi-steps") {

    // merge string into sr
    auto* sr = new SynonymRelations();

    Result result1 = {
            ResultType::STRING,
            true,
            "s3",
            {"6", "5", "7"}
    };
    sr->mergeResultToSynonymsRelations(result1);

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
    sr->mergeResultToSynonymsRelations(result2);

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
    sr->mergeResultToSynonymsRelations(result3);

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
    sr->mergeResultToSynonymsRelations(result4);

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
    sr->mergeResultToSynonymsRelations(result5);

    REQUIRE(*(sr->getHeader()) == std::vector<std::string>{"s3", "v1", "s2", "s1"});
    REQUIRE(generateValueSet(*(sr->getList())) ==  ValueSet {
            { "5", "y", "11", "8" }, { "5", "y", "20", "6" }, { "5", "z", "11", "8" }, { "7", "x", "20", "6" }
    });
    delete sr;

}