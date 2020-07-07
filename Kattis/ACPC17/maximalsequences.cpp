#include<cstdio>
#include<iterator>
#include<algorithm>
#include<vector>
using namespace std;
const int MAXN = 100005;

int N;
int K;
int M;
int Q;

int A[MAXN];
int V[MAXN];
int B[MAXN];
vector<int> pos[MAXN];

bool isPossible( const int &L, const int &R ){
	int len = 0;
	int idx;
	for ( int i=0; i < M; ++i ){
		if ( B[i] == -1 ) continue;
		idx = B[i];
		len += distance( lower_bound( pos[idx].begin(), pos[idx].end(), L ), 
						 upper_bound( pos[idx].begin(), pos[idx].end(), R ) );

	}
	return ( (R - L + 1) == len );
}

int main(){
	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d", A + i );
		V[i] = A[i];
	}
	sort( V, V + N );
	K = unique( V, V + N ) - V;
	for ( int i=0; i < N; i++ ){
		A[i] = lower_bound( V, V + K, A[i] ) - V;
		pos[ A[i] ].push_back( i );
	}
	
	scanf("%d", &Q);
	int idx, st;
	while ( Q-- ){
		bool first = false;
		scanf("%d %d", &st, &M);
		st--;
		for ( int i=0; i < M; ++i ){
			scanf("%d", B + i );
			idx = lower_bound( V, V + K, B[i] ) - V;
			if ( idx == K || V[idx] != B[i] ){
				B[i] = -1;
			}
			else {
				B[i] = idx;
				if ( A[st] == idx ) first = true;
			}
		}
		// Now we answer the query
		if ( !first ){ // A[st] not present in B[j]
			puts("0");
		}
		else if ( isPossible(st, N - 1) ) {
			printf("%d\n", N - st);
		}
		else {
			int l = st;
			int r = N - 1;
			int m;
			while ( r - l > 1 ){
				m = ( l + r ) >> 1;
				if ( isPossible( st, m ) )
					l = m;
				else
					r = m;
			}
			printf("%d\n", l - st + 1);
		}
	}
	return 0;
}
