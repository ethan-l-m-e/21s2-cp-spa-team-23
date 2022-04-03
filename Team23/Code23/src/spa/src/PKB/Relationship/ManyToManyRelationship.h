#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <limits.h>

#include <unordered_set>
#include <unordered_map>

#include "PKB/PKBHelper.h"

using namespace std;

class ManyToManyRelationship : public AbstractManyToManyRelationship {

    unordered_map<string, unordered_set<string>> lhsToSetRhsMap;

    unordered_map<string, unordered_set<string>> rhsToSetLhsMap;





public:
    void setRelationship(string lhs, string rhs) override {
        if (lhsToSetRhsMap.find(lhs) == lhsToSetRhsMap.end()) {
            lhsToSetRhsMap.emplace(lhs, unordered_set<string>{rhs});
        } else {
            lhsToSetRhsMap[lhs].insert(rhs);
        }

        if (rhsToSetLhsMap.find(rhs) == rhsToSetLhsMap.end()) {
            rhsToSetLhsMap.emplace(rhs, unordered_set<string>{lhs});
        } else {
            rhsToSetLhsMap[rhs].insert(lhs);
        }
    }

    void setRelationship(string lhs, unordered_set<string> setRhs) override {
        lhsToSetRhsMap[lhs] = setRhs;

        for (string rhs : setRhs) {
            if (rhsToSetLhsMap.find(rhs) == rhsToSetLhsMap.end()) {
                rhsToSetLhsMap.emplace(rhs, unordered_set<string>{lhs});
            } else {
                rhsToSetLhsMap[rhs].insert(lhs);
            }
        }
    }

    void setRelationship(unordered_set<string> setLhs, string rhs) override {
        rhsToSetLhsMap[rhs] = setLhs;

        for (string lhs : setLhs) {
            if (lhsToSetRhsMap.find(lhs) == lhsToSetRhsMap.end()) {
                lhsToSetRhsMap.emplace(lhs, unordered_set<string>{rhs});
            } else {
                lhsToSetRhsMap[lhs].insert(rhs);
            }
        }
    }

    bool isRelationship(string lhs, string rhs) override {
        if (lhsToSetRhsMap.find(lhs) != lhsToSetRhsMap.end()) {
            return lhsToSetRhsMap[lhs].find(rhs) != lhsToSetRhsMap[lhs].end();
        } else {
            return false;
        }
    }

    unordered_set<string> getRHS(string lhs) override {

        unordered_set<string> emptySet;

        return (lhsToSetRhsMap.find(lhs) != lhsToSetRhsMap.end()) ? lhsToSetRhsMap[lhs] : emptySet;
    }

    unordered_set<string> getLHS(string rhs) override {

        unordered_set<string> emptySet;

        return (rhsToSetLhsMap.find(rhs) != rhsToSetLhsMap.end()) ? rhsToSetLhsMap[rhs] : emptySet;
    }


    void clear() override {
        lhsToSetRhsMap.clear();
        rhsToSetLhsMap.clear();
    }





};


class ManyToManyRelationshipWithMinMax : public ManyToManyRelationship {
private:

    unordered_map<string, string> lhsToMinRHSMap;
    unordered_map<string, string> lhsToMaxRHSMap;

public:
    void setRelationship(string lhs, string rhs) override {

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

    void setRelationship(string lhs, unordered_set<string> setRhs) override {
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

    void setRelationship(unordered_set<string> setLhs, string rhs) override {
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


    string getRHSMin(string lhs) {
        return lhsToMinRHSMap[lhs];
    }

    string getRHSMax(string lhs) {
        return lhsToMaxRHSMap[lhs];
    }

};
