#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int MAX = 201;
const int MAXE = 1005;

vector<int> G[MAX];
bool seen[MAX];
int hole[MAXE];
int n,m,t;
int deg[MAX];
pair<int,int> E[MAXE];

int nc;
int p[MAX];
inline void make_set( int x ){ p[x] = x; }
inline int find_set(int x){ return x==p[x]? x:( p[x] = find_set(p[x]) ); }
void link( int x, int y ){
	int X = find_set(x);
	int Y = find_set(y);
	if ( X == Y ) return;
	p[ Y ] = X;
	nc--;
}

void init(){
	for ( int i=0; i < n; ++i ){
		G[i].clear();
		make_set(i);
	}
	fill( deg , deg + n , 0 );
	fill( hole , hole + m , -1 );
	nc = n;
	t = 0;
}

void read_input(){
	int u,v,d;
	for ( int i=0; i < m; ++i ){
		scanf("%d%d%d",&u,&v,&d);
		u--,v--;
		link(u,v);
		deg[u]++; deg[v]++;
		if ( d ){
			E[t++] = make_pair(u,i);
		}
		else {
	        	G[u].push_back(i); G[v].push_back(i);
		}
	}
}

bool alternate( int u ){
	if ( seen[u] ) return false;
	seen[u] = true;
	int v;
	for ( int i=0; i < G[u].size(); ++i ){
		v = G[u][i];
		if ( hole[v] < 0 || ( alternate( hole[v] ) ) ){
			hole[v] = u;
			return true;
		}
	}
	return false;
}

bool process(){
	//Checking connectivity on undirected graph
	if ( nc > 1 ) return false;
	//Checking degree condition on undirected graph
	for ( int i=0; i < n; ++i ){
		if ( deg[i]&1 ) return false;
		deg[i] >>= 1;
	}
	//Initiate the matching
	for ( int i=0; i < t; ++i ){
		hole[ E[i].second ] = E[i].first;
		if (--deg[ E[i].first ] < 0 ) return false;
		
	}
	//Finding perfect matching
	for ( int i=0; i<n; ++i ){
		for ( int j=0; j < deg[i]; ++j ){
			fill( seen , seen + n, false );
			if ( !alternate( i ) ) return false;
		}
	}
	return true;
}

int main(){
	int runs;
	scanf("%d",&runs);
	while ( runs-- ){
		scanf("%d%d",&n,&m);
		init();
		read_input();
		if ( process() ) puts("possible");
		else puts("impossible");
	}
	return 0;
}
