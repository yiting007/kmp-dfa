#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;

void kmp (string& pat, vector<vector<int>>& dfa) {
    int m = dfa.size(); // #of rows in kmp (possible number of characters)
    int n = pat.size(); // #of columns in kmp (possible number of states)
    dfa[pat[0] - 'a'][0] = 1; // at state 0, if read pat[0] then go to state 1
    int X = 0;  // init state X to be 0
    for (int j = 1; j < n; j++) {
        for (int c = 0; c < m; c++) { // copy mismatch cases
            dfa[c][j] = dfa[c][X];
        }
        dfa[pat[j] - 'a'][j] = j + 1; // set match case
        X = dfa[pat[j] - 'a'][X]; // update state X
    }
}

int search(string& pat, string& target, vector<vector<int>>& dfa) {
    int m = target.size();
    int n = pat.size(); // #of states
    int i = 0, j = 0;
    for (; i < m && j < n; i++) {
        j = dfa[target[i] - 'a'][j];
    }
    if (j == n) return i - n;   // found
    return -1;
}

int main() {
    string pat = "aaa";
    string target = "bbbaabaaa";
    int n = pat.size();
    vector<vector<int>> dfa(26, vector<int>(n, 0));
    kmp(pat, dfa);
    int startIdx = search(pat, target, dfa);
    if (startIdx != -1) {
        cout << "Match from index " << startIdx << endl;
    } else {
        cout << "Do not match" << endl;
    }
    return 0;
}
