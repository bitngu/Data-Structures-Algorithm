#include "test_utils.hpp"
#include "graph.hpp"

#include <algorithm>
#include <iostream>

std::ostream& operator<<(std::ostream& os,
    const std::vector<std::vector<bool>>& rhs)
{
    for (const auto& row : rhs)
    {
        for (auto val : row)
            os << val << ' ';
        os << '\n';
    }
    return os;
}

std::ostream& operator<<(std::ostream& os,
    const std::vector<std::vector<int>>& rhs)
{
    for (unsigned i = 0; i < rhs.size(); ++i)
    {
        os << i << ": ";
        for (auto n : rhs[i])
            os << n << ' ';
        os << '\n';
    }
    return os;
}

namespace TestUtils
{

void checkOpenError(const std::string& filename)
{
    try
    {
        UnweightedGraph graph(filename);
        std::cout << "No exception was thrown.\n";
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "std::runtime_error exception caught with message: " << e.what() << '\n';
    }
    catch (...)
    {
        std::cout << "Caught exception of unexpected type.\n";
    }
}

void sortNeighborLists(std::vector<std::vector<int>>& lists)
{
    for (auto& row: lists)
        std::sort(row.begin(), row.end());
}

void checkOrdering(
    const std::vector<std::vector<int>>& possibleOrderings,
    const std::vector<int>& ordering,
    const std::string& label)
{
    if (label != "BFS" && label != "DFS")
        throw std::runtime_error{"Invalid label"};
    if (std::find(possibleOrderings.cbegin(), possibleOrderings.cend(),
                  ordering) == possibleOrderings.cend())
        std::cout << "Invalid " << label << " ordering.\n";
    else
        std::cout << "Valid " << label << " ordering.\n";
}

void checkEmptyOrdering(const std::vector<int>& ordering,
                        const std::string& label)
{
    std::cout << label << "() ";
    if (ordering.empty())
        std::cout << "returned EMPTY vector when given invalid start.\n";
    else
        std::cout << "returned NON-EMPTY vector when given invalid start.\n";
}

}  // namespace TestUtils
