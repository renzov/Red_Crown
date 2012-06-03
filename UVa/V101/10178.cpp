#include<cstdio>
int p[256];
int rank[256];
void make_set(int x){ p[x] = x; rank[x]=0; }
int find_set(int x){ return x!=p[x]? (p[x]=find_set(p[x])):p[x]; }
void link(int x,int y){
  if (rank[x] > rank[y]){
	 p[y] = x;
  }
  else {
	 p[x] = y;
	 if (rank[x] == rank[y]) rank[y]++;
  }
}

int main(){
  int N,E;
  char a,b;
  int u,v;
  int res;
  while (scanf("%d %d",&N,&E) != EOF ){
		res = 1;
		for (int i=0; i < 256; ++i){
		  make_set(i);
		}
		while(E--){
		  scanf(" %c %c",&a,&b);
		  u = find_set((int)a);
		  v = find_set((int)b);
		  if (u==v) res++;
		  else link(u,v);
		}
		printf("%d\n",res);
  }

  return 0;
}