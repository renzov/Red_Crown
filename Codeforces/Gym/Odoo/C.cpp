#include<iostream>
#include<string>
#include<map>
#include<algorithm>
#include<cassert>
#include<vector>
using namespace std;

const int MAXN = 1005;

typedef pair< int, int > pii;
typedef pair< pii, pii > event; 

int ps[6*MAXN];
int cap[6*MAXN];
bool alive[6*MAXN];
string name[6*MAXN];
map<string, int> id;
vector<event> E;

int main(){

	int N, M, Q;
	int u, v, p, w;
	string str;

	cin >> N >> M >> Q;

	for ( int i = 0; i < N; ++i ){
		cin >> name[i] >> cap[i] >> ps[i];
		id[ name[i] ] = i;
	}

	for ( int i=0; i < M; ++i ){
		cin >> u >> p;
		u--;
		ps[ u + N ] = p;
	}

	for ( int i = 0; i < Q; ++i ){
		cin >> u >> str >> w;
		u--;
		v = id[str];
		
		if ( ps[v] <= ps[N + u] ){
			E.push_back( event( pii( ps[u + N] - ps[v], w ), pii( u, v ) ) );
		}
	}

	sort( E.begin(), E.end() );
	fill( alive, alive + N + M, true );
		
	for ( int i = 0; i < (int)E.size(); ++i ){
		u = E[i].second.first;	// virus
		v = E[i].second.second;	// program
		w = E[i].first.second;
			
		if ( !alive[v] || !alive[N + u] ) continue;

		if ( cap[v] >= w ){
			alive[N + u] = false;
		}
		cap[v] -= w;
		if ( cap[v] <= 0 ) alive[v] = false;
	}	
	// Print solution
	vector<pii> res;
	for ( int i = 0; i < N; ++i )
		if ( alive[i] )
			res.push_back( pii( -ps[i], i ) );
	sort( res.begin(), res.end() );
	cout << (int)res.size() << '\n';
	for ( int i = 0; i < (int)res.size(); ++i ){
		if (i) cout << ' ';
		cout << name[ res[i].second ];
	}
	if ( !res.empty() ) cout << '\n'; 
	return 0;
}
