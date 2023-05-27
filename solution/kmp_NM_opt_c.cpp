#include<stdio.h>
#include<assert.h>
#include<string.h>
#define MAXN 1000004
int N , M;
char s[MAXN],p[MAXN] , buf[MAXN*2];
int v[MAXN];
int search(char *target,  char *pat) {
    memset(v , -1 , (M+4)*sizeof(int));
    int i = 1;
    int j = 0;
    while (i < M) {
        if (pat[i] == pat[j]) {
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
    while (i < 2*M) {
        if (target[i] == pat[j]) {
            i++;
            j++;
        } else if (j == 0) {
            i++;
        } else {
            j = v[j - 1] + 1;
        }
        if (j == M) {
            return i - j;
        }
    }
    return -1;
}
int check(int x, char *str2) {
    strncpy(buf , s+x , M);
    strncpy(buf+M , s+x , M);
    buf[2*M] = '\0';
    return search(buf, str2) != -1;
};
int wcs[26] , wcp[26];
int same(){
    for(int i=0;i<26;i++)if(wcs[i] != wcp[i])return 0;
    return 1;
}
// O(NM) kmp solution
int main() {
    scanf("%d%d",&N,&M);
    scanf("%s%s",s,p);
    int ans = 0;
    for(int i=0;i<M;i++){
        wcs[s[i] - 'A']++;
        wcp[p[i] - 'A']++;
    }
    for(int i=M;i<=N;i++){
        // if(i> N) break;
        if(same() && check(i - M , p))ans++;
        wcs[s[i-M] - 'A']--;
        if(i!=N)wcs[s[i] - 'A']++;
    }
    printf("%d\n", ans);
    return 0;
}