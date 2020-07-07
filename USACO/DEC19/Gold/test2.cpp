#include<bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define ll long long
#define ld long double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pld pair<ld,ld>
const int MAXM = 30, MAXN = 108, INF=1e9+7;
int n,m,k,dist[MAXM][MAXM],dp[MAXN][MAXN][MAXM];
string s;
int fazdp(int pos, int atual, int c){//posicao, tamanho do bloco atual, caractere atual
    if(pos == 0)return 0;//acabou (caso base)
    if(dp[pos][atual][c] < INF)return dp[pos][atual][c];
    int ret = dist[s[pos-1] - 'a'][c];
    if(atual==1){//vamos mudar de bloco
        int aux = INF;
        for(int tam=k; tam<=pos; tam++){
            for(int cc=0; cc<m; cc++){//quem vai ser o caractere do novo bloco?
                aux = min(aux, fazdp(pos-1, tam, cc));
            }
        }
        ret += aux;
    }else{//continua mesmo bloco
        ret += fazdp(pos-1, atual-1, c);
    }
    return dp[pos][atual][c] = ret;
}
int main(){
    fastio;
	for(int k=0; k<MAXN; k++)
        for(int i=0; i<MAXN; i++)
            for(int j=0; j<MAXM; j++)      
                dp[k][i][j] = INF;
    cin>>n>>m>>k>>s;
    for(int i=0; i<m; i++)
        for(int j=0; j<m; j++)
            cin>>dist[i][j];
    for(int k=0; k<n; k++)
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    int ans = INF;
    for(int ult_bloco=k; ult_bloco<=n; ult_bloco++){
        for(int c=0; c<m; c++){
            ans = min(ans, fazdp(n,ult_bloco,c));
        }
    }
    cout<<ans<<endl;
}
