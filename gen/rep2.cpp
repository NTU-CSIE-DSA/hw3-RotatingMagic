#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	int N = atoi(argv[1]);
    int M = atoi(argv[2]);
	int t = atoi(argv[3]);
    int bk = atoi(argv[4]);
	string s, p;
	assert(N >= M && N && M);
    char cc =rnd.next('A', 'Z');
	for(int i=0;i<M;i++){
		p.push_back(cc);
	}
    for(int i=0;i<abs(bk);i++){
        if(bk > 0) p[M-bk] = rnd.next('A', 'Z');
        else p[-bk] = rnd.next('A', 'Z');
    }
	if(t == 0) t = rnd.next(1,max(N/M , 1));
	vector<string> sv(t+1);
	for(int i=0;i< N-t*M;i++){
		sv[rnd.next(0,(int)sv.size()-1)].push_back(rnd.next('A', 'Z'));
	} 
	s += sv[0];
	for(int i=1;i<(int)sv.size();i++){
        int rot = rnd.next(0 , M-1);
		s += p.substr(rot) + p.substr(0 ,rot) + sv[i];
	}
    ensure(s.size() >= N);
	s.resize(N);
    s.assign(N , cc);
	printf("%d %d\n%s\n%s\n",N,M, s.c_str() , p.c_str());
	return 0;
}
