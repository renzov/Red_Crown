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
const int MAXN = 128;
const int MAXW = 2*1000005;
int d[MAXW];
int g[MAXN];
int C[MAXN];
int N;
int M;

void bfs(){
	fill( d, d + M, -1 );
	d[0] = 0;
	queue<int> q;
	q.push( 0 );
	
	int u, v;
	while ( !q.empty() ){
		u = q.front(); q.pop();
		for ( int i=0; i < N; ++i ){
			v = u + C[i];
			if ( v < M && d[v] < 0 ){
				d[v] = d[u] + 1;
				q.push(v);
			}
		}
	}
}


int main(){	
	cin >> N;
	for ( int i=0; i < N; ++i ) cin >> C[i]; 
	M = C[N-1] + C[N-2];
	bfs();
	bool ok = true;
	int cnt;
	g[0] = 0, g[1] = 1;
	for ( int i=2, j=0; i < M && ok; ++i ){
		while ( j < (N - 1) && i >= C[j + 1] ) j++;
		cnt = i / C[j];
		g[i] = g[ i%C[j] ] + cnt;
		ok = g[i] == d[i];
	}
	if (ok) cout << "canonical" << endl;
	else cout << "non-canonical" << endl;
	return 0;
}

