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
const int MAXV = 10000;

vector< int > G[MAXV];
int L,W;
int l,w;
int ncomp,cnt;
int num[MAXV];
int low[MAXV];
bool in[MAXV];
int cmp[MAXV];
stack<int> S;
/* 
	from 0 ... l - 1 	 	 positive row variables
	from l ... L - 1 	 	 negative row variables
	from L ... L + w - 1 	 postive column variables
	from L + w ... L + W - 1 negative column variables
*/
int inv( int x ){
	if ( x < l ) return x + l;
	if ( x < L ) return x - l;
	if ( x < (L + w) ) return x + w;
	return x - w;
}

void add( int r1 , int c1 , int r2 , int c2 ){
	//The clause (r1 and r2) or (r2 and c2) is equivo
	//Adding clause (r1 or r2)
	G[inv(r1)].push_back(r2); G[inv(r2)].push_back(r1);
	// Adding clause (r2 or c1)
	G[inv(r2)].push_back(c1); G[inv(c1)].push_back(r2);
	//Adding clause (r1 or c2)
	G[inv(r1)].push_back(c2); G[inv(c2)].push_back(r1);
	//Adding clause (c1 or c2)
	G[inv(c1)].push_back(c2); G[inv(c2)].push_back(c1);
}

void dfs( int u ){
	num[u] = low[u] = cnt++;
	S.push(u); in[u] = true;
	int v;
	for ( int i=0; i < G[u].size(); ++i ){
		v = G[u][i];
		if ( num[v] == -1 ){
			dfs(v);
			low[u] = min( low[u] , low[v] );
		}
		else if ( in[v] ){
			low[u] = min( low[u] , num[v] );
		}
	}
	if ( num[u] == low[u] ){
		do{
			v = S.top(); S.pop();
			in[v] = false;
			cmp[v] = ncomp;
		}
		while (u != v);
		ncomp++;
	}
}

void find_scc(){
	ncomp = cnt = 0;
	for ( int i=0; i<(L+W); ++i ){
		num[i] = -1;
		in[i] = false;
	}
	while ( !S.empty() ) S.pop();

	for ( int i=0; i < (L+W); ++i )
		if ( num[i]==-1 ) dfs(i);
}

bool two_sat(){
	find_scc();
	for ( int i=0; i < l; ++i )
		if ( cmp[i] == cmp[i+l] ) return false;
	for ( int i=L; i < (L+w) ; ++i )
		if ( cmp[i] == cmp[i+w] ) return false;
	return true;
}

int main(){
	int runs;
	int m;
	int x1,x2,y1,y2;
	int r1,r2,c1,c2;
	scanf("%d",&runs);
	while ( runs-- ){
		scanf("%d %d %d",&l,&w,&m);
		L = 2*l; W = 2*w;

		for ( int i=0; i < (L + W); ++i ) G[i].clear();

		while ( m-- ){
			scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
			if ( x1 == x2 && y1 == y2 ) continue;
			y1 = y1 + L - 1; y2 = y2 + L - 1;
			x1 = x1 - 1; x2 = x2 - 1;
			
			r1 = x1, r2 = x2;
			if ( y1 > y2 ){ r1 = inv(r1); r2 = inv(r2); }
			c1 = y1, c2 = y2;
			if ( x1 > x2 ){ c1 = inv(c1); c2 = inv(c2); }

			if ( x1 != x2 && y1 != y2 ){
				add( r1 , c2 , r2 , c1 );
			}
			else if (x1 != x2){
				G[ inv(c1) ].push_back( c1 );
			}
			else { // y1 != y2
				G[ inv(r1) ].push_back( r1 );
			}
		}
		if ( two_sat() ) puts("Yes");
		else puts("No");
	}
	return 0;
}

