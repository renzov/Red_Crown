#include<cstdio>
#include<queue>
#include<algorithm>
#include<climits>
using namespace std;
typedef pair<int,int> pii;
const int MAXN = 1024;
int N, M;

int A[MAXN][MAXN];
int S[MAXN][MAXN];

deque< pii > Q[MAXN];
deque< pii > colQ;

inline int getSum( const int &x, const int &y, const int &nx, const int &ny ){
	return S[nx][ny] - S[x - 1][ny] - S[nx][y - 1] + S[x - 1][y - 1];
}

inline void pop( deque<pii> &q, const int &p ){
	while ( !q.empty() && q.front().second <= p ) q.pop_front();
}

inline int getMax( deque<pii> &q ){ return ( !q.empty() )? q.front().first:0; }

void insert( deque<pii> &q, const int &v, const int &p ){
	while ( !q.empty() && q.back().first <= v ) q.pop_back();
	q.push_back( pii( v, p ) );
}
	
int solve( const int &n, const int &m ){
	if ( n == 1 && m == 1 ) return 0;
	// initialize the data
	for ( int j=1; j <= M; ++j )
		for ( int i=1; i <= n; ++i )
			insert( Q[j], A[i][j], i );
	for ( int i=1; i <= m; ++i )
		insert( colQ, getMax( Q[i] ), i );
	
	int Mx;
	int res = INT_MAX;
	int val, sum;
	for ( int i=1; i <= (N - n + 1); ++i ){
		for ( int j=1; j <= (M - m + 1); ++j ){
			Mx = getMax( colQ );
			sum = getSum( i, j, i + n - 1, j + m  - 1 );
			val = Mx*n*m - sum;
			//printf("submatrix [ %d, %d ] x [ %d, %d ] max = %d - sum = %d\n", i, i + n - 1, j, j + m - 1, Mx, sum);
			if ( res > val ) res = val;
			// prepare for next interation
			pop( colQ, j );
			if ( (j + m) <= M ){
				insert( colQ, getMax( Q[j + m] ), j + m );
			}
		}
		if ( (i + n) <= N ){
			for ( int j=1; j <= M; ++j ){
				pop( Q[j], i );
				insert( Q[j], A[i + n][j], i + n );
			}
			colQ.clear();
			for ( int j=1; j <= m; ++j )
				insert( colQ, getMax( Q[j] ), j );
		}
	}
	
	colQ.clear();
	for ( int i=1; i <= M; ++i ) Q[i].clear();

	return res;
}

int main(){
	scanf("%d %d", &N, &M);
	for ( int i=1; i <= N; ++i )
		for ( int j=1; j <= M; ++j ){
			scanf("%d", A[i] + j);
			S[i][j] = S[i-1][j] + S[i][j-1] - S[i-1][j-1] + A[i][j];			
		}
	
	int Q;
	scanf("%d", &Q);
	int a, b;
	while ( Q-- ){
		scanf("%d %d", &a, &b);
		printf("%d\n", solve(a,b));
	}
	return 0;
}
