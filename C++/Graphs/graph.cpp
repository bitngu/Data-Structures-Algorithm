#include "graph.hpp"

bool isSelfLoop(const int& row, const int &col);
bool isOddInput(int x);
bool isOutofRange(int x, int range);


bool isSelfLoop(const int& row, const int &col){
    return row == col;
}
bool isOddInput(int x){
    return x < 0;
}
bool isOutofRange(int x, int range){
    return x >= range;
}

UnweightedGraph::UnweightedGraph(const std::string& filename)
{
    std::ifstream file {filename};
    if(!file.is_open()){
        throw std::runtime_error(FAILED_OPEN_MSG);
    }
    file >> numVertices;
    for (int i = 0; i < numVertices; ++i) {
        adjacencyMatrix.emplace_back(std::vector<bool> (numVertices, false));
    }
    int row = -1;
    int col = -1;

    std::vector<std::pair<int,int>> isMultiEdge{};


    //need to figure out when user put has an odd value;

    while(file >> row >> col) {
        if (isSelfLoop(row,col) || isOutofRange (row, numVertices) \
            || isOutofRange(col, numVertices)|| isOddInput(row) || isOddInput(col)) {
            throw std::runtime_error(INVALID_GRAPH_MSG);
        }
        adjacencyMatrix.at(row).at(col) = true;
        vertices.insert(row);
        vertices.insert(col);
        isMultiEdge.emplace_back(std::pair<int,int> (row,col));
        //for the odd number of ints;
        row = -1;
        col = -1;
    }

    for (size_t l = 0; l < isMultiEdge.size(); ++l) {
        for (size_t i = l+1; i < isMultiEdge.size(); ++i) {
            if(isMultiEdge.at(l).first == isMultiEdge.at(i).first &&  isMultiEdge.at(l).second == isMultiEdge.at(i).second){
                    throw std::runtime_error(INVALID_GRAPH_MSG);
                }
            }

        }

    int j = 0;
        for (int rows : vertices) {
            edges.emplace_back();
            for (int i = 0; i < numVertices; ++i) {
                if(adjacencyMatrix[rows][i] == 1){
                    edges.at(j).emplace_back(i);
            }
        }
        ++j;
    }


    for (int k = 0; k < numVertices; ++k) {
        adjacencyList.emplace_back();
        for (int i = 0; i < numVertices ; ++i) {
            if(adjacencyMatrix.at(k).at(i) == 1){
                adjacencyList.at(k).emplace_back(i);
            }
        }

    }

    file.close();
}

int UnweightedGraph::getNumVertices() const
{
    return numVertices;
}

std::vector<std::vector<bool>> UnweightedGraph::getAdjacencyMatrix() const
{
    return adjacencyMatrix;
}

std::vector<std::vector<int>> UnweightedGraph::getAdjacencyLists() const
{

    return adjacencyList;
}

std::vector<int> UnweightedGraph::getBFSOrdering(int start) const
{
    std::vector<int> BFSorder {};

    if (start < 0 or isOutofRange(start, numVertices)){
        return BFSorder;
    }
    //initialize a vector that contains all false;
    std::vector<bool> hasVisited(numVertices);
    for (int i = 0; i < numVertices; ++i) {
        hasVisited.at(i) = false;
    }

    std::queue<std::unordered_map<int, std::vector<int>>> queue;
    std::unordered_map<int, std::vector<int>> map{};
    int i = 0;
    for (const int u : vertices) {
        if (start == u) {
            auto v = edges.at(i);
            auto l = std::pair<int, std::vector<int>>(u, v);
            map.insert(l);
            queue.push(map);
            break;
        }
        ++i;
    }

    hasVisited.at(start) = true;
    while (!queue.empty()) {
        auto v = queue.front();
        queue.pop();
        auto itr = v.begin();
        BFSorder.emplace_back(itr->first);
        for (int j : itr->second) { //check the connected vertices
            if (!hasVisited[j]) {//if the vertices have not been visited
                int m = 0;
                std::unordered_map<int, std::vector<int>> newMap{0};
                for (const int u : vertices) { //look for the edges that's connected by the vertices
                    if (j == u) {
                        auto edge = edges.at(m);//get the edges
                        auto l = std::pair<int, std::vector<int>>(u, edge);
                        newMap.insert(l);
                        queue.push(newMap);
                        hasVisited[j] = true;
                    }
                    ++m;
                }
            }
        }
    }
    return BFSorder;
}



std::vector<int> UnweightedGraph::getDFSOrdering(int start) const
{
    std::vector<int> DFSorder {};

    if (start < 0 or  isOutofRange(start, numVertices)){
        return DFSorder;
    }
    //initialize a vector that contains all false;
    std::vector<bool> hasVisited(numVertices);
    for (int i = 0; i < numVertices; ++i) {
        hasVisited.at(i) = false;
    }

    std::stack<std::unordered_map<int, std::vector<int>>> stack;
    std::unordered_map<int, std::vector<int>> l{};
    int i = 0;
    for (const int u : vertices) {
        if (start == u) {
            auto v = edges.at(i);
            auto p = std::pair<int, std::vector<int>>(u, v);
            l.insert(p);
            stack.push(l);
            break;
        }
        ++i;
    }
    hasVisited.at(start) = true;
    while (!stack.empty()) {
        auto v = stack.top();
        stack.pop();
        auto itr = v.begin();//need iterator to get to connected vertices
        DFSorder.emplace_back(itr->first);
        for (int j : itr->second) { //check the edges
            if (!hasVisited[j]) {//if the vertices have not been visited
                int m = 0;
                std::unordered_map<int, std::vector<int>> newMap{0};
                for (const int u : vertices) { //look for the edges that's connected by the vertices
                    if (j == u) {
                        auto edge = edges.at(m);//get the edges
                        auto p = std::pair<int, std::vector<int>>(u, edge);
                        newMap.insert(p);
                        stack.push(newMap);
                        hasVisited[j] = true;
                    }
                    ++m;
                }
            }
        }
    }

    return DFSorder;
}

std::vector<std::vector<bool>> UnweightedGraph::getTransitiveClosure() const
{
    //**NOT the most efficient**
    std::vector<std::vector<bool>> transitiveClosure{adjacencyMatrix};
    std::vector<int> reachable {};//this holds the value that i will be able to go to
    std::vector<std::vector<int>> edgesCopy {edges};// append to the end of edges to see connection
    for (int m = 0; m < 3 ; ++m) {//this iteration is necessary because there's no ordering.
        int curRow = 0;
        for (const auto &v : vertices) {
            auto curRowEdges = edgesCopy.begin();//keeps track of current row of the edges
            int j = 0;//keeps track of the position of my edges
            for (size_t i = 0; i < edges.at(curRow).size(); ++i) {
                //want to iterate through my edges
                int curCol = edges.at(curRow).at(i);
                int k = 0;// keeps track of the currentCol edges
                for (const auto &u : vertices) {
                    if (curCol == u) {
                        //look for the edges of the current Column
                        reachable = *(curRowEdges + k);
                        break;
                    }
                    ++k;
                }
                reachable.emplace_back(curCol);
                if (!reachable.empty()) {
                    edgesCopy.at(curRow).insert(edgesCopy.at(curRow).end(), reachable.begin(), reachable.end());
                }
                ++j;
            }
            for (const auto &col : edgesCopy.at(curRow)) {
                transitiveClosure.at(v).at(col) = true;
            }
            ++curRow;
        }
        for (int l = 0; l < numVertices; ++l) {
            transitiveClosure.at(l).at(l) = true;
        }
    }
    return transitiveClosure;
}

