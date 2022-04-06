//
// Created by Karan Dev Sapra on 6/4/22.
//

#include "ManyToManyRelationshipWithMinMax.h"


void ManyToManyRelationshipWithMinMax::setRelationship(string lhs, string rhs) {

    ManyToManyRelationship::setRelationship(lhs, rhs);

    if (lhsToMinRHSMap.find(lhs) == lhsToMinRHSMap.end()) {
        lhsToMinRHSMap[lhs] = rhs;
    } else {
        lhsToMinRHSMap[lhs] = std::to_string(std::min(std::stoi(rhs), std::stoi(lhsToMinRHSMap[lhs])));
    }

    if (lhsToMaxRHSMap.find(lhs) == lhsToMaxRHSMap.end()) {
        lhsToMaxRHSMap[lhs] = rhs;
    } else {
        lhsToMaxRHSMap[lhs] = std::to_string(std::max(std::stoi(rhs), std::stoi(lhsToMaxRHSMap[lhs])));
    }


}

void ManyToManyRelationshipWithMinMax::setRelationship(string lhs, unordered_set<string> setRhs) {
    ManyToManyRelationship::setRelationship(lhs, setRhs);

    int min = std::stoi(*setRhs.begin());
    int max = std::stoi(*setRhs.begin());

    for (string rhs : setRhs) {

        int rhsInteger = std::stoi(rhs);

        if (rhsInteger < min) {
            min = rhsInteger;
        }
        if (rhsInteger > max) {
            max = rhsInteger;
        }
    }

    lhsToMinRHSMap[lhs] = std::to_string(min);
    lhsToMaxRHSMap[lhs] = std::to_string(max);

}

void ManyToManyRelationshipWithMinMax::setRelationship(unordered_set<string> setLhs, string rhs) {
    ManyToManyRelationship::setRelationship(setLhs, rhs);

    for (string lhs : setLhs) {

        if (lhsToMinRHSMap.find(lhs) == lhsToMinRHSMap.end()) {
            lhsToMinRHSMap[lhs] = rhs;
        } else {
            lhsToMinRHSMap[lhs] = std::to_string(std::min(std::stoi(rhs), std::stoi(lhsToMinRHSMap[lhs])));
        }

        if (lhsToMaxRHSMap.find(lhs) == lhsToMaxRHSMap.end()) {
            lhsToMaxRHSMap[lhs] = rhs;
        } else {
            lhsToMaxRHSMap[lhs] = std::to_string(std::max(std::stoi(rhs), std::stoi(lhsToMaxRHSMap[lhs])));
        }

    }



}


string ManyToManyRelationshipWithMinMax::getRHSMin(string lhs) {
    return lhsToMinRHSMap.find(lhs) != lhsToMinRHSMap.end() ? lhsToMinRHSMap[lhs] : std::to_string(INT_MAX);
}

string ManyToManyRelationshipWithMinMax::getRHSMax(string lhs) {
    return lhsToMaxRHSMap.find(lhs) != lhsToMaxRHSMap.end() ? lhsToMaxRHSMap[lhs] : 0;
}