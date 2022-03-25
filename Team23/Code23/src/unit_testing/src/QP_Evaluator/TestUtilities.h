//
// Created by Tianyi Wang on 12/3/22.
//
#include "catch.hpp"
#include <utility>
#include "QP_Evaluator/QueryEvaluator.h"
#include "SourceProcessor/Parser.h"
#include "SourceProcessor/DesignExtractor.h"

#pragma once

using ArgList = std::vector<Argument>;
using ResultSet = std::unordered_set<string>;

Query makeQuery(unordered_map<string, DesignEntity>& declarations, std::vector<Argument> synonyms);
Query makeQuery(unordered_map<string, DesignEntity>& declarations, std::vector<Argument> synonyms, vector<SuchThatClause> suchThatClauses, vector<PatternClause> patternClauses);
Query makeQuery(unordered_map<string, DesignEntity>& declarations, std::vector<Argument> synonyms, vector<SuchThatClause> suchThatClauses);
Query makeQuery(unordered_map<string, DesignEntity>& declarations, std::vector<Argument> synonyms, vector<PatternClause> patternClauses);
ResultSet generateResultSet (list<string> result);
ResultSet evaluateAndCreateResultSet(QueryEvaluator *qe, Query *query);
PKB* generateSamplePKB();
PKB* generateSamplePKBForPatternMatchingAssign();
PKB* generateSamplePKBForPatternMatchingCondition();
PKB* constructPKBWithParser(string);
vector<unordered_map<int, NodeCFG*>> constructCFGForTesting();
vector<unordered_map<int, NodeCFG*>> constructCFGForSamplePKB();