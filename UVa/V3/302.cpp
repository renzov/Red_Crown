#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
bool visited[50];
int deg[50];
pair<int,int> E[2000];
bool used[2000];
int sol[2000];
vector<int> G[50];
int m;
int n;
int k;
int start;

bool backtrack( int u, int remain ){
	if (!remain) return u==start;
	if ( u == start && deg[start] == 1 ) return false;
	int e,v;
	for ( int i=0; i < G[u].size(); ++i ){
		e = G[u][i];
		if ( used[e] ) continue;
		if ( E[e].first == u ) v = E[e].second;
		else v = E[e].first;
		if ( remain > 1 && deg[v] > 1 ){
			used[e] = true;
			deg[u]--,deg[v]--;
			if ( backtrack(v,remain-1) ){
				sol[k++] = e;
				return true;
			}
			used[e] = false;
			deg[u]++,deg[v]++;
		}
		else if ( remain == 1 && v == start ){
			used[e] = true;
			deg[u]--,deg[v]--;
			if ( backtrack(v,remain-1) ){
				sol[k++] = e;
				return true;
			}
			used[e] = false;
			deg[u]++,deg[v]++;
		}

	}
	return false;
}

int main(){
	int u,v,w;
	while ( scanf("%d %d",&u,&v) && ( u && v ) ){
		for ( int i=0; i < 50; ++i ) G[i].clear();
		fill( deg , deg + 50 , 0 );
		scanf("%d",&w);
		m = w; n = max(u,v);
		u--,v--,w--;
		start = min(u,v);
		deg[u]++; deg[v]++;
		E[ w ].first = u; E[ w ].second = v;
		G[u].push_back(w); G[v].push_back(w);
		while ( scanf("%d %d",&u,&v) && ( u && v ) ){
			scanf("%d",&w);
			m = max(w,m); n = max(n,max(u,v));
			u--,v--,w--; 
			deg[u]++; deg[v]++; 
			E[w].first = u; E[w].second = v;
			G[u].push_back(w); G[v].push_back(w); 
		}
		bool ok = true;
		for ( int i=0; i < n && ok; ++i ){
			if ( deg[i] & 1 ){ ok = false; }
		}
		if ( !ok ){
			puts("Round trip does not exist.\n");
		}
		else {
			for ( int i=0; i < n; ++i ) sort( G[i].begin() , G[i].end() );
			k = 0;
			fill(used,used+m,false);
			backtrack(start,m);
			for ( int i=k-1; i >= 0; --i ){
				printf("%d",sol[i]+1);
				if (i) putchar(' ');
			}
			puts("\n");
		}
		
	}
	return 0;
}
