//
// Created by リム・イーサン on 30/1/22.
//

#ifndef SPA_QUERYPREPROCESSOR_H
#define SPA_QUERYPREPROCESSOR_H

#include <iostream>
#include "pql/query_obj/Query.h"

class QueryPreprocessor {
public:
    static Query parse(std::string query_input);
};


#endif //SPA_QUERYPREPROCESSOR_H
