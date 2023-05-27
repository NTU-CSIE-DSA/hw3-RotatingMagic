#include <stdio.h>
#include <string.h>
#include <assert.h>
#define MAXN 1000004
char s[MAXN], p[MAXN], concat[MAXN * 2];
int z_pre[MAXN * 2], z_suf[MAXN * 2];
int diff[MAXN];
int n, m;
void swap(char *a, char *b) {
    char t = *a;
    *a = *b;
    *b = t;
}
int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }
void z_cal(int z[], char str[]) {
    // compute Z value array (Z algorithm)
    int sz = n + m + 1;
    int L = 0, R = 0;
    z[0] = m;
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
int get_z_pre(int idx) {
    if (idx < 0 || idx >= n) return 0;
    return z_pre[m + 1 + idx];
}
int get_z_suf(int idx) {
    if (idx < 0 || idx >= n) return 0;
    return z_suf[n - idx - 1 + m + 1 ];
}
int main() {
    scanf("%d%d", &n, &m);
    scanf("%s%s", s, p);

    strncpy(concat, p, m);
    concat[m] = '$';
    strncpy(concat + m + 1, s, n);

    z_cal(z_pre, concat);
    // reverse s and p in concat string
    for (int i = 0; i < m / 2; i++) swap(&concat[i], &concat[m - i - 1]);
    // i + (m + 1) , n - i - 1 + (m + 1)
    for (int i = 0; i < n / 2; i++) swap(&concat[i + m + 1], &concat[n - i + m]);

    z_cal(z_suf, concat);

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