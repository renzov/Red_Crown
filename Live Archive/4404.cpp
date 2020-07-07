#include<sstream>
#include<iostream>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 18;
int N;
vector<int> G[MAXN];
map<string, int> male;
map<string, int> female;
long long dp[MAXN][1 << MAXN];
string nameM[MAXN];
string nameF[MAXN];

void clean(){
	male.clear(); 
	female.clear();
	for ( int i=0; i < N; ++i )
		G[i].clear();
}

void read_names( map<string, int> &H, string V[] ){
	set<string> S;
	string name;
	for ( int i=0; i < N; ++i ){
		cin >> name;
		S.insert( name );
	}
	set<string>::iterator it = S.begin();
	for ( int i=0; i < N; it++,i++ ){
		H[ *it ] = i;
		V[i] = *it;
	}
}

long long solve( const int &u, const int &mask ){
	if ( u == N ) return dp[u][mask] = (mask == 0);
	long long &res = dp[u][mask];
	if ( res >= 0 ) return res;
	res = 0;

	int v;
	for ( int i=0; i < (int) G[u].size(); ++i ){
		v = G[u][i];
		if ( (mask >> v)&1 )
			res += solve( u + 1, mask ^ ( 1 << v ) );
	}
	return res;
}

void print_ans( const int &u, const int &mask ){
	if ( u == N ){
		cout << endl;
		return;
	}
	int v;
	for ( int i=0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( ((mask >> v)&1) && dp[ u + 1 ][ mask ^ (1 << v) ] > 0 ){
			if ( u ) cout << " ";
			cout << nameM[u] << " " << nameF[v];
			print_ans( u + 1, mask ^ (1 << v) );
			break;
		}
	}
}

void process(){
	// Read the names
	cin >> N;
	read_names( male, nameM );
	read_names( female, nameF );
	// Read the graph
	string line;
	getline( cin, line ); // Read the end of line
	string name;
	int u, v;
	for ( int i=0; i < N; ++i ){
		getline( cin, line );
		istringstream in( line );
		in >> name;
		name.pop_back();
		u = male[ name ];
		while ( in >> name ){
			v = female[name];
			G[u].push_back( v );
		}
	}

	for ( int i=0; i < N; ++i )
		sort( G[i].begin(), G[i].end() );
	// Initialize dp matrix
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < (1 << N); ++j )
			dp[i][j] = -1;

	long long cnt = solve( 0, (1 << N) - 1 );
	if ( !cnt ) cout << "No Way" << endl;
	else {
		cout << cnt << endl;
		print_ans( 0, (1 << N) - 1 );
	}
}

int main(){
	int runs;
	cin >> runs;
	for ( int i=1; i <= runs; ++i ){
		cout << "Case " << i << ":" << endl;
		process();
		clean();
	}
	return 0;
}
