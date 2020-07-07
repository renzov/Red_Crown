#include<cstdio>
#include<cmath>
#include<algorithm>
#include<climits>
#include<queue>
using namespace std;
const double EPS = 1e-6;
const int MAXN = 1000005;
typedef pair<long long, long long> line;
int N;
long long C;
long long X[MAXN];

inline long long eval( const line &L, const long long &x ){
	return L.first * x + L.second;
}

bool cmp( const line &L2, const line &L1, const line &L ){
	double x1 = (double) (L.second - L1.second) / (L1.first - L.first);
	double x2 = (double) (L2.second - L1.second) / (L1.first - L2.first);
	return (fabs(x1 - x2) < EPS) || (x1 < x2);
}

struct ConvexHull {
	deque<line> H;
	
	long long query( const long long &x ){
		while( (int)H.size() > 1 && eval( H[0], x ) >= eval( H[1], x ) ){
			H.pop_front();
		}
		return eval( H.front(), x );
	}

	void insert( const line &L ){
		int size = (int)H.size();
		while ( (int)H.size() > 1 && cmp( H[size - 2], H[size - 1], L ) ){
			size--, H.pop_back();
		}
		H.push_back( L );
	}
}CHT;

int main(){
	scanf("%d %lld", &N, &C);
	for ( int i=0; i < N; ++i )
		scanf("%lld", X + i);
	// Remove repeated points (input does not specify if they are all distinct)
	//N = unique( X, X + N ) - X; // Points as different
	long long dp = 0;
	for ( int i=0; i < N; ++i ){
		CHT.insert( line(-2*X[i], X[i]*X[i] + dp ) );
		dp = C + X[i]*X[i] + CHT.query( X[i] );
	}
	printf("%lld\n", dp);
	return 0;
}
