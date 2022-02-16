//
// Created by Lucas Tai on 6/2/22.
//

#ifndef SPA_PARTITION_H
#define SPA_PARTITION_H
#include <string>

class Partition {
    std::string firstString;
    std::string secondString;

public:
    Partition(std::string stringOne, std::string stringTwo);
    Partition();
    std::string GetFirstString();
    std::string GetSecondString();
};


#endif //SPA_PARTITION_H
