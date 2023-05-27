#include <bits/stdc++.h>
using namespace std;

vector<int> Failure(const string &s) {
  vector<int> f(s.size(), 0);
  int k = 0;
  for (int i = 1; i < (int)s.size(); ++i) {
    while (k > 0 && s[i] != s[k]) k = f[k - 1];
    if (s[i] == s[k]) ++k;
    f[i] = k;
  }
  return f;
}
int main(){
    int n , m;
    cin >> n >> m;
    string s, t;
    cin >> s >> t;
    vector<int> f1 = Failure(t+"#"+s);
    reverse(s.begin(), s.end());
    reverse(t.begin(), t.end());
    vector<int> f2 = Failure(t+"#"+s);
    int tl = t.size(), sl = s.size(), stl = sl+1+tl;
    int ans = 0;
    int shift = tl+1;
    for(int i=2*tl;i<=tl+sl;i++){
        int end = i;
        int start = end - (tl-1);
        int rstart = stl-(start-shift)-1;
        if((f1[end]+f2[rstart]) == tl || f1[end]+f2[rstart] == 2*tl)ans++;
    }
    cout << ans << endl;
}