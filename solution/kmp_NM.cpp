#include <cassert>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int N, M;
string s, p;
int search(const std::string& target, const std::string& p) {
    if (target.size() < p.size()) return -1;
    std::vector<int> v(p.size(), -1);
    int i = 1;
    int j = 0;
    while (i < p.size()) {
        if (p[i] == p[j]) {
            v[i] = j;
            i++;
            j++;
        } else if (j == 0) {
            i++;
        } else {
            j = v[j - 1] + 1;
        }
    }
    i = 0;
    j = 0;
    while (i < target.size()) {
        if (target[i] == p[j]) {
            i++;
            j++;
        } else if (j == 0) {
            i++;
        } else {
            j = v[j - 1] + 1;
        }
        if (j == p.size()) {
            return i - j;
        }
    }
    return -1;
}
bool check(string str1, string& str2) {
    string temp = str1 + str1;
    // return (temp.find(str2) != string::npos);
    return search(temp, str2) != -1;
};
// O(NM) solution
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    cin >> s >> p;
    long long t = (long long)N * M;
    int ans = 0;
    for (int i = 0; i < N; i++) {
        if (i + M - 1 >= N) break;
        if (check(s.substr(i, M), p)) ans++;
    }
    printf("%d\n", ans);
    return 0;
}