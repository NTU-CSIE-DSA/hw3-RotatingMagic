#include<stdio.h>
#include<assert.h>
#include<string.h>
#define MAXN 1000004
const int mod = 1e9+7;
int N , M;
char s[MAXN],p[MAXN] , buf[2*MAXN];
long long power(long long n , long long pw){
	long long ans = 1;
	while (pw){
		if (pw & 1) ans = (ans * n) % mod;
		n = n * n % mod;
		pw >>= 1;
	}
	return ans;
}

int check(int x, char s2[]){
    char *temp = buf;
    strncpy(buf , s+x , M);
    strncpy(buf+M , s+x , M);
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
    scanf("%d%d",&N,&M);
    scanf("%s%s",s,p);
    int ans = 0;
    for(int i=0;i<N;i++){
        if(i+M > N) break;
        if(check(i, p)) ans++;
    }
    printf("%d\n",ans);
    return 0;
}