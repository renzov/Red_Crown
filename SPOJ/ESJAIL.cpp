#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int MAX = 100000;
 
vector<int> G[MAX];
int key[MAX];
bool locked[MAX];
bool visited[MAX];
int N;
 
bool bfs(){
    
    queue<int> q;
    q.push(0);
    visited[0] = true;
    
    int u,v;
    
    while (!q.empty()){
        u = q.front();
        q.pop();
        if (u==(N-1)) return true;
        if (key[u] != -1){
           locked[key[u]] = false;
           if (visited[key[u]]){ //Si ya fue visitado
               q.push(key[u]);
           }    
        }
        for (int i=0; i < G[u].size(); ++i){
            v = G[u][i];
            if (!visited[v]){
               visited[v] = true; 
               if (!locked[v]) q.push(v);    
            }
        }
    }
    return false;    
} 
 
int main(){
    
    int K,M;
    int u,v;
    bool res;
    
   
    while (scanf("%d %d %d",&N,&K,&M) && N > 0 ){
        for (int i=0; i < N; ++i){
            G[i].clear();
            locked[i] = false;
            key[i] = -1;
            visited[i] = false;
        }
        for (int i=0; i < K; ++i){
            scanf("%d %d",&u,&v);
            u--,v--;
            locked[v] = true;
            key[u] = v;    
        }
        for (int i=0; i < M; ++i){
            scanf("%d %d",&u,&v);
            u--,v--;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        res = bfs();
        printf((res)? "Y\n":"N\n");
    }    
    
    return 0;    
} 
