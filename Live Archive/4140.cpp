#include<cstdio>
#include<vector>
using namespace std;
const int MAXN = 100005;
const int MAXL = 32;
int N, L;

int bet[MAXN][MAXL];
int f[MAXL];

struct Node {
	int cost;
	int nxt[MAXL];
	Node(){
		cost = 0;
		fill( nxt, nxt + L, -1 );
	}
};

vector<Node> Trie;

void Insert( int *B ){
	int u = 0;	// current node
	int size = 0;
	while ( *B >= 0 ){
		if ( Trie[u].nxt[*B] == -1 ){
			Trie[u].nxt[*B] = Trie.size();
			Trie.push_back( Node() );
			size++;
		}
		u = Trie[u].nxt[*B];
		B++, size++;
	}
	Trie[u].cost += f[ size - 1 ];
}

void process(){
	int m;

	scanf("%d %d", &L, &N);
	for ( int i=0; i < L; ++i )
		scanf("%d", f + i );
	// Read the bets and insert in the trie
	Trie.push_back( Node() );
	for ( int i=0; i < N; ++i ){
		scanf("%d", &m);
		for ( int j=0; j < m; ++j ){
			scanf("%d", bet[i] + j );
			bet[i][j]--;
		}
		bet[i][m] = -1;
		Insert( bet[i] ); // insert i-th bet in the trie
	}
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ){
		process();
		if ( runs ) Trie.clear();
	}
	return 0;
}
