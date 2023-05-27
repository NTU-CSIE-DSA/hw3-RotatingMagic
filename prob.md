## Description
Remember the magical fairy in the house of Demeter Sphynx Abyssinian (DSA)? The fairy's magic spell can be represented by a string $S$, consisting of uppercase English alphabets of length of $N$. Each substring of $S$ is called a segment of the spell, and a segment generates *magic effect* if it is exactly the same as the pattern $P$, which has a length of $M$. However, a segment may produce *the opposite effect* if it is a rotation of $P$. For example, given a string $A$($A=c_1c_2...c_n$) consisting of $n$ alphabets, $c_i...c_n + c_1...c_{i-1}$ is considered a rotation of $A$, for any $i \in [2,n]$.

To help the fairy debug zir magic spell, can you calculate the total number of segments in zir spell that may generate either the original or the opposite magic effect?
## Input
The first line contains two integers $N$ and $M$.
The second line contains a string of length $N$, the string $S$.
The third line contains a string of length $M$, the pattern $P$.

## Output
Output an integer as the answer in a new line.

## Constraints
* $1 \le M \le N \le 10^{6}$
* $S$ and $P$ consist of only uppercase English letters.

## Subtasks
### Subtask 1（10pts）
* $1 \le N \le 10^{4}$
* $1 \le M \le 10^{2}$

### Subtask 2（15pts）
* $N = M$

### Subtask 3（25pts）
* $1 \le N \times M \le 2 \times 10^{7}$

### Subtask 4（50pts）
* No other contraints.

## Sample Cases
### Sample Input 1
```
7 5
DEABCDE
ABCDE
```
### Sample Output 1
```
3
```
## Hint
**Explanation of Sample 1**

Substrings with a legnth M in $S$ are $[DEABC,EABCD,ABCDE]$. 

The first two are rotations of $P$ and the last one is equal to $P$.