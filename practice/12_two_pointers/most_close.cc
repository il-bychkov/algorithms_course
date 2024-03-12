#include <iostream>
#include <vector>
#include <limits.h>

int GetDiff(int num1, int num2) {
    return std::abs(num1 - num2);
}

std::pair<int, int> GetMostClose(const std::vector<int>& a, const std::vector<int>& b) {
    if (a.empty() || b.empty()) {
        return {-1, -1};
    }

    size_t i = 0;  // pointer for array A
    size_t j = 0;  // pointer for array B

    size_t a_result = -1, b_result = -1;
    int min_diff = INT_MAX;
    while(i < a.size() && j < b.size()) {
        int current_diff = GetDiff(a[i], b[j]);
        if (current_diff == 0) {
            // equal numbers = instant result
            return {i, j};
        }
    
        if (current_diff < min_diff) {
            min_diff = current_diff;
            a_result = i;
            b_result = j;
        }
        if (a[i] < b[j]) {
            // moving to bigger number from A to get closer to number from B
            ++i;
        } else {
            // moving to bigger number from B to get closer to number from A
            ++j;
        }
    }
    // one of the pointers got to the end - so we already have an answer
    return {a_result, b_result};
}

int main() {
    std::vector<int> a1 {8, 11, 30};
    std::vector<int> b1 {1,  2,  7};
    auto res1 = GetMostClose(a1, b1);
    if (res1.first >= 0 && res1.second >= 0) {
        std::cout << "Most close: " << a1[res1.first] << " and " << b1[res1.second] << "\n";
    } else {
        std::cout << "No result (((" << "\n";
    }

    std::vector<int> a2 {8, 11, 30};
    std::vector<int> b2 {1,  2, 10};
    auto res2 = GetMostClose(a2, b2);
    if (res2.first >= 0 && res2.second >= 0) {
        std::cout << "Most close: " << a2[res2.first] << " and " << b2[res2.second] << "\n";
    } else {
        std::cout << "No result (((" << "\n";
    }
}