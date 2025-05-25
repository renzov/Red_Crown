#include<cstdio>
using namespace std;
const int MAXN = 10005;

int X[MAXN << 1];

inline bool in( const int &x, const int &l, const int &r ){
	return x >= l && x < r;
}

bool test( const int &N, const int &L, const int &shift ){
	int l = shift;
	int r = shift + L;

	int idx = 0;
	
	while ( idx < N && X[idx] < l ) idx++;
	
	if ( idx >= N ) return false;

	for ( int i = idx; i < (idx + N); ++i ){
		if ( !in( X[i], l, r ) ) return false;
		l += L, r += L;
	}
	return true;
}

void process( const int &C, const int &N ){
	int L = C / N;
	for ( int i = 0; i < N; ++i ){
		scanf("%d", X + i );
		X[i + N] = X[i] + C;
	}
	
	bool found = false; 
	for ( int shift = 0; shift < L && !found; ++shift )
		if ( test( N, L, shift ) ) found = true;
	
	puts( found? "S":"N" );
}

int main(){
	int C, N;
	while ( scanf("%d %d", &C, &N ) == 2 )
		process( C, N );
	return 0;
}
