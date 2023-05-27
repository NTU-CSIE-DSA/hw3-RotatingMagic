#include "testlib.h"
#include <string>
using namespace std;

const int MAXN = 1000;

int main() {
	registerValidation();
	int N = inf.readInt(1, 1000000 ,"N");  
	inf.readSpace();
	int M = inf.readInt(1, 1000000 ,"M");
	inf.readEoln();
	for(int i=0;i<N;i++){
		char c = inf.readChar();
		ensuref(c >= 'A' && c <= 'Z' , "char range %c" , c);
		if (i == N-1)
			inf.readEoln();
	}
	for(int i=0;i<M;i++){
		char c = inf.readChar();
		ensuref(c >= 'A' && c <= 'Z' , "char range %c" , c);
		if (i == M-1)
			inf.readEoln();
	}
	inf.readEof();
	return 0;
}
