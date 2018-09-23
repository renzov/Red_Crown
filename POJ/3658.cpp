#include<cstdio>
using namespace std;

const int MAXN = 100005;
int N;
int H[MAXN];
int W[MAXN];
int L[MAXN];
int R[MAXN];
int left[MAXN];
int right[MAXN];

long long res[MAXN];
int p[MAXN];

inline int find_set( const int &x ){
	return ( x == p[x] )? x:(p[x] = find_set( p[x] ) );
}

int main(){
	int act = 0;
	scanf("%d", &N);
	H[ 0 ] = 1000005;
	H[ N + 1 ] = 1000008;
	for ( int i=1; i <= N; ++i ){
		scanf("%d %d", W + i, H + i );
		if ( H[i] < H[act] ) act = i;
	}
	// Compute L and R pointers
	L[0] = 0;
	for ( int i=1; i <= N; ++i ){
		if ( H[ i - 1 ] < H[ i ] ) L[ i ] = L[ i - 1 ];
		else L[i] = i;
		left[i] = i - 1;
		right[i] = i + 1;
	}
	R[N + 1] = N + 1;
	for ( int i=N; i >= 1; --i ){
		if ( H[i + 1] < H[ i ] ) R[i] = R[i+1];
		else R[i] = i;
	}
	// Init each set
	for ( int i=0; i <= N + 1; ++i ) p[i] = i;
	// Begin the simulation
	long long t = 0;
	int h, l, r;


	for ( int i=0; i < N; ++i ){
		// Fill the water for act
		res[ act ] = t + W[act];
		if ( i == (N - 1) ) break;
		int l = find_set(left[act]);
		int r = find_set(right[act]);
		if ( H[l] < H[r] ){
			h = H[l] - H[act];
			// Merge sets
			p[act] = l;
			W[l] += W[act]; 
			R[l] = l;
			right[l] = right[act];
		}
		else {
			h = H[r] - H[act];
			// Merge sets
			p[act] = r;
			W[r] += W[act];
			L[r] = r;
			left[r] = left[act];
		}
		t += (1LL)*W[act]*h;
		act = find_set( act );
		l = find_set( L[act] );
		r = find_set( R[act] );
		if ( l != act ) act = l;
		else if ( r != act ) act = r;
	}
	for ( int i=1; i <= N; ++i )
		printf("%lld\n", res[i]);
	return 0;
}
