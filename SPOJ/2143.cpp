#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<set>
#include<map>
#include<string>
using namespace std;

const char BLACK = 0;
const char WHITE = 1;
const int MAX = 10001;

set<int> G[MAX];
int indegree[MAX] = {0};
char color[MAX] = {0};

int n = 0;

int topsort(){
  int res = 0;
  queue<int> q;
  for (int i=0; i < n; ++i){
	 if (indegree[i] == 0){
		q.push(i);
		res += color[i];
	 }
  }
  int u,v;
  while (!q.empty()){
	 u = q.front();
	 q.pop();
	 for ( set<int>::iterator it = G[u].begin() ; it != G[u].end(); ++it){
		 v = *it;
		 color[v] &= color[u];
		 indegree[v]--;
		 if (indegree[v]==0){
			 q.push(v);
			 res += color[v];
		 }
	 } 
  }
  
  return res;
}

int main(){
  map<string,int> hash;
  string tmp;
  char cad[500];
  int u,v;
  int res;

  while (scanf("%s",cad) != EOF){
		tmp = string(cad);
		if (hash.find(tmp) == hash.end()){
		  hash[tmp] = n++;
		}
		v = hash[tmp];
		color[v] = WHITE;
		while (1){
		  scanf("%s",cad);
		  if (cad[0]=='0') break;
		  tmp = string(cad);
		  if (hash.find(tmp) == hash.end()){
			 hash[tmp] = n++;
		  }
		  u = hash[tmp];
		  if (G[u].find(v) == G[u].end()){
			 indegree[v]++;
			 G[u].insert(v);
		  }
		}
  }
  res = topsort();
  printf("%d\n",res);
  return 0;
}
