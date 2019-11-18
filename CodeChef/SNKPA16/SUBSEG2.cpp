#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 100005;
const int NLOG = 18;
typedef pair<int,int> interval;
int N, Q;

interval I[MAXN];
int ord[MAXN];
int minsuff[MAXN];
int nxt[NLOG][MAXN];

bool cmp( const int &i, const int &val ){
	return I[i].first < val;
}

bool startpoint( const int &i, const int &j ){
	return I[i].first < I[j].first;
} 

bool equal_end( const interval &A, const interval &B ){
	return A.second == B.second;
}

bool endpoint( const interval &A, const interval &B ){
	return ( A.second != B.second )? (A.second < B.second):(A.first > B.first); 
}

int main(){
	
	scanf("%d %d", &N, &Q);
	for ( int i=0; i < N; ++i )
		scanf("%d %d", &I[i].first, &I[i].second);
	
	sort( I, I + N, endpoint );
	
	N = unique( I, I + N, equal_end ) - I;	// remove intervals with the same end
	
	for ( int i=0; i < N; ++i ) ord[i] = i;

	sort( ord, ord + N, startpoint );		// sort the indices by start point
	// Precalculate the index of the interval with minimum endpoint for all suffixes	
	minsuff[N - 1] = ord[N - 1];
	
	int u, v;
	for ( int i=N - 2; i >= 0; --i ){
		u = ord[i];
		v = minsuff[ i + 1 ];
		minsuff[i] = ( I[ u ].second < I[ v ].second )? u:v;
	}
	int j = 0;	// points to the interval with start greater that the end of I[i] 
	for ( int i=0; i < N; ++i ){	// calculate the nxt[0] pointers
		while ( j < N && I[ ord[j] ].first <= I[i].second )
			j++;
		nxt[0][i] = ( j < N )? minsuff[ j ]:-1;
	}
	// Computation the sparse table
	int log;
	for ( log=0; (1<<log) <= N; ++log  ); log--;
	// Actual computation
	for ( int i=1; i <= log; ++i )
		for ( int j=0; j < N; ++j )
			if ( nxt[i-1][j] != -1 )
				nxt[ i ][ j ] = nxt[ i - 1 ][ nxt[i-1][j] ];
			else 
				nxt[ i ][ j ] = -1;
	// Now we answer the queries
	int l, r;
	int idx, nidx, res;
	for ( log=0; (1<<log) <= N; ++log  ); log--;	
	for ( int i=0; i < Q; ++i ){
		scanf("%d %d", &l, &r);
		idx = lower_bound( ord, ord + N, l, cmp ) - ord;
		if ( idx < N ) idx = minsuff[ idx ];
		if ( idx == N || I[idx].second > r ){
			puts("0"); 	// no interval is contained
			continue;
		}
		res = 1;
		for ( int i=log; i >= 0 && I[idx].second <= r; --i ){
			if ( nxt[i][idx] != -1 ){
				nidx = nxt[i][idx];
				if ( I[nidx].second <= r ){
					idx = nidx;
					res += (1 << i);
				}
			}	
		}
		printf("%d\n", res);
	}
	return 0;
}
