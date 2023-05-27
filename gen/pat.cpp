#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	int N = atoi(argv[1]);
    int M = atoi(argv[2]);
    int t = atoi(argv[3]);
	string s, p;
	for(int i=0;i<M;i++){
		p.push_back(rnd.next('A', 'Z'));
	}
    int cp = rnd.next(0 , M/2);
    for(int i=0;i<cp;i++){
        p[M - cp - i] = p[i];
    }
	if(t == 0) t = rnd.next(1,max(N/M , 1));
	vector<string> sv(t+1);
	for(int i=0;i< N-t*M;i++){
		sv[rnd.next(0,(int)sv.size()-1)].push_back(rnd.next('A', 'Z'));
	} 
	s += sv[0];
	for(int i=1;i<(int)sv.size();i++){
		s += p + sv[i];
	}
	s.resize(N);
	printf("%d %d\n%s\n%s\n",N,M, s.c_str() , p.c_str());
	return 0;
}
