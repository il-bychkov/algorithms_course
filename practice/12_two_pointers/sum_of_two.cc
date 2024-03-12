#include <iostream>
#include <vector>


std::pair<int, int> SumOfTwo(const std::vector<int>& a, int target) {
    size_t i = 0;             // left  pointer
    size_t j = a.size() - 1;  // right pointer

    // till the left and right pointers meeting
    while (i < j)
    {
        // condition of task
        int current_sum = a[i] + a[j];
        if (current_sum == target) {
            return {i, j};
        } else if (current_sum < target) {
            // increase left pointer to increase sum (numbers are bigger on right side)
            ++i;
        } else {
            // decrease rigth pointer to decrease sum (numbers are smaller on left side) 
            --j;
        }
    }

    // no condition
    return {-1, -1};
}


int main() {
    std::vector<int> numbers {1, 2, 4, 8, 16};

    int target1 = 10;
    auto res1 = SumOfTwo(numbers, target1);
    std::cout << "Target = " << target1 << ": " << res1.first << " " << res1.second << '\n';

    int target2 = 9;
    auto res2 = SumOfTwo(numbers, target2);
    std::cout << "Target = " << target2 << ": " << res2.first << " " << res2.second << '\n';

    int target3 = 13;
    auto res3 = SumOfTwo(numbers, target3);
    std::cout << "Target = " << target3 << ": " << res3.first << " " << res3.second << '\n';
}