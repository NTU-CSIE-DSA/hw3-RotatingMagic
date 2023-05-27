#include<stdio.h>
#define MAXN 1000004
int N , M;
char s[MAXN] , p[MAXN];
int check(char *a , char *b){
    for(int i=0;i<M;i++){
        int v = 1;
        for(int j=0;j<M && v;j++){
            if(a[(i+j) % M] != b[j])v=0;
        }
        if(v) return 1;
    }
    return 0;
};
// O(NM^2) solution
int main(){
    scanf("%d%d",&N,&M);
    scanf("%s%s",s,p);
    int ans = 0;
    for(int i=0;i<N;i++){
        if(i+M > N) break;
        if(check(s+i , p)) ans++;
    }
    printf("%d\n",ans);
    return 0;
}