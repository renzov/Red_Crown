#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
#include<map>
#include<queue>
#include<algorithm>
using namespace std;
map<string,int> H;
int n;
vector<string> W;
vector<int> pre;

void print( int v ){
  if ( v == 0 ){
	 cout << W[v] << endl;
  }
  else {
	 print( pre[v] );
	 cout << W[v] << endl;
  }
}

struct node {
  int idx;
  node *edge[26];
  node(){ idx = 0; 
	 for (int i=0; i < 26; ++i) edge[i] = NULL;
  }
};

struct Trie {
  node *root;
  Trie(){
	 root = new node();
  }
  void insert( string &word , int pos ){
	 node *act = root;
	 int where;
	 for ( int i=0; i < word.size(); ++i ){
		where = word[i] - 'a';
		if ( act->edge[where] == NULL ) act->edge[where] = new node();
		act = act->edge[where];
	 }
	 act->idx = pos;
  }
  int search( string &word ){
		node *act = root;
		int where;
		for ( int i=0; i < word.size(); ++i ){
		  where = word[i] - 'a';
		  if ( act->edge[where] == NULL ) return 0;
		  act = act->edge[where];
		}
		return act->idx;
  }
};

Trie t;

int main(){
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  scanf("%d",&n);
  W.resize(n);
  char s[ 100 ];
  vector< vector<int> > G(n);
  for ( int i=0; i < n; ++i ){
	 scanf("%s",s);
	 W[i] = s;
	 t.insert( W[i] , i+1 );
  }
  string tmp;
  char act;
  int v;
  for ( int i=0; i < n; ++i ){
	 tmp = W[i];
	 for ( int j=0; j < tmp.size(); ++j ){
		act = tmp[j];
		for ( char cc='a'; cc <= 'z' ; ++cc ){
		  if ( cc != act ){
			 tmp[j] = cc;
			 if ( v = t.search(tmp) ){
				G[i].push_back( v-1 );
			 }
		  }
		}
		tmp[j] = act;
	 }
  }
  vector<int> d( n  , 0 );
  pre.resize( n );
  fill( pre.begin() , pre.end() , -1 );
  d[ 0 ] = 1;
  queue< int > q;
  int u;
  q.push( 0 );
  while ( !q.empty() ){
	 u = q.front(); q.pop();
	 for ( int i=0; i<G[u].size(); ++i ){
		v = G[u][i];
		if ( d[v] == 0 ){
		  d[v] = d[u] + 1;
		  pre[v] = u;
		  q.push(v);
		}
	 }
  }
  if ( d[n-1] ){
	 cout << d[n-1] << endl;
	 print( n-1 );
  }
  else {
	 cout << "FAIL" << endl;
  }
  return 0;
}