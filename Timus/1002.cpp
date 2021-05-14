#include<cstdio>
#include<vector>
#include<climits>
#include<string>
using namespace std;
const int MAXN = 50005;

char dict[MAXN][55];
int f[] = { 2, 2, 2, 3, 3, 3, 4, 4, 1, 1, 5, 5, 6, 6, 0, 7, 0, 7, 7, 8, 8, 8, 9, 9, 9, 0 };
int M;	// Number of nodes in Trie 
int W;	// Number of words in dictionary
int N;	// Size of string

int D[128];
int dp[128];
int nxt[128];
int idx[128];

struct Node {
	int child[10];	// Index of the other vertices
	int idx;		// index of the word in dictionary
	Node(){
		idx = -1;
		for ( int i=0; i < 10; ++i )
			child[i] = -1;
	}
};

vector<Node> Trie;

bool insert( char *w ){
	// Returns true if the word was inserted in the dictionary
	// That is, if it does not exists previously
	int d;
	int c;
	int cur = 0;	// root of Trie
	for ( int i=0; w[i]; ++i ){
		c = w[i] - 'a';
		d = f[c];
		if ( Trie[cur].child[d] == -1 ){
			Trie.push_back( Node() );
			Trie[cur].child[d] = M++;
		}
		cur = Trie[cur].child[d];
	}
	if ( Trie[cur].idx != -1 ) return false;
	Trie[cur].idx = W;
	return true;
}

void clear(){
	W = 0;
	Trie.clear();
	Trie.push_back( Node() );
	M = 1;
}

void process(){
	int T;
	scanf("%d", &T);
	for ( int i=0; i < T; ++i ){
		scanf("%s", dict[W]);
		if ( insert( dict[W] ) )
			W++;
	}

	dp[N] = 0;
	idx[N] = nxt[N] = -1;

	int cur, d;
	for ( int i=N - 1; i >= 0; --i ){
		dp[i] = INT_MAX;
		nxt[i] = -1;
		cur = 0;
		for ( int j=i; j < N; ++j ){
			d = D[j];
			if ( Trie[cur].child[d] == -1 ) break;	// No more ways to divide string
			cur = Trie[cur].child[d];
			if ( Trie[cur].idx != -1 && dp[j + 1] < INT_MAX ){
				if ( dp[i] > dp[j + 1] + 1 ){
					dp[i] = dp[j + 1] + 1;
					nxt[i] = j + 1;
					idx[i] = Trie[cur].idx;
				}
			}
				
		}
	}
	if ( dp[0] < INT_MAX ){
		int p = 0;
		while ( p < N ){
			if ( p > 0 ) putchar(' ');
			printf("%s", dict[ idx[p] ]);
			p = nxt[p];
		}
		puts("");
	}
	else {
		puts("No solution.");
	}
}



int main(){
	char S[128];
	while ( scanf("%s", S) && S[0] != '-' ){
		N = 0;
		for ( int i=0; S[i]; ++i, N++ )
			D[i] = S[i] - '0';
		
		clear();
		process();
	}

	return 0;
}
