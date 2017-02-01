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

const int MAXN = 105;

vector<int> G[2*MAXN];
bool vis[2*MAXN];

void dfs(int u){
	vis[u] = true;
	int v;
	for (int i=0; i < G[u].size(); ++i){
		v = G[u][i];
		if (!vis[v]) dfs(v);
	}
}

int main(){
	int N,M,K;
	int c;

	while (scanf("%d %d %d", &M, &N, &K) != EOF){
		for (int i=0; i < (N+M); ++i){ 
			G[i].clear();
			vis[i] = false;
		}

		for ( int i=0; i < M; ++i ){
			for (int j=0; j < N; ++j){
				scanf("%d",&c);
				if (c==0){
					G[i].push_back(j + M);
					G[j+M].push_back(i);
				}
			}
		}

		int comp = 0;
		for ( int i=M; i<(N+M) && comp <= K; ++i ){
			if (G[i].size() == 0) comp = 10000;
			else if (!vis[i]){
				dfs(i);
				comp++;
			}
		}
		if (comp <= K) puts("yes");
		else puts("no");
	}
	return 0;
}

