#include<cstdio>
#include<map>
#include<string>
#include<cctype>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

map<string,int> H;
char line[1<<20];
int n,m;
int cnt;
int W[105];
char s[20];
int p;
char name[100001][20];
vector<int> G[100001];
int cases = 0;

int get_word(){
  if ( !line[p] ) return 0;
  int t = 0;
  while ( line[p] && isalpha( line[p] ) ){ s[t++] = line[p]; p++; }
  while ( line[p] && !isalpha( line[p] ) ) p++;
  s[t] = 0;
  return 1;
}

int get_id(){
  if ( H.find( s ) == H.end() ){ 
		strcpy( name[cnt] , s );
		H[s] = cnt++;
		return cnt-1;
  }
  else return H[s];
}

void bfs(){
  vector< pair< string , vector<string> > > out(n);
  for (int i=0; i < n; ++i) out[i].first = name[ W[i] ];
  queue< pair<int,int> > q;
  vector< vector<int> > d( n , vector<int>(m,-1) );
  for (int i=0; i < n; ++i){
	 d[ i ][ W[i] ] = 0;
	 q.push( make_pair( i , W[i] ) );
  }
  int u,v,w;
  while ( !q.empty() ){
	 u = q.front().first; v = q.front().second;
	 q.pop();
	 if ( d[u][v] > 1 ) out[ u ].second.push_back( name[v] );
	 for (int i=0; i < G[ v ].size(); ++i){
		w = G[v][i];
		if ( d[u][w] == -1 ){
		  d[u][w] = d[u][v] + 1;
		  q.push( make_pair(u,w) );
		}
	 }
  }
  for (int i=0; i < n; ++i){
	 sort( out[i].second.begin() , out[i].second.end() );
  }
  sort( out.begin() , out.end() );
  printf("--- CASE %d\n",cases);
  for (int i=0; i < n; ++i){
	 if ( out[i].second.size() ){
		printf("%s",out[i].first.c_str());
		for (int j=0; j < out[i].second.size(); ++j)
		  printf(" %s",out[i].second[j].c_str());
		putchar('\n');
	 }
  }
}

int main(){
  int v;
  while (1){
	 // Init
	 H.clear();
	 for (int i=0; i < n; ++i) G[ W[i] ].clear();
	 gets(line);
	 sscanf(line,"%d %d",&m,&n);
	 if ( !n ) break;
	 cases++;
	 cnt = 0;
	 for (int i=0; i < n; ++i){
		  gets(line);
		  p = 0;
		  get_word();
		  W[i] = get_id();
		  while ( get_word() ){
			 v = get_id();
			 G[ W[i] ].push_back( v ); 
		  }
	 }
	 bfs();
  }
  return 0;
}