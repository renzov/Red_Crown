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

const int MAXE = 20005;
int p[1005];

struct edge {
	int u,v,w;
	edge(int U,int V, int W){
		u = U, v = V, w = W;
	}
	bool operator<(const edge &that) const {
		return w < that.w;
	}
	edge(){}
};

edge E[MAXE];

void make_set( int x ){ p[x] = x; }
int find_set( int x ){ return (x == p[x])? x:(p[x] = find_set(p[x])); };
void link( int x, int y ){
	x = find_set(x);
	y = find_set(y);
	p[x] = y;
}

int main(){

	int M,N;
	int u,v,w;
	int res;

	scanf("%d %d",&N,&M);

	for ( int i=0; i < M; ++i ){
		scanf("%d %d %d",&E[i].u,&E[i].v,&E[i].w);
	}
	
	sort( E , E + M );

	for ( int i=1; i <= N; ++i ) make_set(i);
	res = 0;
	int j = N - 1;
	for ( int i=M-1; i >= 0 && j > 0 ; --i ){
		u = E[i].u, v = E[i].v;
		w = E[i].w;
		if ( find_set(u) != find_set(v) ){
			link( u , v );
			res += w;
			j--;
		}
	}
	if ( j > 0 ) puts("-1");
	else printf("%d\n",res);
	return 0;
}

