#include<cstdio>
const int MAX = 100000;
int seg_tree[ MAX * 4 ];
int left[ MAX + 2 ];
int rigth[ MAX + 2 ];
int dfsnum = 0;
bool visited[ MAX + 2 ];

struct node{
  node *next;
  int vertex;
  node(){}
  node(int v,node *g){ vertex=v; next = g; }
};

node *G[MAX + 2 ] = {0};


void dfs(int u){
  visited[u] = true;
  left[ u ] = ++dfsnum;
  node *p = G[u];
  while (p){
		if (!visited[ p->vertex ]){
		  dfs( p->vertex );
		}
		p = p->next;
  }
  rigth[ u ] = dfsnum;
}

void build_tree(int n,int l,int r){
  seg_tree[n] = r - l + 1;
  if (l==r) return;
  int m = (l+r) >> 1;
  build_tree(n<<1,l,m); build_tree((n<<1) + 1,m+1,r);
}

void update(int n,int l,int r,int p){
  if (l==r){
	 seg_tree[n] = 1 - seg_tree[n];
	 return;
  }
  int m = (l + r) >> 1;
  if (p<=m) update(n<<1,l,m,p);
  else update((n<<1) + 1,m+1,r,p);
  seg_tree[n] = seg_tree[n<<1] + seg_tree[(n<<1) + 1];
}

int query(int n,int L,int R,int l,int r){
  if (l==L && r==R) return seg_tree[n];
  int M = (L + R) >> 1;
  if (r <= M) return query(n<<1,L,M,l,r);
  if (M < l) return query((n<<1)+1,M+1,R,l,r);
  return query(n<<1,L,M,l,M) + query((n<<1)+1,M+1,R,M+1,r);
}

int main(){
  int n;
  int m;
  int u,v;
  char c;
  node *p1;
  node *p2;
  scanf("%d",&n);
  build_tree(1,1,n);
  for (int i=0; i < n-1; ++i){
		scanf("%d %d",&u,&v);
		p1 = new node(u,G[v]);
		p2 = new node(v,G[u]);
		G[v] = p1;
		G[u] = p2;
  }
  dfs(1);
  scanf("%d",&m);
  for (int i=0; i < m; ++i){
	 scanf(" %c %d",&c,&u);
	 if ( c == 'Q' )
		  printf("%d\n",query(1,1,n,left[u],rigth[u]));
	 else 
		  update(1,1,n,left[u]);
  }
  return 0;
}