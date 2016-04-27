#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <climits>

#define repn( i , a , b ) for( int i = ( int ) a ; i < ( int ) b ; i ++ )
#define rep( i , n ) repn( i , 0 , n ) 
#define all( x )  x.begin() , x.end()
#define rall( x ) x.rbegin() , x.rend()
#define mp make_pair
#define fst first
#define snd second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

const int MAXN = 60;
const int MAXE = 6500; //MAXE > 2 * ( 50*50 + 2*50 )

int nxt[MAXE];
int to[MAXE];
int cap[MAXE];
int flow[MAXE];
int head[ 2*MAXN ];
int d[ 2*MAXN ];
bool visited[ 2*MAXN ];
int used[ 2*MAXN ];
int q[ 2*MAXN ];
int bneck[ 2*MAXN ];
int qt,qf;
int E;
int N;

int A[MAXN][MAXN];
int R[MAXN];
int C[MAXN];
char st[15];

int read_num(){
	int res = 0;
	int cnt = 0;
	bool dot = false;
	scanf("%s", st);
	for ( int i=0; st[i]; ++i ){
		if ( isdigit(st[i]) ){
			if ( dot ) cnt++;			
			res *= 10;
			res += (st[i] - '0');
		}
		else {
			dot = true;
		}
	}
	for ( int i=0; i < (2-cnt); ++i ) res *= 10;
	return res;
}

void add_edge( int f, int t, int c ){
	to[E] = t, cap[E] = c, flow[E] = 0, nxt[E] = head[f], head[f] = E; E++;
	to[E] = f, cap[E] = c, flow[E] = c, nxt[E] = head[t], head[t] = E; E++; 
}

int augment_path( int s, int t ){
	int u,v;
	int e;
	int f = 0;

	qf = qt = 0; //Initializing the queue
	q[ qt++ ] = s;
	bneck[s] = INT_MAX;
	
	fill( visited , visited + N , false );
	used[s] =  -1;
	visited[s] = true;
	while ( qf < qt ){
		u = q[qf++];
		if ( u==t ){
			f = bneck[t];
			while ( u != s ){
				e = used[u];
				flow[e] += f; flow[e^1] -= f;
				u = to[e^1];
			}
			return f;
		}
		for ( e = head[u]; e >= 0 ; e = nxt[e] ){
			v = to[e];
			if ( flow[e] < cap[e] && !visited[v] ){
				bneck[v] = min( bneck[u] , cap[e] - flow[e] );
				visited[v] = true;
				q[qt++] = v;
				used[v] = e;
			}
		}
	}
	return 0;
}


int max_flow( int src, int sink ){
	int res = 0;
	int f;
	while ( (f=augment_path( src , sink )) )
		res += f;
	return res;
}

int main(){

	int runs;
	int n,m;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &m, &n);
		fill( R , R + m, 0 );
		fill( C , C + n, 0 );
		for ( int i=0; i  < m; ++i ){
			for ( int j=0; j < n; ++j ){
				A[i][j] = read_num();
				R[i] += A[i][j];
				C[j] += A[i][j];
			}
		}
		bool ok = true;
		// Test if each row and column has integer sum
		for ( int i=0; i < m && ok; ++i )
			ok &= ( (R[i]%100) == 0 );
		for ( int j=0; j < n && ok; ++j )
			ok &= ( (C[j]%100) == 0 );
		if ( !ok ){
			puts("no");
			continue;
		}
		// Calculate the demands 
		fill( head, head + (n+m+3) , -1 );
		E = 0;
		for ( int i=0; i < m; ++i ) R[i] /= 100, d[ i + 1 ] = -R[i];
		for ( int j=0; j < n; ++j ) C[j] /= 100, d[ j + m + 1 ] = C[j];
			
		int low, up;
		for ( int i=0; i < m; ++i ){
			for ( int j=0; j < n; ++j ){
				if ( A[i][j] % 100 ){ 
					low = A[i][j] / 100; up = low + 1;
				}
				else { 
					low = up = A[i][j] / 100; 
				}
				A[i][j] /= 100;
				add_edge( i+1 , j+m+1, up - low );
				d[i+1] += low;
				d[m+j+1] -= low;
			}
		}	

		int D = 0;
		int neg = 0;
		for ( int i=1; i <= (n+m); ++i ){
			if ( d[i] > 0 ){ 
				add_edge( i , n+m+1, d[i] );
				D += d[i];
			}
			if ( d[i] < 0 ){ 
				add_edge( 0 , i , -d[i] );
				neg -= d[i];
			}
		}

		N = n+m+2; // setting number of vertices for flow
		if ( D != neg || max_flow( 0 , n+m+1 ) != D ){
			puts("no");
			continue;
		}

		for ( int i=1, j; i <= m; ++i ){
			for ( int e = head[i]; e >= 0 ; e = nxt[e] ){
				if ( to[e] > 0 ){
					j = to[e] - m - 1;
					A[i-1][j] = A[i-1][j] + flow[e];
				}
			}
		}
		for ( int i=0; i < m; ++i ){
			printf("%d", A[i][0]);
			for ( int j=1; j < n; ++j )
				printf(" %d", A[i][j]);
			puts("");
		}
	}
	return 0;
}

