#include<cstdio>
#include<set>
using namespace std;
const int MAXN = 50005;
bool nfree[2*MAXN];

int solve( set<int> &X, set<int> &Y ){
	int res = 0;
	while ( !X.empty() && !Y.empty() ){
		if ( *X.begin() < *Y.begin() ){
			res++;
			X.erase( X.begin() );
		}
		Y.erase( Y.begin() );
	}
	return res;
}

int main(){
	freopen("cardgame.in", "r", stdin);
	freopen("cardgame.out", "w", stdout);

	int N; 
	int K, x;

	scanf("%d", &N);
	K = N >> 1;
	
	set<int> L, R;
	for ( int i = 0; i < N; ++i ){
		scanf("%d", &x);
		nfree[x] = true;
		if ( i < K )
			L.insert( x );
		else 
			R.insert( x );
	}
	set<int> A, B;
	for ( int i = 1; i <= 2*N; ++i ){
		if ( nfree[i] ) continue;
		if ( (int)A.size() < K )
			A.insert( i );
		else 
			B.insert( i );
	}
	printf("%d\n", solve( L, B ) + solve( A, R ) );
	return 0;
}
