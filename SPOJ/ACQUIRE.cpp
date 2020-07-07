#include<cstdio>
#include<climits>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;
typedef pair<int,int> pii;
typedef pair<long long, long long> line;
const int MAXN = 50005;
const double EPS = 1e-6;

int N;
pii E[MAXN];

inline bool cmp2( const pii &A, const pii &B ){
	return A.second <= B.second;
}

inline long long eval( const line &L, const long long &x ){
	return L.first * x + L.second;
}

bool cmp( const line &L2, const line &L1, const line &L ){
	double x1 = (double)(L.second - L1.second) / ( L1.first - L.first );
	double x2 = (double)(L2.second - L1.second) / ( L1.first - L2.first );
	return x1 < x2 || fabs( x1 - x2 ) < EPS;
}

struct ConvexHull {
	deque<line> H;

	void insert( const line &L ){
		if ( H.empty() ){ H.push_back(L); return; }
		if ( H.back().first == L.first ){
			if ( H.back().second <= L.second ) return;
			H.pop_back();
		}
		int size = (int) H.size();
		while ( size > 1 && cmp( H[size - 2], H[size - 1], L ) )
			H.pop_back(), size--;
		H.push_back( L );
	}

	long long query( const long long &x ){
		while ( (int)H.size() > 1 && eval( H[0], x ) >= eval( H[1], x ) )
			H.pop_front();
		return eval( H.front(), x );
	}

} CHT;

int main(){
	int h, w;
	scanf("%d", &N);
	for ( int i = 0; i < N; ++i ){
		scanf("%d %d", &w, &h);
		E[i] = pii( h, w );
	}
	sort(E, E + N);
	deque<pii> pareto;
	pareto.push_back( E[0] );
	for ( int i=1; i < N; ++i ){
		while ( !pareto.empty() && cmp2( pareto.back(), E[i] ) )
			pareto.pop_back();
		pareto.push_back( E[i] );
	}
	N = pareto.size();
	long long dp = 0;
	for ( int i=N - 1; i >= 0; --i ){
		CHT.insert( line( pareto[i].first, dp ) );
		dp = CHT.query( pareto[i].second );
	} 
	printf("%lld\n", dp);
	return 0;
}
