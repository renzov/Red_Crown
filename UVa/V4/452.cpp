#include<string>
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<sstream>
using namespace std;
vector<int> G[30];
int longest[30];
int W[30];
map<char,int> hash;
int n;

int get_index( char c ){
	if ( hash.find(c) != hash.end() ) return hash[c];
	return ( hash[c] = n++ );
}

void dfs( int u ){
	int lon = 0;
	int v;
	for ( int i=0; i < G[u].size(); ++i ){
		v = G[u][i];
		if ( longest[v] == -1 ) dfs(v);
		if ( lon < longest[v] ) lon = longest[v];
	}
	longest[u] = lon + W[u];
}

int main(){
	int runs;
	string line;
	int u,v,w;
	int res;
	string a;
	cin >> runs; getline(cin,line);
	getline( cin , line );
	while ( runs-- ){
		hash.clear();
		for ( int i=0; i < 30; ++i ){ G[i].clear(); longest[i] = -1; }
		n = 0;
		while ( getline(cin,line) && line.size() ){
			stringstream in(line);
			in >> a;
			u = get_index( a[0] );
			in >> W[u];
			while ( in >> a ){
				for ( int i=0; i<a.size(); ++i ){
					v = get_index( a[i] );
					G[u].push_back(v);
				}
			}	
		}
		res = -1;
		for ( int i=0; i < n; ++i ){
			if ( longest[i] == -1 ) dfs(i);
			if ( longest[i] > res ) res = longest[i];
		}
		cout << res << endl;
		if ( runs ) cout << endl;
	}
	


	return 0;
}
