#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 1000004
char s[MAXN], t[MAXN];
int sl, tl, stl;
char st[MAXN<<1], ts[MAXN<<1];
int F1[MAXN<<1]={0}, F2[MAXN<<1]={0};
void failure(int f[], char ss[]){
    int k = 0;
    for(int i=1;i<stl;i++){
        while(k>0 && ss[i] != ss[k]) k = f[k-1];
        if(ss[i] == ss[k]) k++;
        f[i] = k;
    }
}
int main(){
    int n ,m;
    scanf("%d%d",&n,&m);
    scanf("%s%s", s, t);
    sl = strlen(s); tl = strlen(t); stl = sl+tl+1;
    st[tl] = ts[tl] = '#';
    for(int i=0;i<tl;i++){
        st[i] = t[i];
        ts[i] = t[tl-i-1];
    }
    for(int i=0,j=tl+1;i<sl;i++,j++){
        st[j] = s[i];
        ts[j] = s[sl-i-1];
    }
    st[stl] = ts[stl] = 0;
    failure(F1, st);
    failure(F2, ts);
    int ans = 0, shift = tl+1, end, start, rstart;
    for(int i=2*tl;i<=tl+sl;i++){
        end = i;
        start = end - (tl-1);
        rstart = stl-(start-shift)-1;
        if((F1[end]+F2[rstart]) == tl || (F1[end]+F2[rstart]) == 2*tl)ans++;
    }
    printf("%d\n", ans);
}