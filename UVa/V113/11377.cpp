#include<vector>
#include<queue>
#include<cstdio>
#include<numeric>

using namespace std;
const int MAX = 2005;

bool has_airport[MAX] = {0};
vector<int> G[MAX];
int d[MAX];
int n;

int dijkstra(int s,int e){
    int u,v;
    deque< pair<int,int> > q;
    for (int i=0; i < n; ++i)
        d[i] = INT_MAX;
    d[s] = (has_airport[s]  || (u==e))? 0:1;
    q.push_back( make_pair(s,d[s]) );
    while (!q.empty()){
        u = q.front().first;
        if (d[u] < q.front().second) continue;
        q.pop_front();
        if (u==e) return d[u];
        for (int i=0; i < G[u].size(); ++i){
            v = G[u][i];
            if (has_airport[v]){
               if (d[u] < d[v]){
                  d[v] = d[u];
                  q.push_front( make_pair(v,d[v]) );    
               }
            }
            else {
                if ((d[u]+1) < d[v]){
                    d[v] = d[u] + 1;
                    q.push_back( make_pair(v,d[v]) );    
                }
            }    
        }    
    }
    return -1;
}

int main(){
    
    int runs;
    int k,m;
    int u,v;
    int q;
    int res;
  
    
    scanf("%d",&runs);
    
    for (int cases = 1; cases <=  runs; ++cases){
        scanf("%d %d %d",&n,&m,&k);
        
        for (int i=0; i < n; ++i) G[i].clear(),has_airport[i] = false;
        
        for (int i=0; i < k; ++i){
            scanf("%d",&u);
            has_airport[u-1] = true;    
        }
        for (int i=0; i < m; ++i){
            scanf("%d %d",&u,&v);
            u--,v--;
            G[u].push_back(v);
            G[v].push_back(u);    
        }
        scanf("%d",&q);
        printf("Case %d:\n",cases);
        for (int i=0; i < q; ++i){
            scanf("%d %d",&u,&v);
            u--,v--;
            res = dijkstra(u,v);
            printf("%d\n",res);    
        }
        putchar('\n');        
    }    
    
    return 0;    
}
