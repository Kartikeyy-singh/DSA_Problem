#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Solution {
    int mod = 1e9+7;

    long long bep(long long a, long long b) {
        if (b == 0) return 1;
        if (b & 1) {
            return (a * (bep(a, b - 1) % mod)) % mod;
        }
        long long x = bep(a, b / 2) % mod;
        return (x * x) % mod;
    }

public:
    int numberOfGoodPartitions(vector<int>& nums) {
        unordered_map<int, pair<int, int>> ump;
        int n = nums.size();
        for (int i = 0; i < nums.size(); i++) {
            if (ump.find(nums[i]) != ump.end()) {
                ump[nums[i]].second = i;
            } else {
                ump[nums[i]] = {i, i};
            }
        }
        int bp = 0;
        int fp = -1;
        for (int i = 0; i < n; i++) {
            auto x = ump[nums[i]];
            fp = max(fp, x.second);
            if (fp == i && i != n - 1) {
                bp++;
            }
        }
        return bep(2, bp);
    }
};

void driverFunction(const string& inputFile, const string& outputFile) {
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    if (!inFile.is_open() || !outFile.is_open()) {
        cerr << "Error opening file" << endl;
        return;
    }

    int t;
    inFile >> t;  // Read the number of test cases

    auto start = high_resolution_clock::now();  // Start measuring time for the entire function

    for (int testCase = 0; testCase < t; testCase++) {
        int n;
        inFile >> n;  // Read the size of the array for the current test case
        vector<int> nums(n);

        for (int i = 0; i < n; i++) {
            inFile >> nums[i];  // Read the elements of the array
        }

        Solution solution;

        auto startCase = high_resolution_clock::now();  // Start measuring time for this test case
        int result = solution.numberOfGoodPartitions(nums);
        auto endCase = high_resolution_clock::now();  // End measuring time for this test case

        outFile << result << endl;  // Write the result to the output file

        auto durationCase = duration_cast<milliseconds>(endCase - startCase);
        cout << "Test case " << testCase + 1 << " running time: " << durationCase.count() << " ms" << endl;
    }

    auto end = high_resolution_clock::now();  // End measuring time for the entire function
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Total running time: " << duration.count() << " ms" << endl;

    inFile.close();
    outFile.close();
}

int main() {
    string inputFile = "test6.txt";   // Input file name
    string outputFile = "output6.txt"; // Output file name
    driverFunction(inputFile, outputFile);
    return 0;
}
