#include<stdio.h>
#include<assert.h>
#include<string.h>
#define MAXN 1000004
const int mod = 1e9+7;
const int base = 27;
#define llu unsigned long long
const llu prime1 = 4294967279ULL;
const llu modinv1[] = {1ULL, 2147483640ULL, 1431655760ULL, 1073741820ULL, 858993456ULL, 715827880ULL, 3681400525ULL, 536870910ULL, 3340530106ULL, 429496728ULL, 2342709425ULL, 357913940ULL, 1651910492ULL, 3988183902ULL, 286331152ULL, 268435455ULL, 4042322145ULL, 1670265053ULL, 1582356366ULL, 214748364ULL, 2658789268ULL, 3318838352ULL, 2614327909ULL, 178956970ULL, 1030792147ULL, 825955246ULL}; 
llu h1p = 1;
llu h1=1;
int N , M;
char s[MAXN],p[MAXN] , buf[2*MAXN];
long long power[MAXN];
void initpw(){
    power[0] = 1;
    for(int i=1;i<=M;i++){
        power[i] = power[i-1] * base % mod;
    }
}
long long hp = 0;
int check(int x){
    char *temp = buf;
    strncpy(buf , s+x , M);
    strncpy(buf+M , s+x , M);
    long long h = 0;
    for(int i=0;i<M;i++){
        h = (h*base + temp[i] -'A' + 1) % mod;
    }
    if(h == hp) return 1;
    for(int i=M;i<2*M;i++){
        h = (h - (temp[i-M] -'A' + 1) *power[M-1]) % mod;
        if(h < 0) h += mod;
        h = (h*base + temp[i] -'A' + 1) % mod;
        if(h == hp) return 1;
    }
    return 0;
};
// O(NM) solution , but optimized
int wcs[26] , wcp[26];
int same(){
    for(int i=0;i<26;i++)if(wcs[i] != wcp[i])return 0;
    return 1;
}
int main(){
    scanf("%d%d",&N,&M);
    scanf("%s%s",s,p);
    int ans = 0;
    initpw();
    hp = 0;
    for(int i=0;i<M;i++){
        hp = (hp*base + p[i] -'A' + 1) % mod;
    }
    for(int i=0;i<M;i++){
        wcs[s[i] - 'A']++;
        wcp[p[i] - 'A']++;
    }
    // i <= N-M
    for(int i=M;i<=N;i++){
        // if(i> N) break;
        if(same() && check(i - M))ans++;
        wcs[s[i-M] - 'A']--;
        if(i!=N)wcs[s[i] - 'A']++;
    }
    printf("%d\n",ans);
    return 0;
}