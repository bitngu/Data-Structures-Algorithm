#include "priorityqueue.h"
#include "json.hpp"
#include <fstream>
#include <iostream>

nlohmann::json readJSON(const char* filename){
    std::ifstream file {filename};
    nlohmann::json content;
    if (!file){ //if there's no valid file name, exit
        perror("");
        exit(1);
    }
    file >> content; //extract file content
    file.close();//close file to avoid memory leak
    return content;
}

void printExecuteHeapOp(const nlohmann::json &content){
    size_t heapSize = content["metadata"]["maxHeapSize"];//get the size of heap
    PriorityQueue queue {heapSize};//make the queue based on the size of heap
    queue.setNumOps(content["metadata"]["numOperations"]);//keep track of current number of operations
    for (auto itr = content.begin(); itr != --content.end(); ++itr) {
      if(itr.value()["operation"] == "insert"){
          //insert when told to insert
          queue.insert(static_cast<Key> (itr.value()["key"]));
      } else{
          //delete when told to delete
          queue.removeMin();
      }
    }
    //print result in json format;
    std::cout << queue.JSON();

}


int main(int argc, char** argv) {
    if (argc < 2){
        std::cout << "Not enough argument" << std::endl;
        exit(1);
    }
    nlohmann::json jsonContent = readJSON(argv[1]);
    printExecuteHeapOp(jsonContent);
    return 0;
}
