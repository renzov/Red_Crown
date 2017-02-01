#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> G[ 120 ];

int a[120][3];
bool visited[ 120 ];
int best[ 120 ];

inline bool cover(int x,int y){
  return a[ x ][ 0 ] > a[ y ][ 0 ] && a[ x ][ 1 ] > a[ y ][ 1 ];
}

int dfs(int u){
  visited[u] = true;
  int v;
  int b = 0;
  for (int i=0; i < G[u].size(); ++i){
	 v = G[u][i];
	 if (!visited[ v ]) dfs(v);
	 if ( (best[v] + a[v][2]) > b ) b = best[v] + a[v][2]; 
  }
  best[ u ] = b;
  return best[ u ];
}

int main(){
  int p;
  int n;
  int runs = 0;
  int x,y,z;
  while (scanf("%d",&n) && n){
		runs++;
		p = 0;
		for (int i=0; i < n; ++i){
		  scanf("%d %d %d",&x,&y,&z);
		  if (x > y) swap(x,y);
		  if (x > z) swap(x,z);
		  if (y > z) swap(y,z);
		  visited[ p ] = false;
		  G[ p ].clear();
		  a[p][0] = x; a[p][1] = y; a[p][2] = z; ++p;
		  visited[ p ] = false;
		  G[ p ].clear();
		  a[p][0] = x; a[p][1] = z; a[p][2] = y; ++p;
		  visited[ p ] = false;
		  G[ p ].clear();
		  a[p][0] = y; a[p][1] = z; a[p][2] = x; ++p;
		}
		/* Create a graph */
		n = p;
		for (int i=0; i < n-1; ++i){
		  for (int j=i+1; j < n; ++j){
				if ( cover(i,j) ){
					 G[ i ].push_back( j );
				}
				else if ( cover(j,i) ){
					 G[ j ].push_back( i );
				}
		  }
		}
		int res = 0;
		for (int i=1; i < n; ++i){
		  if (!visited[i]) dfs( i );
		  if (res < (best[i] + a[i][2])){ res = best[i] + a[i][2]; }
		}
		printf("Case %d: maximum height = %d\n",runs,res);
  }
  return 0;
}