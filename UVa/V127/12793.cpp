#include<cstdio>
#include<cassert>
#include<list>
#include<algorithm>
using namespace std;
typedef pair<int, int> pii;
typedef pair<pii, int > point;

const int MAXM = 505;
const int MAXN = 10005;
long long A[MAXM];
long long B[MAXM];
long long C[MAXM];
long long D[MAXM];

int X[MAXN];
int Y[MAXN];
int Z[MAXN];

list<int> R[MAXN];	// points in each region

int f( const int &plane, const int &pt ){
	long long res = A[plane] * X[pt] + B[plane] * Y[pt] + C[plane] * Z[pt] - D[plane];
	if ( res < 0 ) return -1;
	return 1;
}

void process( const int &N, const int &M ){
	for ( int i = 0; i < M; ++i )
		scanf("%lld %lld %lld %lld", A + i, B + i, C + i, D + i );
	
	for ( int i = 0; i < N; ++i ){
		scanf("%d %d %d", X + i, Y + i, Z + i );
		R[0].push_back( i ); 
	}
	
	int size = 1;
	int sign;
	int r;
	list<int>::iterator p;
	// Now we apply each plane sequentially
	for ( int i = 0; i < M; ++i ){
		r = size;
		for ( int j = 0; j < r; ++j ){
			assert( !R[j].empty() );
			p = R[j].begin();
			sign = f( i , *p );
			p++;
			while ( p != R[j].end() ){
				if ( sign != f( i , *p ) ){
					R[size].push_back( *p );
					R[j].erase( p++ );			// tricky, p++ advances the pointer and returns its previous value
				}
				else {
					p++;
				}
			}
			if ( !R[size].empty() ) size++;
		}
	}

	int ans = 0;
	for ( int i = 0; i < size; ++i )
		ans = max( ans, (int)R[i].size() );
	printf("%d\n", ans );
}

void clean( const int &N ){
	for ( int i = 0; i < N; ++i )
		R[i].clear();
}

int main(){
	int N, M;

	while ( scanf("%d %d", &M, &N) == 2 ){
		process( N, M );
		clean( N );
	}
	return 0;
}
