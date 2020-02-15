#include<cstdio>
#include<iostream>
#include<string>
#include<map>
#include<cstdlib>
#include<algorithm>
using namespace std;

string cow[] = { "Beatrice", "Belinda", "Bella", "Bessie" , "Betsy",  "Blue" , "Buttercup" , "Sue" };
int C[16][2];
int ord[16];
int pos[16];

int main(){

	freopen ("lineup.in", "r", stdin);
	freopen ("lineup.out", "w", stdout);

	map<string,int> idx;
	
	idx["Beatrice"] = 0;
	idx["Belinda"] = 1;
	idx["Bella"] = 2;
	idx["Bessie"] = 3;
	idx["Betsy"] = 4;
	idx["Blue"] = 5;
	idx["Buttercup"] = 6;
	idx["Sue"] = 7;
	
	int N;
	string w;

	cin >> N;
	for ( int i=0; i < N; ++i ){
		cin >> w;	
		C[i][0] = idx[w];
		cin >> w;
		cin >> w;
		cin >> w;
		cin >> w;
		cin >> w;
		C[i][1] = idx[w];
	}

	for ( int i=0; i < 8; ++i )
		ord[i] = i;

	bool ok;
	int u, v;

	do {
		ok = true;
		for ( int i=0; i < 8; ++i ){
			pos[ ord[i] ] = i;
		}
		
		for ( int i=0; i < N && ok; ++i ){
			u = C[i][0], v = C[i][1];
			if ( abs( pos[u] - pos[v] ) > 1 ) ok = false;
		}
		if ( ok ) break;
	}
	while ( next_permutation( ord, ord + 8 ) );
	
	for ( int i=0; i < 8; ++i )
		cout << cow[ ord[i] ] << "\n";
	return 0;
}
