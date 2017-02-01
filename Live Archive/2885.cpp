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
#include <numeric>

#define repn( i , a , b ) for( int i = ( int ) a ; i < ( int ) b ; i ++ )
#define rep( i , n ) repn( i , 0 , n ) 
#define all( x )  x.begin() , x.end()
#define rall( x ) x.rbegin() , x.rend()
#define mp make_pair
#define X first
#define Y second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;
typedef pair< double, pii > pdi;

const int MAXN = 55;
const double EPS = 0.00001;

int N,M,L;
int S;
map<pii, int> H;
pii P[4*MAXN];
pii seg[MAXN];
int T[MAXN];
bool G[4*MAXN][4*MAXN];
double D[4*MAXN][4*MAXN];
bool istele[4*MAXN];

int get_id( int x, int y ){
	pii temp = pii(x,y);
	if ( H.find(temp) == H.end() ){
		P[S] = temp;
		H[ temp ] = S++;
	}
	return H[temp];
}

double dist( const int &x1, const int &y1, const int &x2, const int &y2 ){
	long long d1 = 1LL * (x1-x2) * (x1-x2);
	long long d2 = 1LL * (y1-y2) * (y1-y2);
	return sqrt( (double)(d1 + d2) );
}

long long area(const pii &A, const pii &B, const pii &C){
	return 
	  1LL * ( B.X - A.X ) * ( C.Y - A.Y ) -
	  1LL * ( C.X - A.X ) * ( B.Y - A.Y );
}

bool left ( pii &A, pii &B, pii &C ){
	return area(A, B, C) > 0;
}

bool colinear( const pii &A, const pii &B, const pii &C ){
	return area(A, B, C) == 0;
}

bool proper_inter( const int &i, const int &j, const int &x, const int &y ){
	if ( colinear( P[i], P[j], P[x] ) || colinear( P[i], P[j], P[y] ) || 
		 colinear( P[x], P[y], P[i] ) || colinear( P[x], P[y], P[j] ) )
		 return false;

	return 	( left( P[i], P[j], P[x] ) ^ left( P[i], P[j], P[y] ) ) && 
			( left( P[x], P[y], P[i] ) ^ left( P[x], P[y], P[j] ) );
}

bool between(const pii &A, const pii &B, const pii &C){
	if (!colinear(A,B,C)) return false;
	if ( A.X != B.X )
		return  (A.X <= C.X && C.X <= B.X) ||
				(B.X <= C.X && C.X <= A.X);
	else
		return  (A.Y <= C.Y && C.Y <= B.Y) ||
				(B.Y <= C.Y && C.Y <= A.Y);
}

bool inter( const int &i, const int &j, const int &x, const int &y ){
	if ( proper_inter(i,j,x,y) ) return true;
	if ( between( P[i] , P[j] , P[x] ) || between( P[i] , P[j] , P[y] ) || 
		 between( P[x] , P[y] , P[i] ) || between( P[x] , P[y] , P[j] ) ) return true;
	return false;
}

double dijkstra( int s, int t ){
	if ( s == t ) return 0.0;
	double d[S + 5][MAXN];
	bool inQ[S + 5][MAXN];
	priority_queue< pdi, vector<pdi>, greater<pdi> > q;
	
	for ( int i=0; i < S; ++i ) fill( inQ[i], inQ[i] + N + 2, false );

	d[s][0] = 0.0;
	inQ[s][0] = true;
	q.push( pdi( 0.0 , pii(s,0) ) );

	int u,v,k;
	double w;
	while ( !q.empty() ){
		u = q.top().second.first;
		k = q.top().second.second;
		w = q.top().first;
		q.pop();
		if ( fabs( d[u][k] - w ) > EPS ) continue;
		if ( u == t ) return w;
		for ( v=0; v < S ; ++v ){
			if ( G[u][v] ){
				if ( !inQ[v][k] || (w + D[u][v] < d[v][k]) ){
					inQ[v][k] = true;
					d[v][k] = w + D[u][v];
					q.push( pdi( d[v][k], pii(v,k) ) );
				}
			}
		}
		if ( k < N && istele[u] ){
			for ( int i=0; i < L; ++i ){
				v = T[i];
				if ( u == v || !G[u][v] ) continue;
				if ( !inQ[v][k+1] || w < d[v][k+1] ){
					inQ[v][k+1] = true;
					d[v][k+1] = w;
					q.push( pdi( w, pii(v, k+1) ) );
				}
			}
		}
	}
	return -1;
}

int main(){
	int x, y;
	int s, t;
	while ( 1 ){
		scanf("%d %d %d", &N, &M, &L);
		if ( (N + M + L) == 0 ) break;
		H.clear();
		S = 0;
		for ( int i=0; i < M; ++i ){
			scanf("%d %d", &x, &y);
			seg[i].X = get_id(x, y);
			scanf("%d %d", &x, &y);
			seg[i].Y = get_id(x, y);		
		}
		for (int i=0; i < L ; ++i ){
			scanf("%d %d", &x, &y);
			T[i] = get_id( x , y );
		}
		scanf("%d %d", &x, &y);
		s = get_id(x, y);
		scanf("%d %d", &x, &y);
		t = get_id(x, y);
		// Create the graph
		for ( int i=0; i < S; ++i ){
			istele[i] = false;
			fill( G[i], G[i] + S, false );
		}
		
		for ( int i=0; i < L; ++i ) istele[ T[i] ] = true;
		// Create edges
		bool ok;
		for (int i=0; i < S; ++i)
			for ( int j=i+1; j < S; ++j ){
				ok = true;
				for ( int k=0; k < M && ok; ++k ){
					if ( seg[k].X == i || seg[k].X == j || seg[k].Y == i || seg[k].Y == j )
						continue;
					ok &= !inter( i , j, seg[k].X, seg[k].Y );
				}
				if ( ok ){
					G[i][j] = G[j][i] = true;
					D[i][j] = D[j][i] = dist(P[i].X, P[i].Y, P[j].X, P[j].Y);
				}
			}
		// Do dijkstra
		printf("%.0f\n", dijkstra(s,t));
	}
	return 0;
}

