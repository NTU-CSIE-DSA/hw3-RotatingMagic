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
// O(NM) kmp solution
int main() {
    scanf("%d%d",&N,&M);
    scanf("%s%s",s,p);
    int ans = 0;
    for (int i = 0; i < N; i++) {
        if (i + M > N) break;
        if (check(i, p)) ans++;
    }
    printf("%d\n", ans);
    return 0;
}