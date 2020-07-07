#include<cstdio>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;
typedef pair<long long, long long> line;
const double EPS = 1e-6;
const int MAXN = 1000005;

long long S[MAXN];

inline long long eval( const line &L, const long long &x ){
	return L.first * x + L.second;
}

bool cmp( const line &L2, const line &L1, const line &L ){
	double x1 = (double)(L1.second - L.second) / (L.first - L1.first);
	double x2 = (double)(L1.second - L2.second) / (L2.first - L1.first); 
	return x1 < x2 || fabs( x1 - x2 ) < EPS;
}

struct ConvexHull {
	deque<line> H;

	long long query( const long long &x ){
		if ( H.empty() ) return 0;
		while ( (int)H.size() > 1 && eval( H[0], x) <= eval(H[1], x) )
			H.pop_front();
		return eval( H.front(), x );
	}

	void insert( const line &L ){
		int size = (int)H.size();
		while ( (int)H.size() > 1 && cmp( H[size - 2], H[size - 1], L ) )
			H.pop_back(), size--;
		H.push_back( L );
	}

} CHT;

int main(){

	int N;
	long long A, B, C, X;

	scanf("%d", &N);
	scanf("%lld %lld %lld", &A, &B, &C);
	S[0] = 0;
	for ( int i=1; i <= N; ++i ){
		scanf("%lld", &X);
		S[i] = S[i - 1] + X;
	}

	long long dp;
	CHT.insert( line(0, 0) );
	for ( int i=1; i <= N; ++i ){
		dp = A * S[i] * S[i] + B * S[i] + C + CHT.query( -2LL * A * S[i] );
		CHT.insert( line( S[i], dp + S[i]*S[i]*A - B*S[i] ) );
	}
	printf("%lld\n", dp);
	return 0;
}
