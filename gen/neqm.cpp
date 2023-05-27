#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	int N = atoi(argv[1]);
    int M = atoi(argv[2]);
	int ans = atoi(argv[3]);
	int cnt = atoi(argv[4]);
	string s, p;
	ensuref(N == M && N && M ,"NM");
	ensuref(ans?!cnt:cnt ,"ans cnt");
	for(int i=0;i<M;i++){
		p.push_back(rnd.next('A', 'Z'));
	}
	int t = rnd.next(0,M-1);
	s = p.substr(t) + p.substr(0,t);
	ensuref(s.length() == M , "len");
	for(int i=0;i<cnt;i++){
		s[rnd.next(0, N-1)] = rnd.next('A', 'Z');
	}
	printf("%d %d\n%s\n%s\n",N,M, s.c_str() , p.c_str());
	return 0;
}
