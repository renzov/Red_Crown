#include<cstdio>
#include<set>
#include<algorithm>
using namespace std;

typedef pair<int,int> pii;
typedef pair< pii, int > event;
const int MAXN = 40005;

event E[2*MAXN];
int H[MAXN];
set<pii> S;

int main(){
	int N;
	int A, B;
	int x, t, idx;
	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d %d %d", &A, &B, H + i);
		E[2*i] = event( pii( A, 1 ) , i );
		E[2*i + 1] = event( pii( B, 0 ) , i );
	}
	long long res = 0;
	int lastH = 0;
	int lastX = 0;
	sort( E, E + 2*N );
	for ( int i=0; i < 2*N; ){
		x = E[i].first.first;
		res += 1LL * ( x - lastX ) * lastH;
		while ( i < 2*N && E[i].first.first == x ){
			t = E[i].first.second;
			idx = E[i].second;
			if ( t == 0 ){ // Deletion
				S.erase( pii( H[idx] , idx ) );
			}
			else {
				S.insert( pii( H[idx] , idx ) );
			}
			i++;
		}
		lastX = x;
		if ( !S.empty() ) lastH = S.rbegin()->first;
		else lastH = 0;
	}
	printf("%lld\n", res);
	return 0;
}

