#include<cstdio>
#include<algorithm>
#include<stack>
using namespace std;
typedef pair<int,int> pii;
const int ULTRA = 150000;
const int MAXN = 100005;
int seg[4*MAXN];
int H[MAXN];
int minL[MAXN];
int minR[MAXN];
int N;

inline int left( const int &x ){ return x << 1; }
inline int right( const int &x ){ return (x << 1)|1; }

int query( const int &node, const int &L, const int &R, const int &l, const int &r ){
	if ( L==l && r == R ) return seg[node];
	int M = (L + R) >> 1;
	if ( r <= M ) return query( left(node), L, M, l, r );
	if ( l > M ) return query( right(node), M + 1, R, l, r );
	return min( query(left(node), L, M, l, M) , query( right(node), M + 1, R, M + 1, r ) );
}

void build( const int &node, const int &L, const int &R ){
	if ( L==R ){ seg[node] = H[L]; return; }
	int M = ( L + R ) >> 1;
	build( left(node), L , M );
	build( right(node), M + 1, R );
	seg[node] = min( seg[left(node)], seg[right(node)] );
}

int main(){
	
	while ( scanf("%d", &N) == 1 ){
		for ( int i=0; i < N; ++i ) scanf("%d", H + i);
		build( 1, 0, N - 1 );
		// Calculate left values
		stack<pii> S;
		for ( int i=1; i < N - 1; ++i ){
			if ( H[i] > H[i - 1] && H[i] > H[i + 1]  ){ // it is a peak
				while ( !S.empty() && S.top().first <= H[i] )
					S.pop();
				if ( S.empty() ){  
					minL[i] = 0;	
				}
				else {
				 	minL[i] = query( 1, 0, N - 1, S.top().second, i);
				}
				S.push( pii( H[i] , i ) );
			}
		}

		while ( !S.empty() ) S.pop();
		// Calculate right values
		for ( int i=N-2; i > 0; --i ){
			if ( H[i] > H[i - 1] && H[i] > H[i + 1]  ){ // it is a peak
				while ( !S.empty() && S.top().first <= H[i] )
					S.pop();
				if ( S.empty() ){
					minR[i] = 0;
				}
				else {
					minR[i] = query( 1, 0, N - 1, i, S.top().second);
				}
				S.push( pii( H[i] , i ) );				
			}		
		}

		bool first = true;
		for ( int i=1; i < N - 1; ++i ){
			if ( H[i] > H[i - 1] && H[i] > H[i + 1] && (H[i] - max( minL[i] , minR[i] ) >= ULTRA) ){ // it is a peak
				if ( !first ) putchar(' '); 
				first = false;
				printf("%d", i + 1);
			}		
		}
		puts("");
	}
	return 0;
}
