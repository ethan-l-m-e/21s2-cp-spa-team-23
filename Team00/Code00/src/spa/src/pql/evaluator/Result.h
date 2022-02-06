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
    LIST,
    TUPLES,
    EMPTY
};
using ResultHeader = std::variant<
        std::string,
        std::tuple<std::string, std::string>>;
using ResultItem = std::variant<
        bool,
        std::string,
        std::tuple<std::string, std::string>>;

typedef struct Result {
    ResultType resultType = ResultType::EMPTY;
    bool resultBoolean;
    ResultHeader resultHeader;
    std::vector<ResultItem> resultItemList;
} Result;

#endif //SPA_RESULT_H
