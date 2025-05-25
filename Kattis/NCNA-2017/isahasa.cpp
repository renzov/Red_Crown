#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<string>
using namespace std;
const int MAXN = 505;

int N = 0;
bool G[MAXN][MAXN] = {0};
bool D[MAXN][MAXN] = {0};

map<string, int> idx;

int get_idx( const string &s ){
	if ( idx.find(s) == idx.end() )
		idx[s] = N++;
	return idx[s];
}

int main(){
	int M, Q;
	int u, v;
	string name1, name2, type;

	cin >> M >> Q;
	while ( M-- ){
		cin >> name1 >> type >> name2;
		u = get_idx( name1 );
		v = get_idx( name2 );
		if ( type[0] == 'i' ){
			G[u][v] = true;
		}
		else {
			D[u][v] = true;
		}
	}
	
	for ( int i=0; i < N; ++i )
		G[i][i] = true;

	for ( int k=0; k < N; ++k )
		for ( int i=0; i < N; ++i )
			for ( int j=0; j < N; ++j ){
				G[i][j] |= ( G[i][k] & G[k][j] );
				D[i][j] |= ( G[i][k] & D[k][j] );
				D[i][j] |= ( D[i][k] & G[k][j] );
				D[i][j] |= ( D[i][k] & D[k][j] );				
			}

	bool res;
	for ( int i=1; i <= Q; ++i ){
		cout << "Query " << i << ": ";
		cin >> name1 >> type >> name2;
		u = get_idx( name1 );
		v = get_idx( name2 );
		if ( type[0] == 'i' )
			res = G[u][v];
		else 
			res = D[u][v];
		
		if ( res )
			cout << "true" << endl;
		else 
			cout << "false" << endl;
	}
	return 0;
}
