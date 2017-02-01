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

/* 
	Note: ( p xor q ) = ( ~p or ~q ) and ( p or q )
	- Each wife of couple i is associanted with variable x_i and each husband with ~x_i.
*/ 

const int MAXN = 1000;

vector<int> G[MAXN];

int cmp[MAXN];
int num[MAXN];
int low[MAXN];
bool in[MAXN];
int cnt,ncomp;
int N,n;
stack<int> S;

int value[MAXN];
int rep[ MAXN ];

inline int inv( int x ){ //Returns the id of the dual variable
	return (x < n)? (x + n):(x - n);
}

void dfs( int u ){
	low[u] = num[u] = cnt++;
	S.push(u); in[u] = true;

	int v;
	for ( int i=0; i < G[u].size(); ++i ){
		v = G[u][i];
		if ( num[v] == -1 ){
			dfs( v );
			low[u] = min( low[u] , low[v] );
		}
		else if ( in[v] ){
			low[u] = min( low[u] , num[v] );
		}
	}
	
	if ( low[u] == num[u] ){
		rep[ ncomp ] = u; // we choose one vertex to represent the scc
		do {
			v = S.top(); S.pop();
			in[v] = false;
			cmp[v] = ncomp;
		}
		while ( v != u );
		ncomp++;
	}
}

void find_scc(){
	cnt = ncomp = 0;
	for ( int i=0; i < N; ++i ){
		in[i] = false;
		num[i] = -1;
	}
	while ( !S.empty() ) S.pop();

	for ( int i=0; i < N; ++i )
		if ( num[i] == -1 ) dfs(i);

}

bool two_sat(){

	find_scc();
	//Check that no literal an its negagation are in the same scc
	for ( int i=0; i < n; ++i )
		if ( cmp[ i ] == cmp[ i + n ] ) return false;
	/* 	
		Finding a truth assignment to the components
	   	Important : The SCC found by the algorithm are numbered in reverse
	 	topological order
	*/
	fill( value , value + ncomp , -1 );

	int j;
	
	for ( int i=0; i < ncomp; ++i ){
		if ( value[ i ] == -1 ){
			value[ i ] = 1; 	//true
			// finding dual comp
			j = cmp[ inv(rep[i]) ];
			value[ j ] = 0; 	//false
		}
	}
	return true;
}

void add( int x , int y ){
	// Adding the edges that represent (x or y)
	// in the implication graph
	int nx = inv(x);
	int ny = inv(y);
	G[nx].push_back(y);
	G[ny].push_back(x);
}

int read(){
	char s[10];
	char t;
	int l;
	int v;
	scanf("%s",s);
	l = strlen(s);
	t = s[l-1]; s[l-1] = '\0';
	sscanf( s , "%d" , &v );
	if ( t == 'w' ) return v;
	return v + n;
}

int main(){
	int x,y;
	int m;
	while ( scanf("%d %d",&n,&m) && n ){
		
		N = 2*n;
		
		for ( int i=0; i < N; ++i )
			G[i].clear();

		while ( m-- ){
			x = read();	
			y = read();
			add( x , y );
		}
		
		G[inv(0)].push_back(0);

		if ( two_sat() ){
			for ( int i=1; i < n; ++i ){
				if ( i > 1 ) putchar(' ');
				if ( value[cmp[i]] == value[cmp[0]] ) printf("%dw",i);
				else printf("%dh",i);
			}
			puts("");
		}
		else {
			puts("bad luck");
		}
	}
	return 0;
}

