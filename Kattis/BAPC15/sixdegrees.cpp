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

const int MAXN = 3005;
vector<int> G[MAXN];
int d[MAXN][MAXN];
int ecc[MAXN];
map<string, int> id;
int N = 0;

void clear_mem(){
	id.clear();
	for ( int i=0; i < N; ++i ) G[i].clear();
	N = 0;
}

int get_id( string &x ){
	return ( id.find(x) != id.end() )? id[x]:( id[x] = N++ );
}

void bfs( int s, int *D ){
	D[s] = 0;
	ecc[s] = 0;
	queue<int> q;
	q.push(s);
	int u, v; 
	while ( !q.empty() ){
		u = q.front();
		q.pop();
		for ( int i=0; i < (int) G[u].size(); ++i ){
			v = G[u][i];
			if ( D[v] == -1 ){
				D[v] = D[u] + 1;
				ecc[s] = max( ecc[s] , D[v] );
				q.push( v );
			}
		}
	}
}

int main(){
	int M;
	int runs;
	int u, v;
	string name1, name2;

	cin >> runs;
	while ( runs-- ){
		cin >> M;
		for ( int i=0; i < M; ++i ){
			cin >> name1 >> name2;
			u = get_id(name1), v = get_id(name2);
			G[u].push_back(v), G[v].push_back(u);
		}
		// Clear the distance matrix
		for ( int i=0; i < N; ++i ) 
			for ( int j=0; j < N; ++j )
				d[i][j] = -1;
		// Find shortests path from every vertex 
		for ( int i=0; i < N; ++i )
			bfs( i , d[i] );

		// Calculate the number of elements that have eccentricity >= 7
		int bad = 0;
		for ( int i=0; i < N; ++i ) 
			if ( ecc[i] >= 7 ) bad++;

		if ( bad*100 <= 5*N ) cout << "YES" << endl;
		else cout << "NO" << endl;

		if ( runs ) clear_mem();	
	}
	return 0;
}

