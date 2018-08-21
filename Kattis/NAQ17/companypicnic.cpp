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
const int MAXN = 1024;
int N;

int S[MAXN];
map<string, int> H;
vector<int> T[MAXN];
int idx = 0;

int M[MAXN][2];
int V[MAXN][2];

inline int get_id( const string &s ){
	return ( H.count(s) )? H[s]:( H[s] = idx++ );
}

int get_vel( const string &s ){
	int res = 0;
	bool dot = false;
	int cnt = 3;

	for ( int i=0; i < (int)s.size(); ++i ){
		if (dot) cnt--;		
		if ( isdigit( s[i] ) ) res = res*10 + (s[i] - '0'); 
		else dot = true;
	}
	while ( cnt-- ) res *= 10;
	return res;
}

int dfs( const int &u ){
	int sum = 0;
	int val = 0;
	int v;
	
	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		dfs( v );
		sum += M[v][0];
		val += V[v][0];
	}

	M[u][0] = M[u][1] = sum;
	V[u][0] = V[u][1] = val;
	int match;
	int vmatch;
	// We try matching u to a child
	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		match = 1 + sum - M[v][0] + M[v][1];
		vmatch = min( S[u], S[v] ) + val - V[v][0] + V[v][1];
		if ( M[u][0] < match ){
			M[u][0] = match;
			V[u][0] = min( S[u], S[v] ) + val - V[v][0] + V[v][1];
		}
		else if ( M[u][0] == match && V[u][0] < vmatch ){
			V[u][0] = vmatch;
		}
	}
}

int main(){
	int u, v, root;
	string name1, name2, str;
	cin >> N;
	H["CEO"] = -1;

	for ( int i=0; i < N; ++i ){
		cin >> name1 >> str >> name2;
		v = get_id( name1 );
		u = get_id( name2 );
		S[v] = get_vel( str );
		if ( u == -1 ){
			root = v;
		}
		else {
			T[u].push_back( v );
		}
	}
	dfs( root );
	printf("%d %.5f\n", M[root][0], (double)V[root][0] / ( M[root][0] * 1000 ) );
	return 0;
}

