#include<iostream>
#include<cassert>
#include<string>
const int mod = 1e9+7;
using namespace std;
int N , M;
string s,p;
long long power(long long n , long long pw){
	long long ans = 1;
	while (pw){
		if (pw & 1) ans = (ans * n) % mod;
		n = n * n % mod;
		pw >>= 1;
	}
	return ans;
}
bool check(int x, string &s2){
    string temp = s.substr(x , M);
    temp += temp;
    long long h = 0 , hp = 0;
    for(int i=0;i<M;i++){
        h = (h*26 + temp[i] -'A') % mod;
        hp = (hp*26 + s2[i] -'A') % mod;
    }
    if(h == hp) return 1;
    for(int i=M;i<2*M;i++){
        h = (h - (temp[i-M] -'A') * power( 26 , M-1)) % mod;
        if(h < 0) h += mod;
        h = (h*26 + temp[i] -'A') % mod;
        if(h == hp) return 1;
    }
    return 0;
};
// O(NM) solution
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    cin >> s >> p;
    int ans = 0;
    for(int i=0;i<N;i++){
        if(i+M > N) break;
        if(check(i, p)) ans++;
    }
    cout << ans << '\n';
    return 0;
}