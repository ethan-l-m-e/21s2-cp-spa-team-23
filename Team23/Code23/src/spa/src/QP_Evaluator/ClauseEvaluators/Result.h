//
// Created by リム・イーサン on 31/1/22.
//

#ifndef SPA_RESULT_H
#define SPA_RESULT_H

#include <string>
#include <variant>
#include <vector>

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
