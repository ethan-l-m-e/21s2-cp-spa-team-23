#include "PKBHelper.h"

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

