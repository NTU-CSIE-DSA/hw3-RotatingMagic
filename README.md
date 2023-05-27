# Tutorial
## Solution: Rabin-Karp algorithm
### Hash All Rotations

Let the string $T = p + p$, $p$ is the pattern string.
$T_{i}...T_{i+m}$ for $i \in [0,m-1]$ is a rotation of $p$ or equal to $p$.
The hash function 
```math
$$h(T_{i}...T_{i+m}) = T_i\times b^{m-1}+T_{i+1}\times b^{m-2}...+T_{m-1}\times b^{0} \mod x$$
```
And 
```math
$$h(T_{i+1}...T_{i+m+1}) = h(T_{i}...T_{i+m})\times  b- T_{i} \times b^{m}   + T_{i+m+1} \mod x$$
```
Therefore, the hash values of all $p$'s rotations can be computed in $O(M)$ time. 

### Search
There are $n-m+1$ candidate substrings to check in $S$. For each substring, we compute its hash value and check whether it is equal to one of the $p$'s rotation hash values. The checking can be done in $O(logM)$ with sorting and binary search, or $O(1)$ with hash table. Note that the hash values of $S$'s substrings can be computed in the same way as $T$ mentioned in the last section, which cost $O(N)$ in total.

### Hash collision
Please refer to [birthday problem](https://en.wikipedia.org/wiki/Birthday_problem#Probability_table).
If we check multiple hash values using different primes, the equivalent hash space size is $prime_1 \times prime_2 ... $.
In this problem, we at most hash $2 \times 10^6$ strings.
The collision probability $p \lt 10^{-6}$ with hash space size $\approx 1.8 \times 10^{19}$.
### Hash Checking Implementation
Many submissions on Judge look like this:
```
init ans[0 ... n] to 1
for p_j in primes:
    hash_value_set = set()
    for each rotation_i of pattern:
        insert hash(rotation_i , p_j) into hash_value_set
    for each substring_i of S:
        if hash(substring_i, p_j) not in hash_value_set:
            ans[i] = 0
return sum(ans)
```
However, it does **NOT** make a equivalent hash space of size $prime_1\times prime_2\times ...prime_k$
The probability of hash collision of this method is large enough to give you WA, even using like $5$ primes ~ $10^7$.

A proper implementation should be like this:
```
init ans[0 ... n] to 1
hash_value_set = set()
for each rotation_i of pattern:
    hash_tuple_i = []
    for p_j in primes:
        insert hash(rotation_i , p_j) into hash_tuple_i
    insert hash_tuple_i into hash_value_set
    
for each substring_i of S:
    hash_tuple_i = []
    for p_j in primes:
        insert hash(rsubstring_i , p_j) into hash_tuple_i
    if hash_tuple_i not in hash_value_set:
        ans[i] = 0
return sum(ans)
```
Because we use the tuple $(hash_{p1},hash_{p2}, ...)$ to compare, the equivalent hash space will be $prime_1\times prime_2 \times...prime_k $.
And the probability will be equivalent to the table provided in [birthday problem](https://en.wikipedia.org/wiki/Birthday_problem#Probability_table).
Note that we cannot search the hash tuple by a naive hash table of size $prime_1 \times prime_2...prime_k $.
We can use sorting + binary search or a well-implemented hash set.


## Solution: Z algorithm
Let's skip the detail of Z algorithm and define z value
```math
Z(T, i)=\begin{cases}
0& ,i = 1\\
max\{p:T_{1...p} = T_{i...i+p}\}& ,\text{for }1\lt i\lt n
\end{cases}
```

1-index here.

Let $T = P + \\# +  S$ and $T_{r} = P_{r} + \\# +  S_{r}$.
$S$ is the target string and $P$ is the pattern. 
$S_r$ is the reverse of $S$, $P_r$ is the reverse of $P$.
For example,
```
S=DEABCDE , P=ABCDE
T=      ABCDE#DEABCDE
Z(T)=   0000000050000

T_r=    EDCBA#EDCBAED
Z(T_r)= 0000005000020

T=      ABCDE$#EABCDE
Z_r(T)= 0000000200005
```
In convenience, we further define $Z_{r}(T,i) = Z(T_r, n-i+m)$.
One can imagine this is just an index conversion because we have reversed the string.

For $i=9=3+(m+1)$, $Z(9) = 5$ means $T_{9...13}=ABCDE=T_{1...5}$.

For $i=8=2+(m+1)$, $Z_{r}(8) = 2$ means $T_{8...7}=ED=T_{5...4}$.

By Z algorithm, these functions can be calculated in $O(n+m)$ time.
### Finding Rotation
Let $L_i = i - Z_{r}(i-1)$ , $R_i = i + Z(i)$.
If $R_i - L_i >= m$, it means that substrings of length m start from indices $j \in [L_i, R_i-m]$ are valid rotations.
However, intervals $[L_i,R_i-m]$ may overlap for different $i$. The length $R_i-m - L_i +1$ cannot be directly added to the answer.

### Interval problem
We can store all intervals instead. In the end, sort all intervals in $O(nlogn)$ time and merge the overlapped intervals in $O(n)$ time.
The final answer will be the total length of merged intervals.

This interval problem can also be solved in $O(n)$ time by **Difference array**.
## Solution
[Source Code - Rabin-Karp](./solution/rabin_karp.c)

[Source Code - Z algorithm](./solution/zalgo.c)

## Wrong Answer: KMP

### WA solution
$prefix(i)=$ longest suffix $S_{k...i}$ of $S_i$ s.t. $S_{k...i}$ is prefix of $P$.

$suffix(i)=$ longest $S_{i...k}$ s.t. $S_{i...k}$ is suffix of $P$.

The prefix can be computed using KMP(S, P) and the suffix can be computed using KMP($S^r$, $P^r$).

```
S=DEABCDE
P=ABCDE
prefix=0012345
suffix=2154321
```
#### Common Mistake 1
Some solutions use the condition

$prefix(i) + suffix(i-m+1) =M$ or $prefix(i) + suffix(i-m+1) =2*M$ 

to determine whether $S_{i-m+1...i}$ is a rotation. This is incorrect for evil test cases on NTU COOL.
```
S=AABA
P=ABAA
prefix=1123
suffix=2101

// suffix[0]=2 
// becauase S[0:2] = AA = P[2:4], 
// but (S[0:3] = AAB) != (P[1:4] = BAA)
```
$prefix(3) = 3 , suiifx(0) = 2$, $3+2 = 5 > m =4$.
The output is $0$, but the correct answer is $1$.

#### Common Mistake 2
One may consider using the conditoin $prefix(i) + suffix(i-m+1) \ge M$ to check.
```
S=BAAB
P=AABA
prefix=0123
suffix=2110
```
Same, $prefix(3) = 3 , suiifx(0) = 2$, $3+2 = 5 > m =4$.
The output is $1$, but the correct answer is $0$.
