#include<iostream>
#include<climits>
#include<vector>
#include<map>
#include<cstring>
#include<string>
#include<sstream>
#include<algorithm>
using namespace std;
int n,m;
int c;

vector<int> G[205];
map<string,int> H;
int indeg[205];
int S[205];
int T[205];

void init(){
  for ( int i=0; i <= n; ++i ){ G[i].clear(); indeg[i] = 0; }
  H.clear();
}

int get_id( string &s ){
  if ( H.find( s ) == H.end() ) H[ s ] = c++;
  return H[s];
}

void dfs( int u,int *best ){
  int v;
  int tmp[205];
  best[0] = 0;
  S[u] = 1;
  for ( int i=0; i < G[u].size(); ++i ){
	 v = G[u][i];
	 for ( int j=1; j <= n; ++j ) tmp[j] = INT_MAX;
	 dfs( v , tmp );
	 S[u] += S[v];
	 for ( int j=n;  j >= 1 ; --j ){
		for ( int k=0; k <= j; ++k ){
		  if ( best[k] != INT_MAX && tmp[j-k] != INT_MAX )
			 best[j] = min( best[j] , best[k] + tmp[j-k] );
		}
	 }
  }
  if ( u != 0 )
	 best[ S[u] ] = min( best[ S[u] ] , T[u] );
}

int main(){
  string line;
  int u,v;
  string s;

  while ( 1 ){
	 getline( cin, line );
	 if ( line[0] == '#' ) break;
	 stringstream is(line);
	 is >> n >> m;
	 c = 1;
	 init();
	 for ( int i=0;  i < n; ++i ){
		getline(cin,line);
		stringstream in(line);
		in >> s;
		u = get_id( s );
		in >> T[u];
		while ( in >> s ){
		  v = get_id(s);
		  G[u].push_back( v );
		  indeg[v]++;
		}
	 }
	 if ( m == 0 ){
		cout << 0 << endl;
		continue;
	 }
	 for ( int i = 1; i <= n; ++i ){
		if ( !indeg[i] ) G[0].push_back( i );
	 }
	 int best[205];
	 for ( int i=1; i <= n; ++i ) best[i] = INT_MAX;
	 dfs( 0 , best );
	 int res = INT_MAX;
	 for ( int i=m; i <= n; ++i ){
		if ( res > best[i] ) res = best[i];
	 }
	 cout << res << endl;
  }
  return 0;
}