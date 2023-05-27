#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	int N = atoi(argv[1]);
    int M = atoi(argv[2]);
    int cnt = atoi(argv[3]);
    int st = atoi(argv[4]);
	string s, p;
	ensure(N >= M && N && M);
    ensure(st <N);
    char cc = rnd.next('A', 'Z');
	for(int i=0;i<M;i++){
		p.push_back(cc);
	}

	for(int i=0;i<N;i++){
		s.push_back(cc);
	}
    for(int i=0;i<cnt;i++){
        s[rnd.next(st , N-1)] = rnd.next('A','Z');
    }
	printf("%d %d\n%s\n%s\n",N,M, s.c_str() , p.c_str());
	return 0;
}
