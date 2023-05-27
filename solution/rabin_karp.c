#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>
#define MAXN 1000004
#define pcnt 3 // number of primes we will use
// O((N+M)logM) solution
const int base = 27;
int N , M;
char s[MAXN],p[MAXN];
long long prt[MAXN][pcnt];
int ans[MAXN];
long long power(long long n , long long pw , int mod){
	long long ans = 1;
	while (pw){
		if (pw & 1) ans = (ans * n) % mod;
		n = n * n % mod;
		pw >>= 1;
	}
	return ans;
}

int cmp (const void * a, const void * b){
   return ( *(long long*)a - *(long long*)b );
};
int cmpv(const void * a, const void * b){
    //compare long long[pcnt]
    for(int i=0;i<pcnt;i++){
        long long tmp = ( ((long long*)a)[i] - ((long long*)b)[i]);
        if(tmp != 0) return tmp >0 ? 1:-1;
    }
    return 0;
};
void run(int mods[]){
    long long pmm1[pcnt];
    for(int i=0;i<pcnt;i++){
        pmm1[i] = power(base , M - 1 , mods[i]);
    }
    for(int j=0;j<pcnt;j++){
        long long hp = 0;
        for(int i=0;i<M;i++){
            hp = (hp*base + p[i] -'A' + 1) % mods[j];
        }
        for(int i=M;i<2*M;i++){
            prt[i - M][j] = hp;
            hp = (hp - (p[i - M] -'A' + 1) * pmm1[j]) % mods[j];
            if(hp < 0) hp += mods[j];
            hp = (hp*base + p[i - M] -'A' + 1) % mods[j];
            
        }
    }
    qsort(prt, M, sizeof(long long)*pcnt, cmpv);
    // i <= N-M
    long long hs[pcnt] = {0}; // hash tuple
    for(int j=0;j<pcnt;j++){
        for(int i=0;i<M;i++){
            hs[j] = (hs[j]*base + s[i] -'A' + 1) % mods[j];
        }
    }
    for(int i=M;i<=N;i++){
        int *it = (int*) bsearch (&hs, prt, M, sizeof(long long)*pcnt, cmpv);
        if(it != NULL){
            ans[i] = 1;
        }
        for(int j=0;j<pcnt;j++){
            hs[j] = (hs[j] - (s[i-M] -'A' + 1) * pmm1[j]) % mods[j];
            if(hs[j] < 0) hs[j] += mods[j];
            hs[j] = (hs[j]*base + s[i] -'A' + 1) % mods[j];
        }
    }
}
int main(){
    scanf("%d%d",&N,&M);
    scanf("%s%s",s,p);
    for(int i=M;i<=N;i++)ans[i] = 0;
    // int primes[] = {1000000+3,1000000+33,1000000+37,1000000+39,1000000+81,1000000+99,1000000+117,1000000+121,1000000+133,1000000+151};
    int primes[] = {10013387 ,10013537 , 10013659};
    run(primes);
    int cnt = 0;
    for(int i=M;i<=N;i++){
        cnt += (ans[i] == 1);
    }
    printf("%d\n",cnt);
    return 0;
}
