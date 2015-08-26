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
        int cur = dfa[target[i] - 'a'][j];
        if (cur <= j) break;
        j = cur;
        cout << "at state " << j << endl;
    }
    return j;
}

int main() {
    string line;
    ifstream file ("test.in");
    if (file.is_open()) {
        while (getline(file,line)){
            cout << line << ": ";

            int n = line.size();
            int res = n;
            vector<vector<int>> dfa(26, vector<int>(n, 0));
            kmp(line, dfa);
            for (int i = 1; i < n; i++) {
                if (line[i] != line[0]) continue;
                if (line.substr(i, n - 1) == line.substr(0, n - i)) {
                    res += (n - i);
                    continue;
                }
                string cur = line.substr(i, n - 1);
                cout << "substring: " << cur << endl;
                cout << search(line, cur, dfa) << endl;
                res += search(line, cur, dfa);
            }
            cout << res << endl;
        }
        file.close();
    }
    return 0;
}
