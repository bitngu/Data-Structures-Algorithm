#include <fstream>
#include <chrono>
#include <iostream>
#include "json.hpp"
#include "insertionsort.h"
#include "mergesort.h"
#include "quicksort.h"


int numMemAccessIS;
int numCompareIS;
int numMemAccessMS;
int numCompareMS;
int numMemAccessQS;
int numCompareQS;

//For printing purpose
static std::vector<std::string> sample;
static std::vector<int> insertComp;
static std::vector<int> insertMem;
static std::vector<int> mergeComp;
static std::vector<int> mergeMem;
static std::vector<int> quickComp;
static std::vector<int> quickMem;
static std::vector<std::chrono::duration<double>> clock1;
static std::vector<std::chrono::duration<double>> clock2;
static std::vector<std::chrono::duration<double>> clock3;


void writeToFile(std::ofstream &out, const std::string &sample, const std::chrono::duration<double>& wctIS,
                 const std::chrono::duration<double>& wctMS, std::chrono::duration<double>& wctQS);
void timeAnalysis(nlohmann::json& obj, std::ofstream& out);
nlohmann::json readInput(const char* filename);
void printOutput();

void printOutput() {
    std::cout << "Sample" << "," << "InsertionSortTime" << "," << "InsertionSortCompares" << "," <<  "InsertionSortMemaccess" << ","\
    << "MergeSortTime" << "," << "MergeSortCompares" << "," << "MergeSortMemaccess" << "," << "QuickSortTime" << "," \
    <<  "QuickSortCompares" << "," << "QuickSortMemaccess" << std::endl;

    for (size_t i = 0; i <  sample.size() ; ++i) {
        std::cout << sample[i] << "," << clock1[i].count() << "," << insertComp[i] << "," \
        << insertMem[i] << "," << clock2[i].count() << "," << mergeComp[i] << "," << mergeMem[i] << ","\
        << clock3[i].count() <<"," << quickComp[i] << "," << quickMem[i] << std::endl;
    }
}

nlohmann::json readInput(const char* filename) {
    std::ifstream file {filename};
    nlohmann::json jsonObject;
    if(file.is_open()){
        file >> jsonObject;
        return jsonObject;
    }
    else{
        exit(1);
    }
}

void writeToFile(std::ofstream &out, const std::string &sample, const std::chrono::duration<double>& wctIS,
                 const std::chrono::duration<double>& wctMS, std::chrono::duration<double>& wctQS) {
    out << sample <<"," << wctIS.count() << "," << numCompareIS << "," << numMemAccessIS << "," \
    << wctMS.count() << "," << numCompareMS << "," << numMemAccessMS << "," << wctQS.count() << "," \
    << numCompareQS << "," << numMemAccessQS << std::setprecision(6) << std::fixed <<std::endl;
}


void timeAnalysis(nlohmann::json& obj, std::ofstream& out) {
    out << "Sample" << "," << "InsertionSortTime" << "," << "InsertionSortCompares" << "," <<  "InsertionSortMemaccess" \
    << "," << "MergeSortTime" << "," << "MergeSortCompares" << "MergeSortMemaccess" << "," << "QuickSortTime" << "," \
    <<  "QuickSortCompares" << "QuickSortMemaccess" << std::endl;



    for (auto itr = obj.begin(); itr != --obj.end(); ++itr) {
        //global variables to keep track of comparison and memory access of each sort
        numMemAccessIS = 0;
        numCompareIS = 0;
        numMemAccessMS = 0;
        numCompareMS = 0;
        numMemAccessQS = 0;
        numCompareQS = 0;

        //Need 3 copies because we want to sort each individual array;
        std::vector<int> arr1 = itr.value();
        std::vector<int> arr2 = itr.value();
        std::vector<int> arr3 = itr.value();


        //Time each sort
        auto startIS = std::chrono::system_clock::now();
        InsertionSort(&arr1);
        std::chrono::duration<double> wctIS = (std::chrono::system_clock::now() - startIS);
        insertComp.push_back(numCompareIS);
        insertMem.push_back(numMemAccessIS);
        clock1.push_back(wctIS);



        auto startMS = std::chrono::system_clock::now();
        MergeSort(&arr2);
        std::chrono::duration<double> wctMS = (std::chrono::system_clock::now() - startMS);
        mergeComp.push_back(numCompareMS);
        mergeMem.push_back(numMemAccessMS);
        clock2.push_back(wctIS);


        auto startQS = std::chrono::system_clock::now();
        QuickSort(&arr3);
        std::chrono::duration<double> wctQS = (std::chrono::system_clock::now() - startQS);
        quickComp.push_back(numCompareQS);
        quickMem.push_back(numMemAccessQS);
        clock3.push_back(wctIS);
        sample.push_back(itr.key());
        writeToFile(out, itr.key(), wctIS, wctMS, wctQS);
    }

}

int main(int argc, char** argv) {
    nlohmann::json jsonObject = readInput(argv[1]);
    //probably should pass in a file to write to
    std::ofstream out {"TimeOutputExample.csv"};
    timeAnalysis(jsonObject, out);
    printOutput();



}