//
// Created by Tianyi Wang on 14/2/22.
//

#include "TestUtilities.h"
#include <utility>
#include "catch.hpp"

using namespace std;

TEST_CASE("Query with no clauses") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarations = {{"v", DesignEntity::VARIABLE},
                                                           {"a", DesignEntity::ASSIGN},
                                                           {"pn", DesignEntity::PRINT},
                                                           {"s", DesignEntity::STMT}
                                                           };
    Query query_1 = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "v"}});
    Query query_2 = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "s"}});
    Query query_3 = makeQuery(declarations, {Argument{ArgumentType::BOOLEAN, ""}});
    Query query_4 = makeQuery(declarations, {Argument{ArgumentType::ATTR_REF, make_pair("pn", AttrName::VAR_NAME)}});

    auto qe = new QueryEvaluator(testPKB);

    /**
     * Select v
     * Type: select variables
     */
    REQUIRE(generateResultSet(qe->evaluate(&query_1)) == ResultSet {"x", "y", "z"});

    /**
     * Select s
     * Type: select statements
     */
    REQUIRE(generateResultSet(qe->evaluate(&query_2)) == ResultSet {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"});

    /**
     * Select BOOLEAN
     */
    REQUIRE(generateResultSet(qe->evaluate(&query_3)) == ResultSet {"TRUE"});

    /**
     * Select pn.varName
     */
    REQUIRE(generateResultSet(qe->evaluate(&query_4)) == ResultSet {"z", "x"});

    delete qe;
    
}

TEST_CASE("Query with false clauses") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarations = {{"a", DesignEntity::ASSIGN}};
    Argument a4 = {ArgumentType::STMT_NO, "4"};
    Argument a5 = {ArgumentType::STMT_NO, "5"};
    Argument a6 = {ArgumentType::STMT_NO, "6"};
    Argument aa = {ArgumentType::SYNONYM, "a"};
    Argument aw = {ArgumentType::IDENT, "w"};
    Argument wild = {ArgumentType::UNDERSCORE, "_"};


    SuchThatClause clause_4_5 = {ArgList{a4, a5},RelRef::FOLLOWS}; //true
    SuchThatClause clause_5_6 = {ArgList{a5, a6},RelRef::FOLLOWS}; //false
    SuchThatClause clause_6_5 = {ArgList{a6, a5},RelRef::NEXT}; //false
    PatternClause clause_a_0_0 = {ArgList{aa, wild, wild}, SynonymType::ASSIGN}; //true
    PatternClause clause_a_0_w = {ArgList{aa, wild, aw}, SynonymType::ASSIGN}; //false


    Query query_1 = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "a"}}, {clause_5_6});
    Query query_2 = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "a"}}, {clause_5_6, clause_4_5});
    Query query_3 = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "a"}}, {clause_6_5, clause_4_5}, {clause_a_0_0});
    Query query_4 = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "a"}}, {clause_4_5, clause_4_5}, {clause_a_0_0, clause_a_0_w});
    Query query_5 = makeQuery(declarations, {Argument{ArgumentType::BOOLEAN, ""}}, {clause_4_5, clause_4_5, clause_6_5}, {clause_a_0_0});


    auto qe = new QueryEvaluator(testPKB);

    /**
     * Type: false such that clause
     */
    REQUIRE(generateResultSet(qe->evaluate(&query_1)).empty());

    /**
     * Type: false such that clause + true such that clause
     */
    REQUIRE(generateResultSet(qe->evaluate(&query_2)).empty());

    /**
     * Type: false such that clause + true such that clause + true pattern clause
     */
    REQUIRE(generateResultSet(qe->evaluate(&query_3)).empty());

    /**
     * Type: true such that clause + true such that clause + true pattern clause + false pattern clause
     */
    REQUIRE(generateResultSet(qe->evaluate(&query_4)).empty());

    /**
     * Type: boolean
     */
    REQUIRE(generateResultSet(qe->evaluate(&query_5)) == ResultSet{"FALSE"});

    delete qe;
    
}

TEST_CASE("Multi clauses") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarations = {
            {"s1", DesignEntity::STMT},
            {"s2", DesignEntity::STMT},
            {"s3", DesignEntity::STMT},
    };

    Argument as1 = {ArgumentType::SYNONYM, "s1"};
    Argument as2 = {ArgumentType::SYNONYM, "s2"};
    Argument as3 = {ArgumentType::SYNONYM, "s3"};
    Argument a0 = {ArgumentType::UNDERSCORE, "_"};
    Argument a4 = {ArgumentType::STMT_NO, "4"};
    Argument a5 = {ArgumentType::STMT_NO, "5"};

    SuchThatClause clause_s1_s2 = {ArgList{as1, as2},RelRef::FOLLOWS};
    SuchThatClause clause_s2_s3 = {ArgList{as2, as3},RelRef::FOLLOWS};
    SuchThatClause clause_s2_5 = {ArgList{as2, a5},RelRef::FOLLOWS};
    SuchThatClause clause_s1_s3 = {ArgList{as1, as3},RelRef::FOLLOWS};
    SuchThatClause clause_s1_0 = {ArgList{as1, a0},RelRef::FOLLOWS};
    SuchThatClause clause_s2_0 = {ArgList{as2, a0},RelRef::FOLLOWS};
    SuchThatClause clause_4_5 = {ArgList{a4, a5},RelRef::FOLLOWS};

    Query query_0 = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "s1"}}, {clause_s1_s2, clause_4_5});
    Query query_1 = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "s1"}}, {clause_s1_s2, clause_s2_5});
    Query query_2 = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "s1"}}, {clause_s1_s3, clause_s2_5});
    Query query_3 = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "s2"}}, {clause_s1_s2, clause_s2_s3});
    Query query_4 = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "s1"}}, {clause_s2_5, clause_s1_s2});
    Query query_5 = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "s1"}}, {clause_s1_0, clause_s2_0, clause_s1_s2});
    Query query_6 = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "s1"}}, {clause_s2_5, clause_s1_s3});
    Query query_7 = makeQuery(declarations, {Argument{ArgumentType::BOOLEAN, ""}}, {clause_s2_5, clause_s1_s3});

    auto qe =  new QueryEvaluator(testPKB);

    /**
     * Select s1 such that Follows(s1, s2) such that Follows(4, 5)
     * Type: boolean clause, no merge needed
     */
    REQUIRE(generateResultSet(qe->evaluate(&query_0)) == ResultSet {"1","2","3","4","5","6","7"});

    /**
     * Select s1 such that Follows(s1, s2) such that Follows(s2, 5)
     * Type: join string, value exists
     */
    REQUIRE(generateResultSet(qe->evaluate(&query_1)) == ResultSet {"3"});

    /**
     * Select s1 such that Follows(s1, s3) such that Follows(s2, 5)
     * Type: join string, value doesn't exist
     */
    REQUIRE(generateResultSet(qe->evaluate(&query_2)) == ResultSet {"1","2","3","4","5","6","7"});

    /**
    * Select s2 such that Follows(s1, s2) such that Follows(s2, s3)
    * Type: join tuples, left value exists
    */
    REQUIRE(generateResultSet(qe->evaluate(&query_3)) == ResultSet {"2","3","4","5","7"});

    /**
     * Select s1 such that Follows(s2, 5) such that Follows(s1, s2)
     * Type: join tuples, right value exists
     */
    REQUIRE(generateResultSet(qe->evaluate(&query_4)) == ResultSet {"3"});

    /**
     * Select s1 such that Follows(s1, _) such that Follows(s2, _) such that Follows(s1, s2)
     * Type: join tuples, both value exist
     */
    REQUIRE(generateResultSet(qe->evaluate(&query_5)) == ResultSet {"1","2","3","4","6"});

    /**
     * Select s1 such that Follows(s2, 5) such that Follows(s1, s3)
     * Type: join tuples, both value don't exist
     */
    REQUIRE(generateResultSet(qe->evaluate(&query_6)) == ResultSet {"1","2","3","4","5","6","7"});

    /**
     * Select BOOLEAN such that Follows(s2, 5) such that Follows(s1, s3)
     * Type: join tuples, boolean
     */
    REQUIRE(generateResultSet(qe->evaluate(&query_7)) == ResultSet {"TRUE"});

    delete qe;
    
}

TEST_CASE("Multi clauses with tuples") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarations = {
            {"s1", DesignEntity::STMT},
            {"s2", DesignEntity::STMT},
            {"s3", DesignEntity::STMT},
    };

    Argument as1 = {ArgumentType::SYNONYM, "s1"};
    Argument as2 = {ArgumentType::SYNONYM, "s2"};
    Argument as3 = {ArgumentType::SYNONYM, "s3"};
    Argument a0 = {ArgumentType::UNDERSCORE, "_"};
    Argument a4 = {ArgumentType::STMT_NO, "4"};
    Argument a5 = {ArgumentType::STMT_NO, "5"};

    SuchThatClause clause_s1_s2 = {ArgList{as1, as2},RelRef::FOLLOWS};
    SuchThatClause clause_s2_s3 = {ArgList{as2, as3},RelRef::FOLLOWS};
    SuchThatClause clause_s2_5 = {ArgList{as2, a5},RelRef::FOLLOWS};
    SuchThatClause clause_s1_s3 = {ArgList{as1, as3},RelRef::FOLLOWS};
    SuchThatClause clause_s1_0 = {ArgList{as1, a0},RelRef::FOLLOWS};
    SuchThatClause clause_s2_0 = {ArgList{as2, a0},RelRef::FOLLOWS};
    SuchThatClause clause_4_5 = {ArgList{a4, a5},RelRef::FOLLOWS};
    SuchThatClause clause_5_s3 = {ArgList{a5, as3},RelRef::PARENT};

    Query query_0 = makeQuery(declarations, {
        Argument{ArgumentType::SYNONYM, "s1"}
        },
                              {clause_s1_s2, clause_4_5});
    Query query_1 = makeQuery(declarations, {
        Argument{ArgumentType::SYNONYM, "s1"},
        Argument{ArgumentType::SYNONYM, "s2"}
        },
                              {clause_s1_s2, clause_4_5});
    Query query_2 = makeQuery(declarations, {
        Argument{ArgumentType::SYNONYM, "s1"},
        Argument{ArgumentType::SYNONYM, "s2"},
        Argument{ArgumentType::SYNONYM, "s3"}
        },
                              {clause_s1_s2, clause_4_5, clause_5_s3});

    auto qe = new QueryEvaluator(testPKB);

    /**
     * Select s1 s2 such that Follows(s1, s2) such that Follows(4, 5)
     * Type: boolean clause, no merge needed
     */
    REQUIRE(generateResultSet(qe->evaluate(&query_1)) == ResultSet {"1 2","2 3","3 4","4 5","5 11","6 7","7 10"});

    /**
     * Select s1 s2 s3 such that Follows(s1, s2) such that Follows(4, 5) such that Parent(5, s3)
     * Type: boolean clause, no merge needed
     */
    REQUIRE(generateResultSet(qe->evaluate(&query_2)) == ResultSet {
            "1 2 6", "2 3 6", "3 4 6", "4 5 6", "5 11 6", "6 7 6", "7 10 6",
            "1 2 7", "2 3 7", "3 4 7", "4 5 7", "5 11 7", "6 7 7", "7 10 7",
            "1 2 10", "2 3 10", "3 4 10", "4 5 10", "5 11 10", "6 7 10", "7 10 10",
    });

    delete qe;
    
}

TEST_CASE("Pattern clause: return stmt") {
    PKB *testPKB = generateSamplePKBForPatternMatching();
    Query query;
    auto qe = new QueryEvaluator(testPKB);
    unordered_map<string, DesignEntity> declarations = {{"a1", DesignEntity::ASSIGN}};
    Argument assignSyn = {ArgumentType::SYNONYM, "a1"};
    Argument leftIdent = {ArgumentType::IDENT, "\"x\""};
    Argument noResultLeft = {ArgumentType::IDENT, "noResult"};
    Argument rightVar = {ArgumentType::PARTIAL_UNDERSCORE, "_\"y\"_"};
    Argument rightConst = {ArgumentType::PARTIAL_UNDERSCORE, "_\"3\"_"};
    Argument noResultsRight = {ArgumentType::PARTIAL_UNDERSCORE, "_\"asdsadsadasdsa\"_"};
    Argument wild = {ArgumentType::UNDERSCORE, "_"};

    // create PatternClause using arguments and synonym
    PatternClause wild_wild = {ArgList {assignSyn, wild, wild}, SynonymType::ASSIGN};
    PatternClause ident_wild = {ArgList {assignSyn, leftIdent, wild}, SynonymType::ASSIGN};
    PatternClause wild_const = {ArgList {assignSyn, wild, rightConst}, SynonymType::ASSIGN};
    PatternClause ident_const = {ArgList {assignSyn, leftIdent, rightConst}, SynonymType::ASSIGN};
    PatternClause wild_var = {ArgList {assignSyn, wild, rightVar}, SynonymType::ASSIGN};
    PatternClause ident_var = {ArgList {assignSyn, leftIdent, rightVar}, SynonymType::ASSIGN};
    PatternClause none_wild = {ArgList {assignSyn, noResultLeft, wild}, SynonymType::ASSIGN};
    PatternClause wild_none = {ArgList {assignSyn, wild, noResultsRight}, SynonymType::ASSIGN};

    query = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "a1"}}, {wild_wild});
    REQUIRE(evaluateAndCreateResultSet(qe, &query) == ResultSet {"1", "2", "3", "4", "5", "6", "7"});

    query = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "a1"}}, {ident_wild});
    REQUIRE(evaluateAndCreateResultSet(qe, &query) == ResultSet {"1", "2", "3", "7"});

    query = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "a1"}}, {none_wild});
    REQUIRE(evaluateAndCreateResultSet(qe, &query).empty());

    query = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "a1"}}, {ident_const});
    REQUIRE(evaluateAndCreateResultSet(qe, &query) == ResultSet {"7"});

    query = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "a1"}}, {wild_const});
    REQUIRE(evaluateAndCreateResultSet(qe, &query) == ResultSet {"5", "7"});

    query = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "a1"}}, {wild_var});
    REQUIRE(evaluateAndCreateResultSet(qe, &query) == ResultSet {"1", "3", "4", "5", "6", "7"});

    query = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "a1"}}, {ident_var});
    REQUIRE(evaluateAndCreateResultSet(qe, &query) == ResultSet {"1", "3", "7"});

    query = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "a1"}}, {wild_none});
    REQUIRE(evaluateAndCreateResultSet(qe, &query).empty());

    //non-standardized spacing
    Argument spacingRightVar = {ArgumentType::PARTIAL_UNDERSCORE, "_\"   y  \"_"};
    PatternClause wild_weirdVar = {ArgList {assignSyn, wild, spacingRightVar}, SynonymType::ASSIGN};
    query = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "a1"}}, {wild_weirdVar});
    REQUIRE(evaluateAndCreateResultSet(qe, &query) == ResultSet {"1", "3", "4", "5", "6", "7"});
    delete qe;
    
}

TEST_CASE("Pattern clause: return var + Stmt") {
    PKB *testPKB = generateSamplePKBForPatternMatching();
    Query query;
    auto qe = new QueryEvaluator(testPKB);
    unordered_map<string, DesignEntity> declarations = {{"a", DesignEntity::ASSIGN}, {"v", DesignEntity::VARIABLE}};
    Argument assignSyn = {ArgumentType::SYNONYM, "a"};
    Argument leftSynonym = {ArgumentType::SYNONYM, "v"};
    Argument rightConst = {ArgumentType::PARTIAL_UNDERSCORE, "_\"2\"_"};
    Argument wild = {ArgumentType::UNDERSCORE, "_"};

    PatternClause synonym_wild = {ArgList {assignSyn, leftSynonym, wild}, SynonymType::ASSIGN};
    PatternClause synonym_var = {ArgList {assignSyn, leftSynonym, rightConst}, SynonymType::ASSIGN};

    query = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "a"}}, {synonym_wild});
    REQUIRE(evaluateAndCreateResultSet(qe, &query) == ResultSet {"1", "2", "3", "4", "5", "6", "7"});

    query = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "a"}}, {synonym_var});
    REQUIRE(evaluateAndCreateResultSet(qe, &query) == ResultSet{"4", "5"});

    query = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "v"}}, {synonym_wild});
    REQUIRE(evaluateAndCreateResultSet(qe, &query) == ResultSet{"x", "y"});

    query = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "v"}}, {synonym_var});
    REQUIRE(evaluateAndCreateResultSet(qe, &query) == ResultSet{"y"});
    delete qe;
    
}

TEST_CASE("Pattern clause: full expression and exact matching") {
    PKB *testPKB = generateSamplePKBForPatternMatching();
    Query query;
    auto qe = new QueryEvaluator(testPKB);
    unordered_map<string, DesignEntity> declarations = {{"a1", DesignEntity::ASSIGN}};
    Argument assignSyn = {ArgumentType::SYNONYM, "a1"};
    Argument leftWild = {ArgumentType::UNDERSCORE, "_"};

    // exact matching simple
    PatternClause clauseIdentEasy = {ArgList {assignSyn, leftWild,
                                          {ArgumentType::IDENT, "\"y + 1\""}},
                                 SynonymType::ASSIGN};
    query = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "a1"}}, {clauseIdentEasy});
    REQUIRE(evaluateAndCreateResultSet(qe, &query) == ResultSet {"3"});

     // exact matching difficult
    PatternClause clauseIdentHard = {ArgList {assignSyn, leftWild,
                                              {ArgumentType::IDENT, "\"((y + (3 - z)) * (x + 2)) + 1\""}},
                                     SynonymType::ASSIGN};
    query = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "a1"}}, {clauseIdentHard});
    REQUIRE(evaluateAndCreateResultSet(qe, &query) == ResultSet {"5"});

    // no exact match
    PatternClause clauseIdentNoResults = {ArgList {assignSyn, leftWild,
                                              {ArgumentType::IDENT, "\"((y + (3 - z)) * (x + 2))\""}},
                                     SynonymType::ASSIGN};
    query = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "a1"}}, {clauseIdentNoResults});
    REQUIRE(evaluateAndCreateResultSet(qe, &query).empty());

    // wild easy match
    PatternClause clauseWildEasy = {ArgList {assignSyn, leftWild,
                                                   {ArgumentType::PARTIAL_UNDERSCORE, "_\"x * 1\"_"}},
                                          SynonymType::ASSIGN};
    query = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "a1"}}, {clauseWildEasy});
    REQUIRE(evaluateAndCreateResultSet(qe, &query) == ResultSet {"6"});

    // wild medium match
    PatternClause clauseWildMedium = {ArgList {assignSyn, leftWild,
                                             {ArgumentType::PARTIAL_UNDERSCORE, "_\"y + x\"_"}},
                                    SynonymType::ASSIGN};
    query = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "a1"}}, {clauseWildMedium});
    REQUIRE(evaluateAndCreateResultSet(qe, &query) == ResultSet {"4"});

    // wild difficult match
    PatternClause clauseWildHard = {ArgList {assignSyn, leftWild,
                                               {ArgumentType::PARTIAL_UNDERSCORE, "_\"y + (3 - z)\"_"}},
                                      SynonymType::ASSIGN};
    query = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "a1"}}, {clauseWildHard});
    REQUIRE(evaluateAndCreateResultSet(qe, &query) == ResultSet {"5" , "7"});


    // valid queries with non standardised spacing
    PatternClause weirdSpacing = {ArgList {assignSyn, leftWild,
                                           {ArgumentType::PARTIAL_UNDERSCORE, "_\"  y  +   x   \"_"}},
                                  SynonymType::ASSIGN};
    query = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "a1"}}, {weirdSpacing});
    REQUIRE(evaluateAndCreateResultSet(qe, &query) == ResultSet {"4"});

    //invalid query: wrong brackets
    //invalid query: wrong var/const
    delete qe;
    

}

TEST_CASE("Merge synonyms 1 such that and 1 pattern") {
    PKB *testPKB = generateSamplePKBForPatternMatching();
    unordered_map<string, DesignEntity> declarations = {{"a", DesignEntity::ASSIGN}, {"v", DesignEntity::VARIABLE}};
    Argument aa = {ArgumentType::SYNONYM, "a"};
    Argument av = {ArgumentType::SYNONYM, "v"};
    Argument rightConst = {ArgumentType::PARTIAL_UNDERSCORE, "_\"2\"_"};
    Argument a5 = {ArgumentType::STMT_NO, "5"};

    SuchThatClause clause_a_5 = {ArgList{aa, a5},RelRef::FOLLOWS};
    SuchThatClause clause_5_v = {ArgList{a5, av},RelRef::USES_S};
    PatternClause synonym_var = {ArgList {aa, av, rightConst}, SynonymType::ASSIGN};


    Query query_1 = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "a"}}, {clause_a_5}, {synonym_var});
    Query query_2 = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "v"}}, {clause_5_v}, {synonym_var});

    auto qe = new QueryEvaluator(testPKB);

    /**
     * Select a such that Follows(a, 5) Pattern a(v, _"2"_)
     * Tuple -> single
     */
    REQUIRE(generateResultSet(qe->evaluate(&query_1)) == ResultSet {"4"});

    /**
     * Select v such that Uses(5, v) Pattern a(v, _"2"_)
     */
    REQUIRE(generateResultSet(qe->evaluate(&query_2)) == ResultSet {"y"});

    delete qe;
    
}