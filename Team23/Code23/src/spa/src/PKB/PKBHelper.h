//
// Created by Karan Dev Sapra on 14/3/22.
//

#pragma once


#include <string>
#include <unordered_set>



using namespace std;


unordered_set<string> convertSetGenericsToSetStrings(unordered_set<int> setIntegers) {

    unordered_set<string> setStrings;

    for (int i : setIntegers) {
        setStrings.insert(std::to_string(i));
    }

    return setStrings;
}

unordered_set<string> convertSetGenericsToSetStrings(unordered_set<string> setStrings) {

    return setStrings;
}


//// https://stackoverflow.com/questions/54286969/how-to-convert-a-template-type-to-string-if-it-can-be-a-string-too
//auto to_string(val_t val)
//{
//    if constexpr (std::is_same<val_t, std::string>::value)
//    {
//        return static_cast<std::string>(val);
//    }
//    else
//    {
//        return std::to_string(val);
//    }
//}


unordered_set<string> convertSetGenericToSetStrings(unordered_set<string> setStrings) {

    return setStrings;

}
