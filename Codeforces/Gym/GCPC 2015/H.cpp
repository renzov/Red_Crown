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

const int MAXN = 512;
int N;
int M = 0;
vector<int> G[MAXN];
map<string, int > idx;
bool vis[MAXN];

int get_id( string &name ){
	if ( idx.find(name) != idx.end() ) return idx[name];
	return idx[name] = M++;
}

int main(){
	string name;
	int K, u, v;
	queue<int> q;

	cin >> N;
	fill( vis, vis + N, false );
	for ( int i=0; i < N; ++i ){
		cin >> name >> K;		
		u = get_id( name );
		// determine if is program
		if ( name.find("::PROGRAM") == name.size() - 9 && name.size() != 8 ){
			vis[u] = true;
			q.push(u);
		}
		for ( int j=0; j < K; ++j ){
			cin >> name;
			G[get_id(name)].push_back(u);
		}
	}
	while ( !q.empty() ){
		u = q.front();
		q.pop();
		for ( int i=0; i < (int)G[u].size(); ++i ){
			v = G[u][i];
			if ( !vis[v] ){
				q.push(v);
				vis[v] = true;
			}
		}
	}
	cout << count( vis, vis + N, false ) << endl;
	return 0;
}

