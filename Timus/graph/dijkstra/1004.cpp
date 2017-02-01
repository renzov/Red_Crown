#include<iostream>
#include<queue>
#include<list>
#include<climits>
#include<cstdio>
using namespace std;
int n;
int G[101][101];

int best;
int start,fin;
int best_pred[101];

void dijkstra(int s){
  int d[101];
  int pred[101];
  for (int i=0; i < n; ++i){
	 d[i] = INT_MAX;
	 pred[i] = -1;
  }
  int u,v,w;

  priority_queue< pair<int,int> , vector< pair<int,int> > , greater< pair<int,int> > > q;
  d[s] = 0;
  q.push( make_pair(0,s) );
  
  while (!q.empty()){
		u = q.top().second;
		w = q.top().first;
		q.pop();
		if (w > d[u]) continue; 
		for (v=0; v < n; ++v){
		  if (G[u][v] < INT_MAX){
			 if (w + G[u][v] < d[v]){
				pred[v] = u;
				d[v] = w + G[u][v];
				q.push( make_pair(d[v],v) );
			 }
		  }
		}
  }

  int dist;
  bool change = false;

  for (int i=0; i < n; ++i){
	 for (int j=i+1; j < n; ++j){
		if (G[i][j] < INT_MAX && pred[i] != j && pred[j] != i){
		  dist = d[i] + d[j] + G[i][j];
		  if (dist < best){
			 change = true;
			 start = i;
			 fin = j;
			 best = dist;
		  }
		}
	 }
  }
  if (change){
	 for (int i=0; i < n; ++i)
		best_pred[i] = pred[i];
  }
}

int main(){
  int m;
  int u,v,w;
  list<int> sol;
	
  while (scanf("%d",&n) && (n >= 0) ){
	 scanf("%d",&m);
	 for (int i=0; i < n; ++i){
		G[i][i] = INT_MAX;
		for (int j=i+1; j < n; ++j)
		  G[i][j] = G[j][i] = INT_MAX;
	 }
	 for (int i=0; i < m; ++i){
		scanf("%d %d %d",&u,&v,&w);
		v--,u--;
		if (G[u][v] > w) G[u][v] = G[v][u] = w;
	 }
	 best = INT_MAX;
	 for (int i=0; i < n; ++i){
		dijkstra(i);
	 }
	 if (best < INT_MAX){
		int cnt = 0;
		u = start;
		while (u > -1){
		  sol.push_back(u+1);
		  u = best_pred[u];
		}
		sol.pop_back();
		while (!sol.empty()){
		  cnt++;
		  if (cnt > 1) cout << ' ';
		  cout << *sol.begin();
		  sol.pop_front();
		}
		u = fin;
		while (u > -1){
		  sol.push_front(u+1);
		  u = best_pred[u];
		}
		while (!sol.empty()){
		  cnt++;
		  if (cnt > 1) cout << ' ';
		  cout << *sol.begin();
		  sol.pop_front();
		}
		cout << endl;
	 }
	 else {
		cout << "No solution." << endl;
	 }
  }

  return 0;
}