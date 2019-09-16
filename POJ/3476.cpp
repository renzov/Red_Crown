#include<cstdio>
#include<set>
#include<cstring>
#include<queue>

using namespace std;
typedef pair<int,int> pii;
const int MAXN = 1000005;

set<pii> S;
int nxt[MAXN];	// for "linked list"
int prev[MAXN];	
int T[MAXN];	// Size of the sets
int f[MAXN];	// set representative (always the leftmost element)
char A[MAXN];	// array of elements
int N;			// number of elements

inline int find_set( const int &x ){ return ( x == f[x] )? x:( f[x] = find_set( f[x] ) ); }

void update( set<pii>::iterator &it ){
	int idx = it->second;
	int size = T[idx];
	S.erase( it );
	int L = prev[ idx ];	// Points to the last element of the previous segment
	// Print 
	putchar( A[idx] );
	for ( int i=0; i < size; i++ ){
		printf(" %d", idx + 1);
		idx = nxt[idx];
	}
	putchar('\n');

	int R = idx; // Now it points to the first element in the next segment
	// Update nxt and prev pointer
	if ( L != -1 ) nxt[L] = R;
	if ( R != -1 ) prev[R] = L;
	// Check if we need to join
	int fL, fR;
	if ( L != -1 && R != -1 && A[L] == A[R] ){
		fL = find_set( L );	
		fR = find_set( R );
		// delete from set
		if ( T[fL] > 1 ) S.erase( pii( -T[fL] , fL ) );
		if ( T[fR] > 1 ) S.erase( pii( -T[fR] , fR ) );
		// create new segment
		f[ fR ] = fL;
		T[ fL ] += T[ fR ];
		S.insert( pii( -T[fL], fL ) );
	}
}

int main(){

	scanf("%s", A);
	N = strlen(A);
	// Initialize prev[]
	prev[0] = -1;
	for ( int i=1; i < N; ++i ) prev[i] = i - 1;
	// Initialize nxt[]
	nxt[N - 1] = -1;
	for ( int i=N - 2; i >= 0; --i ) nxt[i] = i + 1;
	// Initialize union find
	for ( int i=0; i < N; ++i ) f[i] = i;
	// Initialize S
	int cnt = 1;
	int first = 0;
	for ( int i=1; i < N; ++i ){
		if ( A[i] == A[i - 1] ){
			f[i] = f[i - 1];	// union of sets
			cnt++;
		}
		else {
			T[first] = cnt;
			if ( cnt > 1 ) S.insert( pii( -cnt , first ) );
			first = i;
			cnt = 1;;
		}
	}
	T[first] = cnt;
	if (cnt > 1) S.insert( pii( -cnt, first ) );
	// Simulate
	set<pii>::iterator it;
	while ( !S.empty() ){
		it = S.begin();
		if ( it->first == -1 ) break;	// size 1 set
		update( it );
	}
	return 0;
}
