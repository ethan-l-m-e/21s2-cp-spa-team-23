//
// Created by Lucas Tai on 4/2/22.
//

#ifndef SPA_STRINGFORMATTER_H
#define SPA_STRINGFORMATTER_H
#include <string>
#include <Partition.h>
class StringFormatter {
    public:
        Partition Trim(std::string sourceCode,int type);
};


#endif //SPA_STRINGFORMATTER_H
