#include<cstdio>
#include<cstdlib>
#include<queue>

using namespace std;
char A[16], B[16];

int main(){

	queue<int> Q;
	int d;
	scanf("%s %s", A, B);

	for ( int i = 0; A[i]; ++i ){
		d = abs( A[i] - B[i] );
		if ( d == 0 && Q.empty() ) continue;
		Q.push(d);
	}
	if ( Q.empty() ) Q.push(0);
	while ( !Q.empty() ){
		printf("%d", Q.front());
		Q.pop();
	}
	
	puts("");
	return 0;
}
