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

vector<int> G[ 10 ];
int pot[10];

void add(int u,int v){ G[u].push_back(v); G[v].push_back(u); }

void init(){
	add(0,2); add(0,4); add(0,6);
	add(1,2); add(1,6); add(5,6);
	add(2,3); add(3,4); add(4,5);
	int p = 1;
	for ( int i=6; i >= 0 ; --i ){
		pot[ i ] = p; p*= 10;
	}
}

map< int, int > res;

int calc(int s,int u,int v){
	int dv = (s / pot[v]) % 10;
	s += dv * pot[u];
	s -= dv * pot[v];
	return s;
}

void bfs(){
	int d;
	int u,v,next;
	int state;
	res[ 123456 ] = 1;
	queue< pii > q;
	q.push( make_pair(123456,0) );
	while ( !q.empty() ){
		state = q.front().first; u = q.front().second;
		q.pop();
		d = res[state];
		for ( int i=0; i < G[u].size(); ++i ){
			v = G[ u ][ i ];
			next = calc( state , u , v );
			int &ref = res[next];
			if ( !ref ){ ref = d + 1; q.push( make_pair(next,v)); }
		}
	}
}

int main(){
	init();
	bfs();
	int s;
	int n;
	int p;
	scanf("%d",&n);
	while ( n-- ){
		scanf("%d",&s);
		p = res[s];
		if ( !p ) puts("-1");
		else printf("%d\n",p-1);
	}
	return 0;
}

