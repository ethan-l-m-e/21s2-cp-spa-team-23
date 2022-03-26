//
// Created by リム・イーサン on 31/1/22.
//

#ifndef SPA_RESULT_H
#define SPA_RESULT_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>

using std::pair;
using std::string;
using std::unordered_set;
using std::variant;

template <> struct std::hash<pair<string, string>> {
    inline size_t operator()(const pair<string, string> &v) const {
        std::hash<string> string_hasher;
        return string_hasher(v.first) ^ string_hasher(v.second);
    }
};

enum class ResultType {
    BOOLEAN,
    SINGLE,
    PAIR,
    EMPTY
};
using ResultHeader = variant<string, pair<string, string>>;
using ResultItems = variant<
        unordered_set<string>,
        unordered_set<pair<string, string>>
        >;

typedef struct Result {
    ResultType resultType = ResultType::EMPTY;
    bool resultBoolean;
    ResultHeader resultHeader;
    ResultItems resultSet;
} Result;

#endif //SPA_RESULT_H
