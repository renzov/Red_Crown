#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<cstdlib>
#include<algorithm>
using namespace std;

vector<int> G[350];
int T[350];
int P[350][10];
int L[350];
int cmp[350];
int n;
int indegree[350] = {0};
map<string,int> hash;



int give_id(string &s){
  if (hash.find(s) == hash.end()){
		hash[s] = n;
		return n++;
  }
  return hash[s];
}

void dfs(int u,int nc){
  cmp[u] = nc;
  for (int i=0; i < G[u].size(); ++i){
		L[ G[u][i] ] = L[u] + 1;
		dfs(G[u][i],nc);
  }
}

void preprocess(){

  int i,j;

  for (int i=0; i < n; ++i)
	 for (int j=0; (1<<j) < n; ++j)
		P[i][j] = -1;
  
  for (int i=0; i < n; ++i)
	 P[i][0] = T[i];

  for (int j=1; (1 << j) < n; ++j){
		for (int i=0; i < n; ++i){
			 if (P[ i ][ j-1 ] != -1)
				P[i][j] = P[ P[i][j-1] ][j-1];
		}
  }

}

int query(int p,int q){
  int i,log,tmp;

  if (L[p] < L[q]){
		tmp=p,p=q,q=tmp;
  }
  
  for (log = 1; (1<<log) <= L[p]; ++log);
  log--;

  for (i=log; i >= 0; --i){
		if (L[p] - (1<<i) >= L[q]){
		  p = P[p][i];
		}
  }
  
  if (p==q) return p;
  
  for (i=log; i >= 0; --i){
		if (P[p][i] != -1 && P[p][i] != P[q][i])
			 p = P[p][i],q = P[q][i]; 
  }
  
  return T[p];
  
}

int main(){
  n = 0;
  string parent,child;
  int u,v;
  int a;
  int d,d2,rem;

  for (int i=0; i < 320; ++i) T[i] = -1;
  
  while (1){
	 cin >> child >> parent;
	 if (child == "no.child") break;
	 u = give_id(parent);
	 v = give_id(child);
	 indegree[v]++;
	 T[v] = u;
	 G[u].push_back(v);
  }
  
  for (int i=0; i < n; ++i)
	 if (indegree[i] == 0){
		  L[i] = 0;
		  dfs(i,i);
	 }
  
  preprocess();

  while (cin >> parent >> child){
		if (hash.find(parent) == hash.end())
			 u = -1;
		else
			 u = hash[parent];
		
		if (hash.find(child) == hash.end())
			 v = -1;
		else
			 v = hash[child];
		
		if (u==-1 || v==-1 || cmp[u] != cmp[v]){
		  cout << "no relation" << endl;
		}
		else {
			a = query(u,v);
			if (a == u){
				d = L[v] - L[u];
				if (d == 1) cout << "parent" << endl;
				else if (d == 2) cout << "grand parent" << endl;
				else {
					d -= 2;
					for (int i=0; i < d; ++i){
						  if (i > 0) cout << " ";
						  cout << "great";
					}
					cout << " grand parent" << endl;
				}
			}
			else if (a == v){
				d = L[u] - L[v];
				if (d == 1) cout << "child" << endl;
				else if (d == 2) cout << "grand child" << endl;
				else {
					d -= 2;
					for (int i=0; i < d; ++i){
						  if (i > 0) cout << " ";
						  cout << "great";
					}
					cout << " grand child" << endl;
				}
			}
			else {
				d = L[u] - L[a];
				d2 = L[v] - L[a];
				rem = abs(d - d2);
				if (d == 1 && rem == 0){
				  cout << "sibling" << endl;
				}
				else {
				  cout << min(d-1,d2-1) << " cousin";
				  if (rem != 0) cout << " removed " << rem;
				  cout << endl;
				}
		   }
		}
  } 

  return 0;
}