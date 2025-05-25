#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int MAXN = 100005;

int A[MAXN];

bool possible( const int &M, const int &N, const int &T ){
	
	int idx = 0;
	int f, t = 0;		// cur time
	priority_queue< int, vector<int>, greater<int> > Q;

	for ( int i = 0; i < M; ++i )
		Q.push( A[idx++] );
	
	while ( !Q.empty() ){
		
		f = Q.top();
		t = max( t, f );
		Q.pop();
		if (t > T)
			break;
		if ( idx < N )
			Q.push( f + A[idx++] );
	}
	return t <= T;
}

int main(){
	int N, T;

	scanf("%d %d", &N, &T);
	for ( int i=0; i < N; ++i )
		scanf("%d", A + i );

	if ( *max_element( A, A + N ) > T ){
		puts("-1");
		return 0;	
	}
	
	int l = 0;	// Not possible
	int r = N;	// Possible
	int m;

	while ( r - l > 1 ){
		m = (l + r) >> 1;
		if ( possible(m, N, T) )
			r = m;
		else
			l = m;
	}

	printf("%d\n", r);
	return 0;
}
