#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<sstream>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;
const int INF = 999999999;

vector<int> person;
vector<int> club;
vector<int> party;
int n;
map<string,int> hash;
int C[3500][3500];
int flow[3500][3500];
vector<int> G[3500];
string names[3500];
int pred[3500];
int max_cap[3500];
int q[3500];

int get_id(string &name,int type){
  if (hash.find(name) == hash.end()){
	 G[n].clear();
	 names[n] = name;
	 switch (type){
		case 0: person.push_back(n); break;
		case 1: party.push_back(n); break;
		case 2: club.push_back(n); break;
	 }
	 hash[name] = n++;
  }
  return hash[name];
}

inline int min(int a,int b){
	 return (a < b)? a:b;
}

int max_flow(int s,int t){
  int f = 0;
  int qf,qt;
  int u,v;
  while ( 1 ){
	 qf = 0;
	 qt = 0;
	 /* finding an augmenting path with bfs */
	 q[ qt++ ] = s;
	 for (int i=0; i < n; ++i){ pred[i] = max_cap[i]= -1; }
	 max_cap[s] = INF;
	 while (qt > qf && pred[t] == -1){
		  u = q[ qf++ ];
		  		  for (int i=0; i < G[u].size(); ++i){
				v = G[u][i];
				if (max_cap[v] == -1 && (C[u][v] - flow[u][v] > 0)){	/* can push flow */
					 max_cap[v] = min( max_cap[u] , C[u][v] - flow[u][v] );
					 pred[v] = u;
					 q[ qt++ ] = v;
				}
		  }
	 }
	 if ( max_cap[t] == -1 ) break;
	 /* relax edges */
	 f += max_cap[t];
	 v = t;
	 while (v != s){
		  u = pred[v];
		  flow[u][v] += max_cap[t];
		  flow[v][u] -= max_cap[t];
		  v = u;
	 }
  }
  return f;
}

int main(){
  string line;
  string name;
  int runs;
  int a,b,c;
  int s,t;
  int council;
  
  cin >> runs;
  getline(cin,line);
  getline(cin,line);
  
  while (runs--){

	 n = 0;
	 hash.clear();
	 person.clear();
	 party.clear();
	 club.clear();
	 memset(C,0,sizeof(C));
	 memset(flow,0,sizeof(flow));
	 
	 while (getline(cin,line)){
		  if (line.size() == 0) break;
		  stringstream in(line);
		  in >> name;
		  a = get_id(name,0);
		  in >> name;
		  b = get_id(name,1);
		  G[b].push_back(a);
		  G[a].push_back(b);
		  C[b][a] = 1;
		  while ( in >> name ){
				c = get_id(name,2);
				G[a].push_back(c);
				G[c].push_back(a);
				C[a][c] = 1;
		  }
	 }
	 
	 council = club.size();
	 /* source */
	 if (council == 0 || council > person.size()){
		  cout << "Impossible." << endl;
	 }
	 else {
		G[n].clear();
		s = n++;
		for (int i=0; i < party.size(); ++i){
		  a = party[i];
		  G[s].push_back(a);
		  C[s][a] = (council-1)/2;
		}
		/* sink */
		G[n].clear();
		t = n++;
		for (int i=0; i < club.size(); ++i){
		  a = club[i];
		  G[a].push_back(t);
		  C[a][t] = 1;
		}
		
		int res = max_flow(s,t);
		
		if (res == council){
		  for (int i=0; i < club.size(); ++i){
			 b = club[i];
			 for (int j=0; j < person.size(); ++j){
				a = person[j];
				if (flow[a][b] == 1 && C[a][b] == 1){
				  cout << names[a] << " " << names[b] << endl;
				  break;
				}
			 }
		  }
		}
		else {
			 cout << "Impossible." << endl;
		}
	 }
	 if (runs) cout << endl;
  }
  return 0;
}