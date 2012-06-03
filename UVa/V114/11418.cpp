#include<iostream>
#include<cctype>
#include<set>
#include<cstring>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

#define forn(i,n) for (int i = 0; i < (int)(n); ++i)
vector<string> s;
int n;
bool visited[50];
vector<int> G[50];
int LA[50];
int RA[50];
int M[50][50];

bool Alternate_Path( int u ){
  int v;
  forn(i,G[u].size()){
	 v = G[u][i];
	 if ( visited[v] ) continue;
	 visited[v] = true;
	 if ( RA[v] < 0 || Alternate_Path( RA[v] ) ){
		RA[v] = u; LA[u] = v;
		return true;
	 }
  }
  return false;
}

void formalize(string &w){
  w[0] = toupper(w[0]);
  for( int i=1; i < w.size(); ++i )
	 w[i] = tolower( w[i] );
}

int main(){
  int runs;
  int m;
  string w;
  int idx;

  cin >> runs;
  forn(k,runs){
	 s.clear();
	 cin >> n;
	 forn(i,n){
		cin >> m;
		G[i].clear(); LA[i] = -1; RA[i] = -1;
		forn(j,m){
		  cin >> w;
		  formalize(w);
		  if ( (w[0] - 'A') >= n ) continue;
		  s.push_back(w);
		  idx = w[0] - 'A';
		  G[i].push_back( idx );
		  M[i][idx] = s.size()-1;
		}
	 }
	 forn(i,n){
		fill(visited,visited+n,false);
		Alternate_Path(i);
	 }
	 cout << "Case #" << (k+1) << ":\n";
	 set<string> S;
	 forn(i,n){
		S.insert( s[ M[i][ LA[i] ] ] );
	 }
	 for ( set<string>::iterator it = S.begin(); it!=S.end(); it++ )
		cout << *it << "\n";
  }
  return 0;
}