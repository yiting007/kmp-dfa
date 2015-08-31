#include<iostream>
#include<string>
#include<vector>
using namespace std;

void kmp_status(string p, vector<int>& status) {
    //v[i] :where to go (what to compare next) if mismatch occur at i
    status[0] = 0;
    status[1] = 0;

    int cur = 0;
    for (int j = 2; j < p.size(); j++) {

        while (cur != 0 && p[cur] != p[j-1]) {
            cur = status[cur];
        }

        if (p[cur] == p[j-1]) {
            cur = cur + 1;
        }

        status[j] = cur;
    }
}

bool kmp(string p, string text, vector<int>& status) {
    int cur = 0; // cur: All locations before cur have been matched.
    for (int j = 0; j < text.size(); j++) {

        // if don't match, go back to status[cur]
        while (cur > 0 && p[cur] != text[j]) {
            cur = status[cur];
        }

        if(p[cur] == text[j]) {
            cur++;
            if(cur == p.size()) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    string pat = "aab";
    string target = "abaaab";
    cout << "pattern = " << pat << "\t";
    cout << "string = " << target << "\t";
    cout << endl;
    int n = pat.size();
    vector<int> status(n, 0);
    kmp_status(pat, status);
    bool match = kmp(pat, target, status);
    if (match) {
        cout << "Match" << endl;
    } else {
        cout << "Do not match" << endl;
    }
    return 0;
}
