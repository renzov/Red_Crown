#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
#include<climits>
using namespace std;
const int MAXN = 1005;
#define forn(i,n) for(int i=0; i < (int)(n); ++i)
vector<int> G[MAXN];
vector<int> C[MAXN];
vector<int> S[MAXN];
int d[ MAXN ];
int n;
int T;
bool dijkstra(int maxs){
  fill(d,d+n,INT_MAX);
  d[0] = 0;
  priority_queue< pair<int,int> , vector< pair<int,int> > , greater< pair<int,int> > > q;
  q.push( make_pair(0,0) );
  int u,v,w,s;
  while ( !q.empty() ){
	 u = q.top().second; w = q.top().first;
	 q.pop();
	 if ( d[u] < w ) continue;
	 if ( u == (n-1) ) return ( d[u] <= T );
	 forn(i,G[u].size()){
		v = G[u][i]; s = S[u][i]; w = C[u][i];
		if ( s <= maxs && (d[v] > ( d[u]+w )) ){
		  d[v] = d[u] + w;
		  q.push( make_pair( d[v] , v ) );
		}
	 }
  }
  return false;
}

int main(){
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  int u,v,w,s;
  int maxs;
  int best;
  int m;
  scanf("%d %d",&n,&m);
  maxs = 0;
  forn(i,m){
	 scanf("%d %d %d %d",&u,&v,&w,&s);
	 u--,v--;
	 maxs = max(maxs,s);
	 G[u].push_back(v); C[u].push_back(w); S[u].push_back(s);
	 G[v].push_back(u); C[v].push_back(w); S[v].push_back(s);
  }
  scanf("%d",&T);
  if ( !dijkstra(maxs) ){ puts("NO"); }
  else {
	 best = d[n-1];
	 puts("YES");
	 if ( dijkstra(1)) {
		printf("0 %d\n",d[n-1]);
	 }
	 else {
		int r = maxs;
		int l = 1;
		int mid;
		while ( (r-l) > 1 ){
		  mid = (l+r) >> 1;
		  if ( dijkstra(mid) ){
			 best = d[n-1];
			 r = mid;
		  }
		  else {
			 l = mid;
		  }
		}
		printf("%d %d\n",r,best);
	 }
  }
  return 0;
}