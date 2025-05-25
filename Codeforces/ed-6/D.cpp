#include<cstdio>
#include<cstdlib>
#include<set>
#include<map>
#include<climits>
#include<algorithm>
using namespace std;
const int MAXN = 2005;
typedef pair<long long, int> pii;
typedef pair<long long, pii> piii;

int A[MAXN];
int B[MAXN];

long long res;
int cnt;
long long SA = 0;
long long SB = 0;
int resA[2];
int resB[2];

void update( const long long &sum, const long long &val, const int &pA, const int &pB ){
	long long tmp = llabs( sum - val );
	if ( res > tmp ){
		res = tmp;
		cnt = 1;
		resA[0] = pA;
		resB[0] = pB;
	}
}

void update( const long long &sum, const long long &val, const pii &pA, const pii &pB ){
	long long tmp = llabs( sum - val );
	if ( res > tmp ){
		res = tmp;
		cnt = 2;
		resA[0] = pA.first, resA[1] = pA.second;
		resB[0] = pB.first, resB[1] = pB.second;
	}
}

int main(){
	int N, M; 
	
	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){ 
		scanf("%d", A + i );
		SA += A[i];
	}
	scanf("%d", &M);
	for ( int i=0; i < M; ++i ){ 
		scanf("%d", B + i );
		SB += B[i];
	}
	
	res = llabs( SA - SB );
	cnt = 0;
	// Test 1-element replacement
	set< pii > D;
	long long sum;
	set<pii>::iterator pre;
	for ( int i=0; i < N; ++i )
		D.insert( pii( 2LL*A[i], i ) );
	for ( int j=0; j < M; ++j ){
		// remove one element from j
		sum = SA - SB + 2LL*B[j]; 
		pre = D.lower_bound( pii( sum, -INT_MAX ) );
		if ( pre != D.begin() ) pre--;
		for ( int k=0; k < 2; ++k ){
			if ( pre == D.end() ) break;
			update( sum, pre->first, pre->second, j );
			pre++;
		}
	}
	
	// Test 2-element replacement
	set< piii > E;
	for ( int i=0; i < N; ++i )
		for ( int j=i + 1; j < N; ++j )
			E.insert( piii( 2LL*(A[i] + A[j]), pii( i,  j ) ) );
	
	if ( N > 1 && M > 1 ){
		set<piii>::iterator pre2, nxt2;
		for ( int i=0; i < M; ++i )
			for ( int j=i + 1; j < M; ++j ){
				sum = SA - SB + 2LL*( B[i] + B[j] ); 
				pre2 = E.lower_bound( piii( sum , pii(-INT_MAX, -INT_MAX) ) );
				if ( pre2 != E.begin() ) pre2--;
				for ( int k = 0; k < 2; ++k ){
					if ( pre2 == E.end() ) break;
					update( sum, pre2->first, pre2->second, pii( i, j ) );
					pre2++;
				}
			}
	}
	printf("%lld\n%d\n", res, cnt );
	for ( int i=0; i < cnt; ++i )
		printf("%d %d\n", resA[i] + 1, resB[i] + 1 );
		
	return 0;
}
