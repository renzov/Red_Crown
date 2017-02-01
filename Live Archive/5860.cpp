#include<cstdio>
#include<map>
#include<queue>
#include<vector>
using namespace std;
const char UP = 0;
const char DOWN = 1;
vector<int> up[55];
vector<int> down[55];
vector<int> cup[55];
vector<int> cdo[55];
int n;
int H[55];
int C[55];

struct node{
  int u;
  char dir;
  long long mask;
  int w;
  node( int U,char way, long long vis,int di ){ u=U; dir=way; mask=vis; w = di; }
  node(){}
  bool operator<(const node &that) const {
	 return w >= that.w;
  }
};

int dijkstra(){
  
  map<long long , int > d[ 55 ][2];
  
  d[0][UP][1LL] = 0;
  priority_queue< node > q;
  q.push( node( 0 , UP , 1LL , 0 ) );
  int u,v,w,nw;
  char way;
  long long vis,nv;
  puts("AAB");
  while ( !q.empty() ){
	 u = q.top().u; vis = q.top().mask;
	 way = q.top().dir; w = q.top().w;
	 q.pop();
	 if ( d[u][way][vis] < w ) continue;
	 if ( u==0 && way == DOWN ) return w;
	 
	 printf("Caso %d %d %d\n",u,way,w);
	 
	 if ( u == (n-1) && way == UP ){ way = DOWN; }
	 
	 if ( way == UP ){
		for ( int i=0; i < up[u].size(); ++i ){
		  v = up[u][i];
		  nv = vis | (1LL << v);
		  nw = w + cup[u][i];
		  if ( !((vis >> v) & 1) ) nw += C[v];
		  if ( d[v][way].find( nv ) == d[v][way].end() ){
			 d[v][way][nv] = nw;
			 q.push( node( v , way , nv , nw ) );
		  }
		  else if ( d[v][way][nv] > nw ){
			 d[v][way][nv] = nw;
			 q.push( node( v , way , nv , nw ) );
		  }
		}
	 }
	 else {
		for ( int i=0; i < down[u].size(); ++i ){
		  v = down[u][i];
		  nv = vis | (1LL << v);
		  nw = w + cdo[u][i];
		  if ( !((vis >> v) & 1) ) nw += C[v];
		  if ( d[v][way].find( nv ) == d[v][way].end() ){
			 d[v][way][nv] = nw;
			 q.push( node( v , way , nv , nw ) );
		  }
		  else if ( d[v][way][nv] > nw ){
			 d[v][way][nv] = nw;
			 q.push( node( v , way , nv , nw ) );
		  }
		}
	 }
  }
  return -1;
}

int main(){
  int u,v,w;
  int m;
  int cases = 0;
  while ( scanf("%d %d",&n,&m) && n ){
	 cases++;
	 //if ( cases == 25){ printf("%d %d\n",n,m); }
	 C[0] = H[0] = 0;
	 H[n-1] = 1000; C[n-1] = 0;
	 //Init
	 //puts("AA");
	 for ( int i=0; i < n; ++i ){
		up[i].clear(); down[i].clear();
		cup[i].clear(); cdo[i].clear();
	 }
	 for ( int i=1; i < n-1; ++i ){
		scanf("%d %d",C+i,H+i);
		//if ( cases == 25){ printf("%d %d\n",C[i],H[i]); }
	 }
	 //puts("BB");
	 for ( int i=0; i<m; ++i ){
		scanf("%d %d %d",&u,&v,&w);
		//if ( cases == 25) printf("%d %d %d\n",u,v,w);
		u--,v--;
		if ( H[u] <= H[v] ){
		  //up[u][v] = w;
		  up[u].push_back( v );
		  cup[u].push_back( w );
		}
		if ( H[u] >= H[v] ){
		  //down[u][v] = w;
		  down[u].push_back(v);
		  cdo[u].push_back(w);
		}
		//printf("IT = %d\n",i);
	 }
	 //puts("ASA");
	 //puts("SDAS");
	 int res = dijkstra();
	 printf("%d\n",res);
  }
  return 0;
}