#include<queue>
#include<vector>
#include<cstdio>
using namespace std;

int h,w;
int n;
int C;
vector<int> ord;
vector< vector<int> > G;
vector< vector<int> > T;
vector<int> indeg;
vector<int> X;
vector<int> Y;
vector<int> W;
vector<char> visited;
int M[105][105];
int dx[]={1,0,-1,0};
int dy[]={0,-1,0,1};
bool cycle;

inline int abs(int x){ return x<0? -x:x; }

void dfs(int u){
  visited[u] = 1;
  int v;
  for ( int i=0; i < T[u].size() && !cycle; ++i ){
	 v = T[u][i];
	 if ( !visited[v] ) dfs(v);
	 else if ( visited[v] == 1 ) cycle = true;
  }
  visited[u] = 2; 
}

void topsort(){
  priority_queue<int,vector<int>,greater<int> > q;
  int u,v;
  for ( u=0; u < n; ++u ){
	 if ( visited[u] && indeg[u] == 0 ){ 
		  q.push( u );
	 }
  }
  while ( !q.empty() ){
	 u = q.top(); q.pop();
	 printf("%d\n",u);
	 for ( int i=0; i < G[u].size(); ++i ){
		v = G[u][i];
		indeg[v]--;
		if ( visited[v] && indeg[v] == 0 ) q.push( v );
	 }
  }
}

void init(){
  for (int i=0; i < h; ++i)
		for (int j=0; j < w; ++j){
		  M[i][j] = -1;
		}
  T.clear(); visited.clear();
  ord.clear(); G.clear();
  indeg.clear();
  X.clear(); Y.clear(); W.clear();
  G.resize( n );
  indeg.resize( n );
  T.resize(n); visited.resize(n);
  X.resize( n ); Y.resize( n );
  W.resize( n );
}

void set( int u , int x, int y ,int z, int l ){
  for ( int i=0; i < l; ++i ){
	 if ( x < 0 || x >= w || y < 0 || y >= h ) break;
	 M[y][x] = u;
	 y+=dy[z];
	 x+=dx[z];
  }
}

void put_edges( int u , int x , int y ){
  vector<bool> block( n , false );
  int v;
  while ( 1 ){
	 if ( x < 0 || x >= w || y < 0 || y >= h ) break;
	 if ( M[y][x] != -1 && M[y][x] != u ){
		v = M[y][x];
		block[v] = true;
	 }
	 y+=dy[W[u]];
	 x+=dx[W[u]];
  }
  for ( v=0; v<n; ++v ){
	 if ( block[v] ){
		indeg[u]++;
		G[v].push_back(u);
		T[u].push_back(v);
	 }
  }
}

int get_dir( char c ){
  if ( c == 'E' ) return 0;
  if ( c == 'N' ) return 1;
  if ( c == 'W' ) return 2;
  return 3;
}

int main(){
  int u;
  int l;
  char dir;
  int cases = 0;
  while ( scanf("%d %d",&w,&h) != EOF ){
	 cases++;
	 scanf("%d",&n);
	 scanf("%d",&C);
	 init();
	 for (int i=0; i < n; ++i){
		 visited[i] = 0;
		 scanf("%d %d %d %c",&X[i],&Y[i],&l,&dir);
		 W[i] = get_dir( dir );
		 set( i , X[i] , Y[i] , W[i] , l );
	 }
	 for ( int i=0; i<n; ++i ){
		put_edges( i , X[i] , Y[i] );
	 }
	 cycle = false;
	 for ( int j=C; j <= C+1 && !cycle; ++j )
		 for ( int i=0; i < h && !cycle; ++i ){
			 if ( M[i][j] != -1 && !visited[ M[i][j] ] ){
				dfs( M[i][j] );
			 } 
		 }
	 if ( cases > 1 ) putchar('\n');
	 if ( cycle ) puts("Jammed");
	 else topsort();
  }
  return 0;
}