#include<cstdio>
#include<string>
#include<algorithm>
#include<map>
#include<cstring>
#include<iostream>
using namespace std;

bool G[500][500];
string event[500];

map<string,int> hash;
int n;

void transitive_clousure(){
	for (int k=0; k < n; ++k)
		for (int i=0; i < n; ++i)
			for (int j=0; j < n; ++j)
				G[i][j] |= (G[i][k] && G[k][j]);
}

int get_id(char *name){
	string s(name);
	if (hash.find(s) == hash.end()){
		event[n] = s;
		hash[s] = n++;
		return n-1;
	}
	else {
		return hash[s];
	}
}

int main(){
	int nc;
	int m;
	int cases = 0;
	int u,v;
	char name[50];
	
	while (scanf("%d",&nc) && nc){
		cases++;
		memset(G,false,sizeof(G));
		hash.clear();
		n = 0;
		for (int i=0; i < nc; ++i){
			scanf("%d",&m);
			for (int j=0; j < m; ++j){
				scanf("%s",name);
				v = get_id(name);
				if (j > 0){
					G[u][v] = true;
				}
				u = v;
			}
		}
		scanf("%d",&m);
		for (int i=0; i < m; ++i){
			scanf("%s",name);
			u = hash[string(name)];
			scanf("%s",name);
			v = hash[string(name)];
			G[u][v] = true;
		}
		transitive_clousure();
		int cnt = 0;
		pair<string,string> res[3];
		for (int i=0; i < n; ++i){
			for (int j=i+1; j < n; ++j){
				if (!G[i][j] && !G[j][i]){
					if (cnt < 2){
						res[cnt] = make_pair(event[i],event[j]);
					}
					cnt++;
				}
			}
		}
		cout << "Case " << cases << ", ";
		if (cnt == 0) cout << "no concurrent events." << endl;
		else {
			cout << cnt << " concurrent events:" << endl;
			for (int i=0; i < min(2,cnt); ++i){
				//if (i > 0) cout << " ";
				cout << "(" << res[i].first << "," << res[i].second << ") ";
			}
			cout << endl;
		}
	}

	return 0;
}