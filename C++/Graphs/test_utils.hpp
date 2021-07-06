#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include <string>
#include <vector>

// For printing adjacency matrices.
std::ostream& operator<<(std::ostream& os,
    const std::vector<std::vector<bool>>& rhs);

// For printing adjacency lists.
std::ostream& operator<<(std::ostream& os,
    const std::vector<std::vector<int>>& rhs);

namespace TestUtils
{

/**
 * Checks if the UnweightedGraph constructor reports an exception
 * when given the given filename.
 */
void checkOpenError(const std::string& filename);

void sortNeighborLists(std::vector<std::vector<int>>& lists);

void checkOrdering(
    const std::vector<std::vector<int>>& possibleOrderings,
    const std::vector<int>& ordering,
    const std::string& label);

void checkEmptyOrdering(const std::vector<int>& ordering,
                        const std::string& label);

}

#endif // TEST_UTILS_HPP