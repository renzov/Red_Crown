#include<cstdio>
#include<vector>
#include<list>
using namespace std;
typedef pair<int,int> edge;

const int MAXN = 1005;

int N, M, K;

list<int> T1[2*MAXN];
list<int> T2[2*MAXN]; 
edge E1[2*MAXN];
edge E2[2*MAXN]; 
int e1, e2;

list< list<int> > L1, L2;

char st[15];
int val;
/*
	Convention: for every tree the vertices 0...K-1 are leafs and the 
	rest are internal vertices
*/
int read_vert(){
	scanf("%s", st);
	sscanf(st+2,"%d", &val );
	return ( st[1]=='S' )? (val-1):(K+val-1);
}

void read_tree( list<int> T[], edge E[], int l, int nl, int &e ){
	int u, v;	
	for ( int i=1; i < (nl+l); ++i ){
		u = read_vert();
		v = read_vert();
		T[u].push_back( e );
		T[v].push_back( e );
		E[e++] = edge( u, v );
	}
}

void print_tree( edge E[], int e ){
	int u, v;
	for ( int i=0; i < e ; ++i ){
		u = E[i].first, v = E[i].second;
		if ( u >= K ){ printf("P%d ", u-K+1); }
		else { printf("S%d ", u+1); }
		if ( v >= K ){ printf("P%d ", v-K+1); }
		else { printf("S%d ", v+1); }
		puts("");
	}
}

bool decomp( list<int> T[], int n, list< list<int> > &L ){
	int root = -1;
	for ( int i=0; i < n; ++i ){
		if ( (int)T[i].size() > 1 ){ root = i; break; }
	}
	dfs( root );
}

int main(){
	int runs;

	scanf("%d", &runs);
	while ( runs-- ){		
		scanf("%d %d %d", &K, &N, &M);
		read_tree( T1, E1, K, N, e1 );
		read_tree( T2, E2, K, M, e2 );
		if ( !decomp( T1, N + K, L1 ) || !decomp( T2, M + K, L2 ) ){
			puts("NO");
		}
		else {
			// print the solution
		}
		print_tree( E1, e1 );
		puts("");
		print_tree( E2, e2 );
		// clear memory
		if ( runs ){
			e1 = e2 = 0;
			for ( int i=0; i < (N+K); ++i ) T1[i].clear();
			for ( int i=0; i < (M+K); ++i ) T2[i].clear(); 
		}
	}
	return 0;
}
