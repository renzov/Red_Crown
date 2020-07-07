#include<cstdio>
#include<queue>
#include<algorithm>
#include<climits>
using namespace std;
const int MAXN = 10005;
typedef pair<long long, long long> line;

int N, S;
int t[MAXN];
int f[MAXN];
long long T[MAXN];
long long F[MAXN];

inline long long eval( const line &L, const int &x ){
	return L.first * x + L.second;
}

bool cmp( const line &L2, const line &L1, const line &L ){ // Denominators are negative, so the sign is reversed
	return ( ( L1.first - L2.first ) * ( L.second - L1.second ) ) >= ( ( L1.first - L.first ) * ( L2.second - L1.second ) );
} 

struct ConvexHull {
	deque<line> H;
	/* We insert by the "front" as coming from +oo */
	long long query( const int &x ){
		while ( (int)H.size() > 1 && eval(H[0], x) >= eval(H[1], x) ){
			H.pop_front();
		}
		return eval( H.front(), x );
	}
	void insert( const line &L ){
		int size = (int) H.size();
		while ( size > 1 && cmp( H[size - 2], H[size - 1], L )  ){
			//printf("throw away back: (%lld, %lld)\n", H.back().first, H.back().second);
			size--, H.pop_back();
		}
		H.push_back( L );
	}
} CHT;

int main(){
	scanf("%d %d", &N, &S);
	for ( int i=0; i < N; ++i )
		scanf("%d %d", t + i, f + i);
	
	F[N] = T[N] = 0;
	for ( int i=N - 1; i >= 0; --i ){
		F[i] = F[i + 1] + f[i]; 
		T[i] = T[i + 1] + t[i];
	}
	
	long long dp;
	CHT.insert( line( 0, 0 ) );
	for ( int i = N - 1; i >= 0; --i ){
		dp = S * F[i] + T[i] * F[i] + CHT.query( F[i] );
		CHT.insert( line( -T[i], dp ) );
	}
	printf("%lld\n", dp);
	return 0;
}
