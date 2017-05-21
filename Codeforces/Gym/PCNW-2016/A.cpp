#include<algorithm>
#include<cstdio>
#include<climits>
using namespace std;

char s[100];
int a[100];
int L[100];
int R[100];

int main(){
	int N = 0;
	scanf("%s", s);
	for ( int i=0; s[i] ; ++i ){
		a[N++] = s[i] - 'a';
	}

	for ( int i=N-1; i >= 0; --i ){
		R[i] = 25 - a[i];
		for ( int j=i+1; j < N; ++j ){
			if ( a[j] > a[i] ) 
				R[i] = min( R[i], R[j] + a[j] - a[i] - 1 );
		}
	}

	for ( int i=0; i < N; ++i ){
		L[i] = a[i];
		for ( int j=0; j < i; ++j )
			if ( a[j] < a[i] )
				L[i] = min( L[i], L[j] + a[i] - a[j] - 1 );
	}

	int res = L[0] + R[0];
	for ( int i=1; i < N; ++i )
		res = min( res, L[i] + R[i] );
	
	printf("%d\n", res);
	return 0;
}
