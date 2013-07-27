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

int r,s,d;
vector<int> G[ 20 ];
vector<int> L[ 20 ];
pii pred[1 << 11][ 11 ];
int D[ 1 << 11 ][ 11 ];
void init(){
	for ( int i=0; i < r; ++i ){
		G[i].clear();
		L[i].clear();
	}
	for ( int i=0; i < (1<<r) ; ++i )
		for ( int j=0; j < r; ++j )
			D[i][j] = -1;
}

int bit(int m){
	for ( int i=0; i < r; ++i )
		if ( (m >> i) & 1 )
			return i;
	puts("ERROR");
	return -1;
}

void print_sol( int state , int room ){
	if ( state == 1 && room == 0 ) return;
	print_sol( pred[ state ][ room ].first , pred[ state ][ room ].second );
	if ( state == pred[ state ][ room ].first ){ //Change in room
		printf("- Move to room %d.\n",room + 1);
	}
	else { //Change in switch
		int mask = state ^ pred[ state ][ room ].first;
		if ( state & mask ){
			printf("- Switch on light in room %d.\n",bit(mask) + 1);
		}
		else {
			printf("- Switch off light in room %d.\n",bit(mask) + 1);
		}
	}
}

int bfs(){

	int end = 1<<(r-1);
	D[ 1 ][ 0 ] = 0;
	queue< pii > q;
	q.push( make_pair( 1 , 0 ) );
	int state,next;
	int u,v;
	
	while ( !q.empty() ){
		state = q.front().first;
		u = q.front().second;
		q.pop();
		if ( u == (r - 1) && state == end ) return D[ state ][ u ];
		//Trying to move
		for ( int i=0; i < G[u].size(); ++i ){
			v = G[u][i];
			if ( (state & (1<<v)) && (D[state][v] == -1) ){
				D[state][v] = D[state][u] + 1;
				pred[state][v] = make_pair( state , u );
				q.push( make_pair( state , v ) );
			}
		}
		//Trying to swicth lights;
		for ( int i=0; i < L[u].size(); ++i ){
			v = L[u][i];
			next = state ^ ( 1 << v );
			if ( v != u && D[next][u] == -1 ){
				D[next][u] = D[state][u] + 1;
				pred[next][u] = make_pair( state , u );
				q.push( make_pair( next , u ) );
			}
		}
	}
	return -1;
}

int main(){
	int u,v;
	int runs = 0;
	while ( scanf("%d %d %d",&r,&d,&s) && ( r || d || s ) ){
		runs++;
		init();
		for ( int i=0; i < d; ++i ){
			scanf("%d %d",&u,&v);
			u--,v--;
			G[u].push_back(v);
			G[v].push_back(u);
		}
		for ( int i=0; i < s; ++i ){
			scanf("%d %d",&u,&v);
			u--,v--;
			L[u].push_back(v);
		}
		int res = bfs();
		printf("Villa #%d\n",runs);
		if ( res != -1 ){
			printf("The problem can be solved in %d steps:\n",res);
			print_sol( 1 << (r-1) , r - 1 );
		}
		else {
			puts("The problem cannot be solved.");
		}
		puts("");
	}
	return 0;
}

