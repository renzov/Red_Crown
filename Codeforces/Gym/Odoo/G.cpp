#include<cstdio>
#include<climits>
#include<vector>
#include<cstdlib>
using namespace std;
const int MAXN = 100005;

typedef pair<long long, long long> frac;

int N, Q;
long long A[MAXN];
long long B[MAXN];
long long res[MAXN];
vector<int> T[MAXN];

vector<int> qV[MAXN];
vector<int> P[MAXN];
vector<int> L;

inline long long f( const int idx, const int &x ){ return A[idx] * x + B[idx]; }

long long gcd( const long long &a, const long long &b ){
	return b == 0? a:( gcd( b, a % b ) );
}

frac inter( const int &i, const int &j ){
	long long num = B[j] - B[i];
	long long den = A[i] - A[j];
	long long g = gcd( llabs(num), llabs(den) );
	return frac( num / g, den / g );
}

long long compare( const frac &f1, const frac &f2 ){
	return f1.first * f2.second - f2.first * f1.second;
}

bool overlap( const int &idx ){	
	// L has at least 2 elements
	int last = (int)L.size() - 1;
	return compare( inter( idx, L[last] ), inter( L[last], L[last - 1] ) ) <= 0;
}

long long query( const int &point ){
	if ( L.empty() ) return INT_MAX;
	if ( (int)L.size() == 1 ) return f( L.back(), point );
	
	int r = (int)L.size() - 1;
	int l = 0;
	int m;

	if ( compare( inter( L[r], L[r - 1] ), frac( point, 1LL ) ) <= 0 )
		return f( L.back(), point );

	while ( r - l > 1 ){
		m = ( l + r ) >> 1;
		if ( compare( inter( L[m], L[m - 1] ), frac( point, 1LL ) ) >= 0 )
			r = m;
		else 
			l = m;
	}
	return f( L[l], point );
}

void dfs( const int &u ){	
	// First, push the line representing u 
	vector<int> prevState;
	while ( (int)L.size() >= 2 && overlap( u ) ){
		prevState.push_back( L.back() );
		L.pop_back();
	}
	// make the push
	L.push_back( u );
	// answer all the queries on u
	int idx, p;
	for ( int i = 0; i < (int)qV[u].size(); ++i ){
		idx = qV[u][i];
		p = P[u][i];
		res[ idx ] = query( p );
	}
	// continue down the tree
	int v;
	for ( int i = 0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		dfs(v);
	}
	// undo the changes
	L.pop_back();
	while ( !prevState.empty() ){
		L.push_back( prevState.back() );
		prevState.pop_back();
	}
}

int main(){
	int idx, p, a, b;

	scanf("%d %d", &N, &Q);
	for ( int i = 0; i < N; ++i ){
		scanf("%d %d %d %d", &idx, &p, &a, &b);
		A[idx] = a, B[idx] = b;
		T[p].push_back( idx );
	}
	for ( int i = 0; i < Q; ++i ){
		scanf("%d %d", &idx, &a);
		qV[idx].push_back( i );
		P[idx].push_back( a );
	}
	for ( int i = 0; i < (int)T[0].size(); ++i )
		dfs( T[0][i] );

	for ( int i = 0; i < Q; ++i )
		printf("%lld\n", res[i]);
	return 0;
}
