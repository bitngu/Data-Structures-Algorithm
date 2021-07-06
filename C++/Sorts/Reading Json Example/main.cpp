#include <iostream>
#include <fstream>
#include "json.hpp"
int main(int argc, char* argv[]) {
    std::ifstream file{argv[1]};
    nlohmann::json jsonObject;
    if(file.is_open()){
        file >> jsonObject;
    }

    for (auto iterator = jsonObject.begin(); iterator != jsonObject.end(); ++iterator) {
        std::cout << "keys: " << iterator.key() << " values: " <<iterator.value()<<std::endl;
    }




}