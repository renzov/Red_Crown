#include<iostream>
#include<map>
#include<string>
#include<queue>
#include<vector>
using namespace std;

vector<int> G[ 105 ];
int indegree[ 105 ];
string name[ 105 ];
int ord[ 105 ];
int n;

void topsort(){
  priority_queue< int , vector<int> , greater<int> > q;
  for (int i=0; i < n; ++i) 
	 if ( indegree[i] == 0 )
		q.push( i );
  int u,v;
  int pos = 0;
  while (!q.empty()){
		u = q.top();
		q.pop();
		ord[ pos++ ] = u;
		for (int i=0; i < G[u].size(); ++i){
			 v = G[u][i];
			 indegree[v]--;
			 if ( indegree[v] == 0 ) q.push( v );
		}
  }
}

int main(){
  int m;
  string a,b;
  int u,v;
  int cases = 0;
  while (cin >> n){
		cases++;
		map<string,int> hash;
		for (int i=0; i < n; ++i){
			 cin >> name[i];
			 G[i].clear();
			 indegree[i] = 0;
			 hash[ name[i] ] = i;
		}
		cin >> m;
		while (m--){
			 cin >> a >> b;
			 u = hash[a]; v = hash[b];
			 G[u].push_back(v); indegree[v]++;
		}
		topsort();
		cout << "Case #" << cases << ": Dilbert should drink beverages in this order:";
		for (int i=0;  i<n; ++i) cout << " " << name[ ord[i] ];
		cout << ".\n\n";
  }
  return 0;
}