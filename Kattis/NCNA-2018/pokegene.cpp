#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<climits>
#include<cassert>
using namespace std;
typedef pair<int,int> pii;
const int MAXN = 200005;
const int LOGN = 20;
struct Node {	// Node of the trie
	int idx; 		// index of the string (when ordered) otherwise -1
	int nxt[26];	// pointers to the nodes' childs
	int cnt;		// Number of childs -- to make compression easier
	Node(){
		idx = -1;
		cnt = 0;
		fill( nxt, nxt + 26, -1 );
	}
};	

string poke[MAXN];
int ord[MAXN];
int inv[MAXN];
int q[MAXN];
vector<Node> Trie;

int N, M, Q;

vector<int> T[2*MAXN];
vector<int> W[2*MAXN];
int H[2*MAXN];
int d[2*MAXN];
int P[LOGN][2*MAXN];
int lg;

bool cmp( const int &i, const int &j ){
	return poke[i] < poke[j];
}

void construct_trie(){
	
	Trie.push_back( Node() );	// creating the root
	Trie[0].idx = 0;			// root of the trie has index 0

	int id;
	for ( int i=1; i <= N; ++i ){
		id = ord[i];
		// insert string in the trie
		//cout << "Inserting " << poke[id] << endl;
		int act = 0;	// current node index
		int pos;
		for ( int j=0; j < poke[id].size(); ++j ){
			pos = poke[id][j] - 'a';
			//cout << "Node = " << act << " pos = " << pos << endl;
			if ( Trie[act].nxt[pos] == -1 ){
				Trie[act].cnt++;	// one more child
				Trie[act].nxt[pos] = (int)Trie.size();
				act = (int) Trie.size();
				Trie.push_back( Node() );
			}
			else {
				act = Trie[act].nxt[pos];
			}
		}
		Trie[act].idx = i;	// string inserted
	}
}

pii compress( const int &u ){
	pii child;

	if ( Trie[u].cnt == 1 && Trie[u].idx == -1 ){
		for ( int i=0; i < 26; ++i ){
			if ( Trie[u].nxt[i] != -1 ){
				child = compress( Trie[u].nxt[i] );
				child.second++;
				return child;
			}
		}
	}

	int vertex, w, v;

	if ( Trie[u].idx != -1 ) vertex = Trie[u].idx;	// this node represents a string. We use the same index
	else vertex = M++;								// this is a new node. 

	for ( int i=0; i < 26; ++i ){
		if ( Trie[u].nxt[i] != -1 ){
			child = compress( Trie[u].nxt[i] );
			v = child.first, w = child.second;
			T[ vertex ].push_back( v );
			W[ vertex ].push_back( w );
		}
	}
	return pii( vertex, 0 );
}

void dfs( const int &u, const int &p ){
	int v;

	H[u] = ( p == -1 )? 0:(H[p] + 1);
	P[0][u] = p;

	for ( int i = 0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		d[v] = d[u] + W[u][i] + 1;
		dfs( v, u );
	}
}

void precalc(){

	for ( lg = 0; (1 << lg) < M; lg++ );
	assert( lg <= LOGN );
	for ( int i=1; i < lg; ++i )
		for ( int j = 0; j < M; ++j )
			if ( P[i - 1][j] != -1 )
				P[i][j] = P[i - 1][ P[i - 1][j] ];
			else 
				P[i][j] = -1;
}

int lca( int u, int v ){
	if ( H[u] > H[v] ) swap(u, v);
	// H[u] <= H[v]
	for ( int i=lg - 1; i >= 0; --i )
		if ( (H[v] - H[u]) >= (1 << i) )
			v = P[i][v];
	// H[u] == H[v]		
	if ( u == v ) return u;
	for ( int i=lg - 1; i >= 0; --i ){
		if ( P[i][u] != -1 && P[i][u] != P[i][v] ){
			u = P[i][u], v = P[i][v];
		}
	}
	return P[0][u];
}

int main(){
	// Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int K, L;
	int s;
	int u, v;

	cin >> N >> Q;
	for ( int i=1; i <= N; ++i ){
		cin >> poke[i];
		ord[i] = i;
	}
	// ord[i] = index of ith smallest (lexicographic) string
	sort( ord + 1, ord + (N + 1), cmp );
	for ( int i=1; i <= N; ++i )
		inv[ ord[i] ] = i;
	
	construct_trie();
	M = N + 1;	// M = number of vertices of the compressed tree. Initially N + 1 vertices
	compress( 0 );
	// calculations for LCA
	d[0] = 0;
	dfs( 0, -1 );
	precalc();
	//process queries
	while ( Q-- ){
		cin >> K >> L;
		for ( int i=0; i < K; ++i ){
			cin >> s;
			q[i] = inv[s];
		}
		sort( q, q + K );
		// answer the query
		int res;				// the result from each segment of size L
		long long ans = 0LL;	// the result of the query
		for ( int i=0; i <= K - L; ++i ){
			u = lca( q[i], q[i + L - 1] );
			res = INT_MAX;
			if ( i > 0 ){
				v = lca( q[i - 1], q[i + L - 1] );
				res = min( res, d[u] - d[v] );
			}
			if ( i < K - L ){
				v = lca( q[i], q[i + L] );
				res = min( res, d[u] - d[v] );
			}
			if ( res == INT_MAX ){
				ans += d[u];
			}
			else {
				ans += res;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
