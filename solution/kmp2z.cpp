#include <assert.h>
#include <stdio.h>
#include <string.h>
#define MAXN 1000004
char s[MAXN], p[MAXN], concat[MAXN * 2];
int z_pre[MAXN * 2], z_suf[MAXN * 2] , f[MAXN * 2];
int z_pre1[MAXN * 2], z_suf1[MAXN * 2];
int diff[MAXN];
int n, m;
void swap(char *a, char *b) {
    char t = *a;
    *a = *b;
    *b = t;
}
int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }
void failure(int f[], char ss[]) {
    int k = 0;
    for (int i = 1; i < n + m + 1; i++) {
        while (k > 0 && ss[i] != ss[k]) k = f[k - 1];
        if (ss[i] == ss[k]) k++;
        f[i] = k;
    }
}
void z_cal1(int z[], char str[]) {
    // compute Z value array (Z algorithm)
    int sz = n + m + 1;
    int L = 0, R = 0;
    z[0] = 0;
    for (int i = 1; i < sz; i++) {
        if (i <= R && z[i - L] <= R - i)
            z[i] = z[i - L];
        else {
            int j = i > R ? 0 : R - i;
            while (i + j < sz && str[i + j] == str[j]) j++;
            z[i] = j;
            L = i, R = i + j - 1;
        }
    }
}
void z_cal(int Z[], int P[]) {
    // compute Z value array (Z algorithm) from kmp
    int N = n+m+1;
    for (int i = 1; i < N; i++)
        if (P[i])
            Z[i - P[i] + 1] = P[i];
    Z[0] = 0;

    if (Z[1])
        for (int i = 1; i < Z[1]; i++)
            Z[i + 1] = Z[1] - i;

    int t;
    for (int i = Z[1] + 1; i < N - 1; i++){
        t = i;
        if (Z[i] && !Z[i + 1])
            for (int j = 1; j < Z[i] && Z[i + j] <= Z[j]; j++) {
                assert(Z[i + j] <= min(Z[j], Z[i] - j));
                Z[i + j] = min(Z[j], Z[i] - j);
                t = i + j;
            }
        i = t;
    }
}
int get_z_pre(int idx) {
    if (idx < 0 || idx >= n) return 0;
    return z_pre[m + 1 + idx];
}
int get_z_suf(int idx) {
    if (idx < 0 || idx >= n) return 0;
    return z_suf[n - idx - 1 + m + 1];
}
int main() {
    scanf("%d%d", &n, &m);
    scanf("%s%s", s, p);
    int sz = n+m+1;
    strncpy(concat, p, m);
    concat[m] = '$';
    strncpy(concat + m + 1, s, n);

    failure(f , concat); 
    z_cal(z_pre, f);
    // z_cal1(z_pre1, concat);


    for(int i=0;i<sz;i++)assert(z_pre[i] == z_pre1[i]);
    // reverse s and p in concat string
    for (int i = 0; i < m / 2; i++) swap(&concat[i], &concat[m - i - 1]);
    // i + (m + 1) , n - i - 1 + (m + 1)
    for (int i = 0; i < n / 2; i++) swap(&concat[i + m + 1], &concat[n - i + m]);
    failure(f , concat);
    z_cal(z_suf, f);
    // z_cal1(z_suf1, concat);


    // for(int i=0;i<sz;i++)assert(z_suf[i] == z_suf1[i]);
    // should be always correct

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int l = i - get_z_suf(i - 1);
        int r = i + get_z_pre(i);
        if (r - l < m) continue;
        // substring of length m start from [l,l+1 ... r-1] are valid rotation
        diff[l]++;
        diff[r - m + 1]--;
        // Difference array
    }
    int cur = 0;
    for (int i = 0; i < n; i++) {
        cur += diff[i];
        if (cur) ans++;
    }
    printf("%d\n", ans);
}