//
// Created by Bi Nguyen on 11/3/20.
//
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <iostream>
#include "json.hpp"



nlohmann::json verifyResult(const char* fileName1, const char* fileName2){
    std::ifstream file1 {fileName1};
    std::ifstream file2 {fileName2};
    nlohmann::json jsonObj1;
    nlohmann::json jsonObj2;
    if (file1.is_open() && file2.is_open()){
        file1 >> jsonObj1;
        file2 >> jsonObj2;
    } else{
        exit(1);
    }
    nlohmann::json mismatch;
    nlohmann::json out;
    nlohmann::json f;
    int n{};
    //Assuming that both objects have the same size array;
    for (auto itr1 = jsonObj1.begin(), itr2 = jsonObj2.begin(); itr1 != --jsonObj1.end() && itr2 != --jsonObj2.end(); ++itr1, ++itr2) {
        f[fileName1] = itr1.value();
        f[fileName2] = itr2.value();
        out[itr1.key()] = f;
        int k{};
        for (int i = 0; i < jsonObj1["metadata"]["arraySize"]; ++i) {
            if (itr1.value()[i] != itr2.value()[i]){
                mismatch[std::to_string(i)] =  std::vector<int> {itr1.value()[i], itr2.value()[i]};
                out[itr1.key()]["Mismatches"] = mismatch;
                ++k;
            }
        }
        if (k >0){
            ++n;
        }
    }
    out["metadata"]["File1"] = jsonObj1["metadata"];
    out["metadata"]["File1"]["name"] = fileName1;
    out["metadata"]["File2"] = jsonObj2["metadata"];
    out["metadata"]["File2"]["name"] = fileName2;
    out["metadata"]["samplesWithConflictingResults"] = n;
    std::cout <<out;
    file1.close();
    file2.close();
    return out;
}

//int main(int argc, char* argv[]) {
//    verifyResult(argv[1], argv[2]);
//    return 0;
//}