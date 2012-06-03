#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<sstream>
#include<climits>
#include<algorithm>
#include<set>
using namespace std;
const int MAXN = 502;

int S[MAXN];
bool in[MAXN];
vector<int> G[MAXN];
int scc[MAXN];
int number[MAXN];
int low[MAXN];
int nc;
int num;
int st;
int nodes[MAXN];
string name[MAXN];
bool T[MAXN][MAXN];
bool inc[MAXN];

inline int Min(int x,int y){ return x<=y? x:y; }

void strong_connect(int u){
	int i,v;	
	low[u] = number[u] = num++;
	S[st++] = u; in[u] = true;
	for (i=0; i < G[u].size(); ++i){
		v = G[u][i];
		if ( number[v] < 0 ){
			strong_connect(v);
			low[u] = Min(low[u],low[v]);
		}
		else if ( number[v] < number[u] && in[v]){
			low[u] = Min(low[u],number[v]);
		}
	}
	if ( low[u] == number[u] ){
		while ( st > 0 && number[ S[st-1] ] >= number[u] ){
			nodes[nc]++;
			v = S[--st];
			in[v] = false;
			scc[v] = nc;
		}
		nc++;
	}
}

void dfs(int u){
	int v;	
	inc[u] = true;
	for (v=0; v < nc; ++v)
		if ( T[u][v] && !inc[v] ) dfs(v);
}

int main(){
	int n,m;
	int i,j,k;
	int u,v;
	string a,b;
	string line;
	bool first;

	while ( cin >> m && m > 0){
		map<string,int> hash;	
		getline(cin,line);
		n = 0;
		/* Initialize */
		st = nc = num = 0;		
		for (i=0; i < m; ++i){
			G[i].clear();
			nodes[i] = 0;
			in[i] = false;
			inc[i] = false;
			scc[i] = low[i] = number[i] = -1;
		}
		
		for (i=0; i<m; ++i){
			getline(cin,line);
			stringstream input(line);
			input >> a;
			if ( hash.find(a) == hash.end() ){ name[n] = a; hash[a] = n++; }
			u = hash[a];
			while ( input >> b ){
				if ( hash.find(b) == hash.end() ){ name[n] = b; hash[b] = n++; }
				v = hash[b];
				if ( find(G[u].begin(),G[u].end(),v) == G[u].end() ) G[u].push_back(v);
			}
		}

		for (i=0; i < n; ++i)
			if ( number[i] < 0 ) strong_connect(i);

		for (i=0; i < nc; ++i)
			for (j=0; j < nc; ++j)
				T[i][j] = false;
		
		for (i=0; i < n; ++i){
			u = scc[i];
			for (j=0; j < G[i].size(); ++j){
				v = scc[ G[i][j] ];
				if ( u!=v && !T[u][v] ) T[u][v] = true;
			}
		}

		for (i=0; i < nc; ++i)
			if ( !inc[i] && nodes[i] > 1 )
				dfs(i);

		set<string> res;

		for (i=0; i < nc; ++i){
			if ( inc[i] ){
				for (j=0; j < n; ++j)
					if ( scc[j] == i ) res.insert(name[j]);
			}
		}

		first = true;
		cout << res.size() << endl;	
		for(set<string>::iterator it=res.begin(); it!=res.end() ; it++){
			if (!first) cout << " ";
			cout << *it;
			first = false;
		}
		cout << endl;		
	}
	return 0;
}
