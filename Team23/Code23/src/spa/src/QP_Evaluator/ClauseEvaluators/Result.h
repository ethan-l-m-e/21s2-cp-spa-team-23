//
// Created by リム・イーサン on 31/1/22.
//

#ifndef SPA_RESULT_H
#define SPA_RESULT_H

#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <variant>

template <> struct std::hash<std::pair<std::string, std::string>> {
    inline size_t operator()(const std::pair<std::string, std::string> &v) const {
        std::hash<std::string> string_hasher;
        return string_hasher(v.first) ^ string_hasher(v.second);
    }
};

enum class ResultType {
    BOOLEAN,
    STRING,
    TUPLES,
    EMPTY
};
using ResultHeader = std::variant<
        std::string,
        std::pair<std::string, std::string>>;
using ResultItems = std::variant<std::unordered_set<std::string>, std::unordered_set<std::pair<std::string, std::string>>>;

typedef struct Result {
    ResultType resultType = ResultType::EMPTY;
    bool resultBoolean;
    ResultHeader resultHeader;
    ResultItems resultSet;
} Result;

#endif //SPA_RESULT_H
