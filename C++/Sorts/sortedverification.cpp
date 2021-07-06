#include <iostream>
#include <fstream>
#include "json.hpp"
#include <string.h>





nlohmann::json verifySort(const char* filename) {
    std::ifstream jsonFile {filename};
    nlohmann::json jsonObj;
    if (jsonFile.is_open()){
        jsonFile >> jsonObj;
    } else{
        exit(1);
    }

    int size = jsonObj["metadata"]["arraySize"];
    //So if the values in the sample do not have consecutive inversion do nothing
    //otherwise, make a new json object and store all the samples that have consecutive inversion

    //meta data always has information about that sample
    nlohmann::json inversionObj;
    int n{};
    for (auto itr = jsonObj.begin(); itr != --jsonObj.end(); ++itr) {
        nlohmann::json mismatch;
        int k{};//keep count of inversion
        for (int i = 0, j = i+1; i < size && j < size; ++i, ++j) {
//            if (j == size) {//comparing the end with the beginning
//                j = 0;
//            }
            if (itr.value()[i] > itr.value()[j]) { //add mismatch to vector
                std::vector<int> ar{};
                ar.emplace_back(itr.value()[i]);
                ar.emplace_back(itr.value()[j]);
                mismatch[std::to_string(i)] = ar;
                ++k;
            }
        }
        if(k > 0) {//if there is a consecutive inversion
            ++n;
            nlohmann::json sample;
            sample["ConsecutiveInversions"] = mismatch;
            sample["sample"] = itr.value();
            inversionObj[itr.key()] = sample;
        }
    }

    nlohmann::json file;
    inversionObj["metadata"] = jsonObj["metadata"];
    inversionObj["metadata"]["samplesWithInversions"] = n;
    inversionObj["metadata"]["file"] = filename;
    jsonFile.close();
    return inversionObj;
}


//int main(int argc, char* argv[]) {
//    nlohmann::json obj = verifySort(argv[1]);
//    std::cout<<obj<<std::endl;
//    return 0;
//}