#include <iostream>
#include <vector>
#include <limits.h>

int GetMinKSum(std::vector<int> a, int sum_threshold) {
    size_t i = 0;  // pointer to 'sum sequence' start
    size_t j = 0;  // pointer to 'sum sequence' end

    int sum = 0;
    int min_seq_len = INT_MAX;
    for (i = 0; i < a.size(); ++i) {
        // we continue the summarization from same spot, no return to back
        while (j < a.size() && sum <= sum_threshold) {
            sum += a[j];
            ++j;
        }
        // task condition
        if (sum > sum_threshold) {
            int seq_len = j - i;
            // save min sequence length
            if (seq_len < min_seq_len) {
                std::cout << "Saving new seq: sum=" << sum <<  "|seq_len=" << seq_len << "|i=" << i << "|j=" << j << "\n";
                min_seq_len = seq_len;
            }
        } else {
            // we exited the 'while' upper loop because of the end of array; no more steps needed
            break;
        }
        // remove first element of 'sum sequence' as we move sequence start pointer further
        sum -= a[i];
    }

    return min_seq_len;
}


int main() {
    std::vector<int> a {1, 2, 3, 4, 5};
    int target = 4;
    auto res = GetMinKSum(a, target);
    std::cout << "Min seq.len for sum > [" << target << "] = " << res << "\n";
}