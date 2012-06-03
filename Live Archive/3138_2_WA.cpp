#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
vector<int> T[ 1002 ];
vector< vector<int> > L;

int C[1002];
int indeg[1002];


int main(){
  int n,r;
  int u,v,w,t;
  int res;
  while ( scanf("%d %d",&n,&r) && n ){
	 r--;
	 //Init
	 for (int i=0; i < n; ++i){ T[i].clear(); indeg[i] = 0; }
	
	 for (int i=0; i < n; ++i) scanf("%d",C+i);
	 for (int i=0; i < n-1; ++i){
		scanf("%d %d",&u,&v);
		u--,v--;
		T[u].push_back(v);
		indeg[v]++;
	 }
	 res = 0;
	 t = 0;
	 priority_queue< pair<int,int> > q;
	 q.push( make_pair( C[r] , r ) );
	 while ( !q.empty() ){
		u = q.top().second;
		w = q.top().first;
		q.pop();
		t++;
		res += t*C[u];
		for ( int i=0; i < T[u].size(); ++i ){
		  v = T[u][i];
		  indeg[v]--;
		  if ( !indeg[v] ) q.push( make_pair( C[v] , v ) );
		}
	 }
	 printf("%d\n",res);
  }
  return 0;
}