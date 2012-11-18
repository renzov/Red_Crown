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
#define fst first
#define snd second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;
const int MAX = 1005;
const int MAXE = 4000000;
int n;
struct point{
	long long x,y;
	point(){}
	point(long long X,long long Y){ x = X , y = Y; }
	bool operator<(const point &that) const {
		return ( y != that.y )? (y < that.y) : ( x < that.x );
	}
	point operator-(const point &that) const {
		return point(x - that.x,y - that.y);
	}
};

point R[MAX][4];

int cross( const point &a , const point &b, const point &c ){
	long long res = (c.x - a.x)*(b.y - a.y) - (b.x - a.x)*(c.y - a.y);
	if ( res > 0 ) return 1;
	if ( res < 0 ) return -1;
	return 0;
}

bool on_seg( const point &a , const point &b, const point &c ){
	return  (min( a.x , b.x ) <= c.x) && (c.x <= max( a.x , b.x) ) &&
			(min( a.y , b.y ) <= c.y) && (c.y <= max( a.y , b.y) );
}

bool intersect(const point &p1,const point &p2,const point &p3,const point &p4){
	int d1 = cross( p3, p4, p1 );
	int d2 = cross( p3, p4, p2 );
	int d3 = cross( p1, p2, p3 );
	int d4 = cross( p1, p2, p4 );
	if ( (d1 * d2) < 0 && (d3 * d4) < 0 ) return true;
	if ( d1 == 0 && on_seg(p3, p4, p1) ) return true;
	if ( d2 == 0 && on_seg(p3, p4, p2) ) return true;
	if ( d3 == 0 && on_seg(p1, p2, p3) ) return true;
	if ( d4 == 0 && on_seg(p1, p2, p4) ) return true;
	return false;
}

int head[ 2 * MAX ];
int to[ MAXE ];
int next[ MAXE ];
int m;

void add( int u, int v ){
	to[m] = v, next[m] = head[u], head[u] = m++; 
}

bool inS[2 * MAX];
int scc[2 * MAX];
int number[2 * MAX ];
int low[ 2 * MAX ];
int num;
int top;
int S[2 * MAX];
int SCN;

void dfs( int u  ){
	low[u] = number[u] = num++;
	S[top++] = u; inS[u] = true;
	int v;
	for ( int e = head[u]; e >= 0 ; e = next[e] ){
		v = to[e];
		if ( number[v] < 0 ){
			dfs(v);
			low[u] = min(low[u],low[v]);
		}
		else if ( inS[v] ){
			low[u] = min( low[u] , number[v] );
		}
	}

	if ( low[u] == number[u] ){
		do {
			v = S[--top];
			scc[v] = SCN;
			inS[v] = false;
		}
		while ( v != u );
		SCN++;
	}
}

int main(){
	while (scanf("%d",&n) && n ){
		fill( head , head + 2*n , -1 );
		m = 0; //edge counter
		for ( int i=0; i < n; ++i){
			for ( int j=0; j<4; ++j ) scanf("%lld %lld",&R[i][j].x,&R[i][j].y);
			sort( R[i] , R[i] + 4 );
			for ( int j=0; j < i; ++j ){
				if ( intersect(R[i][0] , R[i][3] , R[j][0] , R[j][3]) ){
					add( 2*i , 2*j + 1 );
					add( 2*j , 2*i + 1 );
				}
				if( intersect(R[i][0] , R[i][3] , R[j][1] , R[j][2])  ){
					add( 2*i , 2*j );
					add( 2*j + 1 , 2*i + 1 );
				}
				if ( intersect(R[i][1] , R[i][2] , R[j][0] , R[j][3])  ){
					add( 2*i + 1, 2*j + 1 );
					add( 2*j , 2*i );
				}
				if ( intersect(R[i][1] , R[i][2] , R[j][1] , R[j][2])  ){
					add( 2*i + 1 , 2*j );
					add( 2*j + 1 , 2*i );
				}
			}
		}

		n <<= 1; //Duplicate the nodes
		num = 0;
		top = 0;
		SCN = 1;
		fill( number , number + n , -1 );
		fill( inS , inS + n , false );

		for ( int i=0; i < n; ++i ){
			if ( number[i] < 0 ){
				dfs(i);
			}
		}
		n >>= 1;
		bool ok = true;
		for ( int i=0; i < n && ok; ++i ){
			ok &= ( scc[2*i] != scc[(2*i)+1]);
		}
		if (ok) puts("YES");
		else puts("NO");
	}
	
	return 0;
}

