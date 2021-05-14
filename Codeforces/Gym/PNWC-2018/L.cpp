#include<cstdio>
const int MAXN = 1024;
int A[MAXN];
int B[MAXN];
int N;

bool possible( const int &X ){
	int T = 0;
	for ( int i=0; i < N; ++i )
		if ( A[i] <= X && X <= B[i] )
			T++;
	return T == X;
}

int main(){
	scanf("%d", &N);
	for ( int i=0; i < N; ++i )
		scanf("%d %d", A + i, B + i );
	
	bool found = false;

	for ( int i=N; i >= 0 && !found; --i ){
		if ( possible(i) ){ 
			printf("%d\n", i ); 
			found = true;
		}
	}
	if ( !found ) puts("-1");
	return 0;
}
