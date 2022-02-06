//
// Created by Lucas Tai on 6/2/22.
//

#include "Partition.h"
std::string firstString;
std::string secondString;

Partition::Partition(std::string stringOne, std::string stringTwo){
    firstString = stringOne;
    secondString = stringTwo;
}
Partition::Partition() {
    firstString = "";
    secondString = "";
}

std::string Partition::GetFirstString() {
    return firstString;
}

std::string Partition::GetSecondString(){
    return secondString;
}
