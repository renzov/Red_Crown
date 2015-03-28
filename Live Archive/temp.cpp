#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <list>
#include <queue>
#include <string>

using namespace std;

#define loop(a, b) for(a = 0; a < b; ++a)
#define MAX (int(1e5)+4)

vector<int> e[MAX];
int ndfs[MAX], lp[MAX];
bool emCicloImpar[MAX];
int st[MAX], sp;
int cdfs, rootSons;
int raiz;

bool podeBuscar[MAX];
char cor[MAX];
int n;

void popComp(int u) {
        int v;
        
        memset(podeBuscar, 0, n*sizeof(podeBuscar[0]));
        while((v = st[--sp]) != u) {
                podeBuscar[v] = 1;
                //printf("%d ", v+1);
        }

    	podeBuscar[u] = 1;
        //printf("%d\n", u+1);

        queue <int> fila;

        memset(cor, -1, n*sizeof(cor[0]));
        fila.push(u);
        cor[u]=1;

        while (!fila.empty()) {
                v = fila.front();
                fila.pop();

                int size = e[v].size();
                for (int i=0; i<size; i++) {
                        int w = e[v][i];

                        if (!podeBuscar[w])
                                continue;

                        if (cor[w] == -1) {
                                cor[w] = cor[v]^1;
                                fila.push(w);
                        }
                        else if (cor[w] == cor[v]) {
                                for (i=0; i<n; ++i) {
                                        if (podeBuscar[i])
                                                emCicloImpar[i] = 1;
                                }
                                return;
                        }
                }
        }
}

void cbc(int u) {
        ndfs[lp[u] = st[sp++] = u] = cdfs++;
        int i = e[u].size(), v;

        while(i--) {
                if (ndfs[v = e[u][i]] == -1) {
                        if (ndfs[u] == 0)
                                rootSons++;
                        cbc(v);
                        if (ndfs[lp[u]] > ndfs[lp[v]])
                                lp[u] = lp[v];
                        else if (lp[v] == u) {
                				st[sp++] = u;
                                popComp(v);
                        }
                }
                else if (ndfs[lp[u]] > ndfs[v]){
                        lp[u] = v;
                }
        }
        if (e[u].size() == 0 and ndfs[u] == 0)
                popComp(raiz);

}

int main(void) {
        int ds;
        int m;
        int i;
        int u, v, ans;

        scanf("%d", &ds);
        while(ds--) {
                scanf("%d%d", &n, &m);

                loop(i, n) {
                        e[i].clear();
                        emCicloImpar[i] = 0;
                        ndfs[i] = -1;
                }

                loop(i, m) {
                        scanf("%d %d", &u, &v);
                        --u; --v;
                        e[u].push_back(v);
                        e[v].push_back(u);
                }

                loop(i, n)
                        if (ndfs[i] == -1) {
                                rootSons = cdfs = sp = 0;
                                raiz = i;
                                cbc(i);
                        }

                ans = 0;
                loop(i, n)
                        ans += (emCicloImpar[i]);

                printf("%d\n", ans);
        }

        return 0;
}
