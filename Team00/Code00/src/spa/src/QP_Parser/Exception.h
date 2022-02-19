#include <string>

#ifndef SPA_EXCEPTION_H
#define SPA_EXCEPTION_H

namespace qp {

class QPInvalidSyntacticException : public std::runtime_error {
public:
    QPInvalidSyntacticException(const std::string& message = "") : std::runtime_error(message) {}
};

class QPInvalidSemanticException : public std::runtime_error {
public:
    QPInvalidSemanticException(const std::string& message = "") : std::runtime_error(message) {}
};

class QPTokenizerException : public std::runtime_error {
public:
    QPTokenizerException(const std::string& message = "") : std::runtime_error(message) {}
};

class QPParserException : public std::runtime_error {
public:
    QPParserException(const std::string& message = "") : std::runtime_error(message) {}
};

class QPEvaluatorException : public std::runtime_error {
public:
    QPEvaluatorException(const std::string& message = "") : std::runtime_error(message) {}
};
}


#endif //SPA_EXCEPTION_H
