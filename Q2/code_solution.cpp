#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Solution {
public:
    int mod = 1e9+7;
    long long totalsum(string s) {
        long long n = s.size();
        long long total = (n * (n + 1)) / 2;
        long long ans = 0;
        for (int i = 0; i < 26; i++) {
            long long ct = 0;
            long long tsub = 0;
            bool f = 0;
            for (int j = 0; j < n; j++) {
                if (s[j] != ('a' + i)) {
                    ct++;
                } else {
                    f = 1;
                    tsub += ((ct * (ct + 1)) / 2);
                    ct = 0;
                }
            }
            tsub += ((ct * (ct + 1)) / 2);
            if (f) ans += (total - tsub);
        }
        return ans%mod;
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
        string s;
        inFile >> s;  // Read the string for the current test case

        Solution solution;

        auto startCase = high_resolution_clock::now();  // Start measuring time for this test case
        long long result = solution.totalsum(s);
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
