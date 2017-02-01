#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAX = 10002;

int len[MAX];
int ord[MAX];
char w[MAX][22];
char sw[MAX][22];
vector<int> G[MAX];
int L[MAX];
int next[MAX];
int n;

const int KB = 1024;
const int MAXN = 256*KB;
struct node {
  int w;
  int flag;
  node *edge[26];
  void clear(){
	 	w = -1;
		flag = 0;
  }
} mem[ MAXN ];

int used = 0;

struct Trie {
  node *root;
  Trie(){
	 used = 0;
	 mem[ used ].clear();
	 root = &(mem[ used ]);
  }
  void insert(char *s,int pos){
		node *act = root;
		int where;
		for (int i=0; s[i]; ++i){
		  where = s[i] - 'a';
		  if ((act->flag >> where) & 1) act = act->edge[ where ];
		  else { act->flag |= (1<<where); used++; mem[used].clear(); act->edge[ where ] = &(mem[ used ]); act = act->edge[ where ]; };
		}
		act->w = pos;
  }
  int search(char *s,int skip){
		node *act = root;
		int where;
		for (int i=0; s[i]; ++i){
		  if (i==skip) continue;
		  where = s[i] - 'a';
		  if ((act->flag >> where) & 1) act = act->edge[ where ]; 
		  else return -1;
		}
		return act->w;
  }
  void clear(){
		used = 0;
		mem[ used ].clear();
		root = &(mem[ used ]);
  }
};

bool cmp(const int &a,const int &b){
  return len[ a ] < len[ b ];
}

void count_sort(int x){
  int f[26]={0};
  int i;
  int p;
  for (i=0; w[x][i] ; ++i)
	 f[ w[x][i] - 'a' ]++;
  for (i=0,p=0; i < 26 ; ++i){
	 while ( f[i] ){
		sw[x][p++] = ('a' + i);
		f[i]--;
	 }
  }
  sw[x][p] = '\0';
}

int dfs(int u){
  L[u] = 1;
  int maxi = 0;
  int i,v;
  for (i=0; i < G[u].size(); ++i){
	 v = G[u][i];
	 if ( !L[ v ] ) dfs(v);
	 if (maxi < L[v]){ maxi = L[v]; next[u] = v; }
  }
  L[u] = 1 + maxi;
  return L[u];
}

int main(){
  
  int runs;
  Trie t;
  int i,j,k;
  int u;

  scanf("%d",&runs);
  while (getchar() != '\n');
  while (getchar() != '\n');
  while (runs--){
	 n = 0;
	 while (gets(w[n])){
		if (!w[n][0]) break;
		len[n] = strlen(w[n]);
		count_sort(n);
		ord[n] = n;
		next[n] = -1;
		L[n] = 0;
		n++;
	 }
	 sort(ord,ord+n,cmp);
	 t.insert( sw[ ord[0] ] , ord[0] );
	 for (k=1; k < n; ++k){
		i = ord[k];
		for (j=0; j < len[i]; ++j){
		  u = t.search( sw[i] , j );
		  if ( u >= 0 ){ G[u].push_back(i); }
		}
		t.insert(sw[i],i);
	 }
	 int maxi = 0;
	 int seed;
	 for (i=0; i < n; ++i)
		if (!L[i]){ 
		  dfs(i);
		  if ( L[i] > maxi ){ seed = i; maxi = L[i]; }
		}
	 do {
		puts(w[seed]);
		seed = next[seed];
	 }
	 while ( seed >= 0 );
	 if (runs){
		  for (i=0; i < n; ++i) G[i].clear();
		  t.clear();
		  putchar('\n');
	 }
  }
  return 0;
}