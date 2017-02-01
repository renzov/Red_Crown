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
vector<string> nperson;
vector<string> nclub;
vector<string> nparty;
int n;
map<string,int> hash_person;
map<string,int> hash_club;
map<string,int> hash_party;
int cap[3502][3502];
int fnet[3502][3502];
vector<int> G[3502];
int prev[3502];
int q[3502];

int get_person(string &name){
  if (hash_person.find(name) == hash_person.end()){
	 G[n].clear();
	 nperson.push_back(name);
	 person.push_back(n);
	 hash_person[name] = n++;
  }
  return hash_person[name];
}

int get_party(string &name){
  if (hash_party.find(name) == hash_party.end()){
	 G[n].clear();
	 nparty.push_back(name);
	 party.push_back(n);
	 hash_party[name] = n++;
  }
  return hash_party[name];
}

int get_club(string &name){
  if (hash_club.find(name) == hash_club.end()){
	 G[n].clear();
	 nclub.push_back(name);
	 club.push_back(n);
	 hash_club[name] = n++;
  }
  return hash_club[name];
}

int max_flow(int s, int t)
{
    // init the flow network
    memset( fnet, 0, sizeof( fnet ) );
	 int qf,qb;
    int flow = 0;
	 int v;
	 
    while( true )
    {
        // find an augmenting path
        for (int i=0; i < n; ++i) prev[i] = -1;
        qf = qb = 0;
        prev[q[qb++] = s] = -2;
        while( qb > qf && prev[t] == -1 )
            for( int u = q[qf++], i = 0; i < G[u].size(); ++i ){
              v = G[u][i];  
				  if( prev[v] == -1 && fnet[u][v] - fnet[v][u] < cap[u][v] )
                    prev[q[qb++] = v] = u;
				}

        // see if we're done
        if( prev[t] == -1 ) break;

        // get the bottleneck capacity
        int bot = 0x7FFFFFFF;
        for( int v = t, u = prev[v]; u >= 0; v = u, u = prev[v] )
				if (bot > (cap[u][v] - fnet[u][v] + fnet[v][u]))
            bot = cap[u][v] - fnet[u][v] + fnet[v][u];

        // update the flow network
        for( int v = t, u = prev[v]; u >= 0; v = u, u = prev[v] )
            fnet[u][v] += bot;

        flow += bot;
    }

    return flow;
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
	 hash_person.clear(); hash_party.clear(); hash_club.clear();
	 person.clear(); party.clear(); club.clear();
	 nperson.clear(); nparty.clear(); nclub.clear();
	 memset(cap,0,sizeof(cap));
	 
	 while (getline(cin,line)){
		  if (line.size() == 0) break;
		  stringstream in(line);
		  in >> name;
		  a = get_person(name);
		  in >> name;
		  b = get_party(name);
		  G[b].push_back(a);
		  G[a].push_back(b);
		  cap[b][a] = 1;
		  while ( in >> name ){
				c = get_club(name);
				G[a].push_back(c);
				G[c].push_back(a);
				cap[a][c] = 1;
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
		  cap[s][a] = (council-1)/2;
		}
		/* sink */
		G[n].clear();
		t = n++;
		for (int i=0; i < club.size(); ++i){
		  a = club[i];
		  G[a].push_back(t);
		  cap[a][t] = 1;
		}
		
		int res = max_flow(s,t);
		
		if (res == council){
		  for (int i=0; i < club.size(); ++i){
			 b = club[i];
			 for (int j=0; j < person.size(); ++j){
				a = person[j];
				if ((fnet[a][b] - fnet[b][a]) == 1 && cap[a][b] == 1){
				  cout << nperson[j] << " " << nclub[i] << endl;
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