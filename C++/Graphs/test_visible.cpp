//#include "graph.hpp"
//#include "test_utils.hpp"
//
//#include <cassert>
//#include <iostream>
//#include <string>
//#include <vector>
//
//#define GRAPH_FILES_DIR "/Users/bitnguyen/Desktop/UCDavis/Fall 2020/ECS 34/Programming Homework/hw5/"
//
//int main(int argc, char *argv[])
//{
//    if (argc < 2)
//    {
//        std::cerr << "You did not pass a test case number as command-line argument to this executable."
//            << std::endl;
//        return 1;
//    }
//    int caseNum = std::stoi(argv[1]);
//    switch (caseNum)
//    {
//        case 1:
//            // Self-loop
//            TestUtils::checkOpenError(GRAPH_FILES_DIR"invalid1.txt");
//            TestUtils::checkOpenError(GRAPH_FILES_DIR"graph1.txt");
//            break;
//        case 2:
//            // Out-of-range
//            TestUtils::checkOpenError(GRAPH_FILES_DIR"graph1.txt");
//            TestUtils::checkOpenError(GRAPH_FILES_DIR"invalid2.txt");
//            break;
//        case 5:
//        {
//            std::string filename1(GRAPH_FILES_DIR"graph1.txt");
//            UnweightedGraph graph1(filename1);
//            std::cout << "Number of vertices: " << graph1.getNumVertices() << '\n';
//            std::string filename2(GRAPH_FILES_DIR"graph2.txt");
//            UnweightedGraph graph2(filename2);
//            std::cout << "Number of vertices: " << graph2.getNumVertices() << '\n';
//            break;
//        }
//        case 6:
//        {
//            std::string filename1(GRAPH_FILES_DIR"graph3.txt");
//            UnweightedGraph graph1(filename1);
//            std::cout << "Number of vertices: " << graph1.getNumVertices() << '\n';
//            std::string filename2(GRAPH_FILES_DIR"graph4.txt");
//            UnweightedGraph graph2(filename2);
//            std::cout << "Number of vertices: " << graph2.getNumVertices() << '\n';
//            break;
//        }
//        case 7:
//        {
//            UnweightedGraph graph1(GRAPH_FILES_DIR"graph1.txt");
//            std::cout << graph1.getAdjacencyMatrix();
//            UnweightedGraph graph2(GRAPH_FILES_DIR"graph2.txt");
//            std::cout << graph2.getAdjacencyMatrix();
//            break;
//        }
//        case 8:
//        {
//            UnweightedGraph graph1(GRAPH_FILES_DIR"graph3.txt");
//            std::cout << graph1.getAdjacencyMatrix();
//            UnweightedGraph graph2(GRAPH_FILES_DIR"graph4.txt");
//            std::cout << graph2.getAdjacencyMatrix();
//            break;
//        }
//        case 10:
//        {
//            UnweightedGraph graph1(GRAPH_FILES_DIR"graph1.txt");
//            auto adjLists1 = graph1.getAdjacencyLists();
//            TestUtils::sortNeighborLists(adjLists1);
//            std::cout << adjLists1;
//            UnweightedGraph graph2(GRAPH_FILES_DIR"graph2.txt");
//            auto adjLists2 = graph2.getAdjacencyLists();
//            TestUtils::sortNeighborLists(adjLists2);
//            std::cout << adjLists2;
//            break;
//        }
//        case 11:
//        {
//            UnweightedGraph graph1(GRAPH_FILES_DIR"graph3.txt");
//            auto adjLists1 = graph1.getAdjacencyLists();
//            TestUtils::sortNeighborLists(adjLists1);
//            std::cout << adjLists1;
//            UnweightedGraph graph2(GRAPH_FILES_DIR"graph4.txt");
//            auto adjLists2 = graph2.getAdjacencyLists();
//            TestUtils::sortNeighborLists(adjLists2);
//            std::cout << adjLists2;
//            break;
//        }
//        case 13:
//        {
//            UnweightedGraph graph1(GRAPH_FILES_DIR"graph5.txt");
//            auto bfsOrdering = graph1.getBFSOrdering(3);
//            std::vector<std::vector<int>> possibleBFSOrderings
//                {{3, 5, 0, 1, 2, 4},
//                 {3, 5, 0, 2, 1, 4},
//                 {3, 5, 1, 0, 2, 4},
//                 {3, 5, 1, 2, 0, 4},
//                 {3, 5, 2, 0, 1, 4},
//                 {3, 5, 2, 1, 0, 4}};
//            TestUtils::checkOrdering(possibleBFSOrderings, bfsOrdering, "BFS");
//            bfsOrdering = graph1.getBFSOrdering(-100);
//            TestUtils::checkEmptyOrdering(bfsOrdering, "getBFSOrdering");
//            break;
//        }
//        case 14:
//        {
//            UnweightedGraph graph1(GRAPH_FILES_DIR"graph6.txt");
//            auto bfsOrdering = graph1.getBFSOrdering(100);
//            TestUtils::checkEmptyOrdering(bfsOrdering, "getBFSOrdering");
//            bfsOrdering = graph1.getBFSOrdering(9);
//            std::vector<std::vector<int>> possibleBFSOrderings{{9}};
//            TestUtils::checkOrdering(possibleBFSOrderings, bfsOrdering, "BFS");
//            bfsOrdering = graph1.getBFSOrdering(0);
//            /**
//             * If one does a layer-based BFS, they will find 6 layers,
//             * only 3 of which have more than 1 node. Those 3 layers
//             * have 3, 2, and 2 nodes, respectively. Thus, if my
//             * reasoning is correct, there should be 3! * 2! * 2!
//             * = 6 * 2 * 2 = 24 possible orderings.
//             */
//            std::vector<std::vector<int>> possibleBFSOrderings2
//            {
//                // Permutation of the 3 nodes in the second layer.
//                {0, 1, 2, 3, 4, 6, 5, 7, 8, 9},
//                {0, 1, 3, 2, 4, 6, 5, 7, 8, 9},
//                {0, 2, 1, 3, 4, 6, 5, 7, 8, 9},
//                {0, 2, 3, 1, 4, 6, 5, 7, 8, 9},
//                {0, 3, 1, 2, 4, 6, 5, 7, 8, 9},
//                {0, 3, 2, 1, 4, 6, 5, 7, 8, 9},
//                // Permutation of the 2 nodes in the third layer.
//                {0, 1, 2, 3, 6, 4, 5, 7, 8, 9},
//                {0, 1, 3, 2, 6, 4, 5, 7, 8, 9},
//                {0, 2, 1, 3, 6, 4, 5, 7, 8, 9},
//                {0, 2, 3, 1, 6, 4, 5, 7, 8, 9},
//                {0, 3, 1, 2, 6, 4, 5, 7, 8, 9},
//                {0, 3, 2, 1, 6, 4, 5, 7, 8, 9},
//                // Permutation of the 2 nodes in the last layer.
//                {0, 1, 2, 3, 4, 6, 5, 7, 9, 8},
//                {0, 1, 2, 3, 6, 4, 5, 7, 9, 8},
//                {0, 1, 3, 2, 4, 6, 5, 7, 9, 8},
//                {0, 1, 3, 2, 6, 4, 5, 7, 9, 8},
//                {0, 2, 1, 3, 4, 6, 5, 7, 9, 8},
//                {0, 2, 1, 3, 6, 4, 5, 7, 9, 8},
//                {0, 2, 3, 1, 4, 6, 5, 7, 9, 8},
//                {0, 2, 3, 1, 6, 4, 5, 7, 9, 8},
//                {0, 3, 1, 2, 4, 6, 5, 7, 9, 8},
//                {0, 3, 1, 2, 6, 4, 5, 7, 9, 8},
//                {0, 3, 2, 1, 4, 6, 5, 7, 9, 8},
//                {0, 3, 2, 1, 6, 4, 5, 7, 9, 8},
//            };
//            /**
//             * This assertion is here in order to preserve my sanity.
//             */
//            assert(possibleBFSOrderings2.size() == 24);
//            TestUtils::checkOrdering(possibleBFSOrderings2, bfsOrdering, "BFS");
//            break;
//        }
//        case 15:
//        {
//            UnweightedGraph graph1(GRAPH_FILES_DIR"graph7.txt");
//            auto dfsOrdering = graph1.getDFSOrdering(3);
//            std::vector<std::vector<int>> possibleDFSOrderings
//                {{3, 2, 0, 5, 1, 4},
//                 {3, 2, 0, 4, 5, 1},
//                 {3, 4, 2, 0, 5, 1}};
//            TestUtils::checkOrdering(possibleDFSOrderings, dfsOrdering, "DFS");
//            dfsOrdering = graph1.getDFSOrdering(-100);
//            TestUtils::checkEmptyOrdering(dfsOrdering, "getDFSOrdering");
//            break;
//        }
//        case 16:
//        {
//            UnweightedGraph graph1(GRAPH_FILES_DIR"graph8.txt");
//            auto dfsOrdering = graph1.getDFSOrdering(11);
//            std::vector<std::vector<int>> possibleDFSOrderings
//                {{11, 0, 8, 4, 7, 5, 6, 10, 2, 3, 9},
//                 {11, 8, 4, 7, 5, 6, 10, 2, 3, 9, 0},
//                 {11, 0, 8, 4, 5, 6, 10, 2, 7, 3, 9},
//                 {11, 8, 4, 5, 6, 10, 2, 7, 3, 9, 0},
//                 {11, 0, 8, 4, 5, 6, 10, 2, 3, 9, 7},
//                 {11, 8, 4, 5, 6, 10, 2, 3, 9, 0, 7}};
//            TestUtils::checkOrdering(possibleDFSOrderings, dfsOrdering, "DFS");
//            dfsOrdering = graph1.getDFSOrdering(12);
//            TestUtils::checkEmptyOrdering(dfsOrdering, "getDFSOrdering");
//            break;
//        }
//        case 17:
//        {
//            UnweightedGraph graph1(GRAPH_FILES_DIR"graph1.txt");
//            std::cout << graph1.getTransitiveClosure();
//            UnweightedGraph graph2(GRAPH_FILES_DIR"graph4.txt");
//            std::cout << graph2.getTransitiveClosure();
//            break;
//        }
//        case 19:
//        {
//            UnweightedGraph graph1(GRAPH_FILES_DIR"graph1.txt");
//            std::cout << graph1.getAdjacencyMatrix();
//            std::cout << "Number of vertices: " << graph1.getNumVertices() << '\n';
//            auto adjLists1 = graph1.getAdjacencyLists();
//            TestUtils::sortNeighborLists(adjLists1);
//            std::cout << adjLists1;
//            break;
//        }
//        case 20:
//        {
//            // Cases 13 and 15 merged together.
//            UnweightedGraph graph2(GRAPH_FILES_DIR"graph7.txt");
//            UnweightedGraph graph1(GRAPH_FILES_DIR"graph5.txt");
//            auto bfsOrdering = graph1.getBFSOrdering(3);
//            std::vector<std::vector<int>> possibleBFSOrderings
//                {{3, 5, 0, 1, 2, 4},
//                 {3, 5, 0, 2, 1, 4},
//                 {3, 5, 1, 0, 2, 4},
//                 {3, 5, 1, 2, 0, 4},
//                 {3, 5, 2, 0, 1, 4},
//                 {3, 5, 2, 1, 0, 4}};
//            TestUtils::checkOrdering(possibleBFSOrderings, bfsOrdering, "BFS");
//            bfsOrdering = graph1.getBFSOrdering(-100);
//            auto dfsOrdering = graph2.getDFSOrdering(3);
//            std::vector<std::vector<int>> possibleDFSOrderings
//                {{3, 2, 0, 5, 1, 4},
//                 {3, 2, 0, 4, 5, 1},
//                 {3, 4, 2, 0, 5, 1}};
//            TestUtils::checkOrdering(possibleDFSOrderings, dfsOrdering, "DFS");
//            dfsOrdering = graph2.getDFSOrdering(-100);
//            TestUtils::checkEmptyOrdering(dfsOrdering, "getDFSOrdering");
//            TestUtils::checkEmptyOrdering(bfsOrdering, "getBFSOrdering");
//            break;
//        }
//        case 21:
//        {
//            // Cases 16 and 17 merged together.
//            UnweightedGraph graph3(GRAPH_FILES_DIR"graph1.txt");
//            UnweightedGraph graph2(GRAPH_FILES_DIR"graph4.txt");
//            UnweightedGraph graph1(GRAPH_FILES_DIR"graph8.txt");
//            std::cout << graph3.getTransitiveClosure();
//            auto dfsOrdering = graph1.getDFSOrdering(11);
//            std::vector<std::vector<int>> possibleDFSOrderings
//                {{11, 0, 8, 4, 7, 5, 6, 10, 2, 3, 9},
//                 {11, 8, 4, 7, 5, 6, 10, 2, 3, 9, 0},
//                 {11, 0, 8, 4, 5, 6, 10, 2, 7, 3, 9},
//                 {11, 8, 4, 5, 6, 10, 2, 7, 3, 9, 0},
//                 {11, 0, 8, 4, 5, 6, 10, 2, 3, 9, 7},
//                 {11, 8, 4, 5, 6, 10, 2, 3, 9, 0, 7}};
//            TestUtils::checkOrdering(possibleDFSOrderings, dfsOrdering, "DFS");
//            dfsOrdering = graph1.getDFSOrdering(12);
//            TestUtils::checkEmptyOrdering(dfsOrdering, "getDFSOrdering");
//            std::cout << graph2.getTransitiveClosure();
//            break;
//        }
//        case 22:  // runs valgrind
//        {
//            // Case 6 (with transive closures) and case 14.
//            std::string filename1(GRAPH_FILES_DIR"graph3.txt");
//            UnweightedGraph graph1(filename1);
//            std::string filename2(GRAPH_FILES_DIR"graph4.txt");
//            UnweightedGraph graph2(filename2);
//            std::cout << "Number of vertices: " << graph2.getNumVertices() << '\n';
//            std::cout << graph1.getTransitiveClosure();
//            std::cout << graph2.getTransitiveClosure();
//            std::cout << "Number of vertices: " << graph1.getNumVertices() << '\n';
//            UnweightedGraph graph3(GRAPH_FILES_DIR"graph6.txt");
//            auto bfsOrdering = graph3.getBFSOrdering(100);
//            TestUtils::checkEmptyOrdering(bfsOrdering, "getBFSOrdering");
//            bfsOrdering = graph3.getBFSOrdering(9);
//            std::vector<std::vector<int>> possibleBFSOrderings{{9}};
//            TestUtils::checkOrdering(possibleBFSOrderings, bfsOrdering, "BFS");
//            bfsOrdering = graph3.getBFSOrdering(0);
//            /**
//             * If one does a layer-based BFS, they will find 6 layers,
//             * only 3 of which have more than 1 node. Those 3 layers
//             * have 3, 2, and 2 nodes, respectively. Thus, if my
//             * reasoning is correct, there should be 3! * 2! * 2!
//             * = 6 * 2 * 2 = 24 possible orderings.
//             */
//            std::vector<std::vector<int>> possibleBFSOrderings2
//            {
//                // Permutation of the 3 nodes in the second layer.
//                {0, 1, 2, 3, 4, 6, 5, 7, 8, 9},
//                {0, 1, 3, 2, 4, 6, 5, 7, 8, 9},
//                {0, 2, 1, 3, 4, 6, 5, 7, 8, 9},
//                {0, 2, 3, 1, 4, 6, 5, 7, 8, 9},
//                {0, 3, 1, 2, 4, 6, 5, 7, 8, 9},
//                {0, 3, 2, 1, 4, 6, 5, 7, 8, 9},
//                // Permutation of the 2 nodes in the third layer.
//                {0, 1, 2, 3, 6, 4, 5, 7, 8, 9},
//                {0, 1, 3, 2, 6, 4, 5, 7, 8, 9},
//                {0, 2, 1, 3, 6, 4, 5, 7, 8, 9},
//                {0, 2, 3, 1, 6, 4, 5, 7, 8, 9},
//                {0, 3, 1, 2, 6, 4, 5, 7, 8, 9},
//                {0, 3, 2, 1, 6, 4, 5, 7, 8, 9},
//                // Permutation of the 2 nodes in the last layer.
//                {0, 1, 2, 3, 4, 6, 5, 7, 9, 8},
//                {0, 1, 2, 3, 6, 4, 5, 7, 9, 8},
//                {0, 1, 3, 2, 4, 6, 5, 7, 9, 8},
//                {0, 1, 3, 2, 6, 4, 5, 7, 9, 8},
//                {0, 2, 1, 3, 4, 6, 5, 7, 9, 8},
//                {0, 2, 1, 3, 6, 4, 5, 7, 9, 8},
//                {0, 2, 3, 1, 4, 6, 5, 7, 9, 8},
//                {0, 2, 3, 1, 6, 4, 5, 7, 9, 8},
//                {0, 3, 1, 2, 4, 6, 5, 7, 9, 8},
//                {0, 3, 1, 2, 6, 4, 5, 7, 9, 8},
//                {0, 3, 2, 1, 4, 6, 5, 7, 9, 8},
//                {0, 3, 2, 1, 6, 4, 5, 7, 9, 8},
//            };
//            /**
//             * This assertion is here in order to preserve my sanity.
//             */
//            assert(possibleBFSOrderings2.size() == 24);
//            TestUtils::checkOrdering(possibleBFSOrderings2, bfsOrdering, "BFS");
//            break;
//        }
//        default:
//            std::cerr << "Invalid case number." << std::endl;
//            return 2;
//    }
//    return 0;
//}