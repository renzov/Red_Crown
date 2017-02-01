#include<cstdio>

using namespace std;

int p[10005];
int rank[10005];

void make_set(int x){
  p[x] = x;
  rank[x] = 0;
}

int find_set(int x){
  if (x!=p[x]) p[x] = find_set(p[x]);
  return p[x];
}

void link(int x,int y){
  if (rank[x] > rank[y]){
		p[y] = x;
  }
  else {
		p[x] = y;
		if (rank[y]==rank[x]) rank[y]++;
  }
}

void union_set(int x,int y){
  link(find_set(x),find_set(y));
}

int main(){

  
  int n,k,m;
  int u,v;
  int res = 0;

  scanf("%d %d %d",&n,&k,&m);
  for (int i=0; i<n; ++i) make_set(i);
  int left = n-1;
  for (int i=0; i < k && left; ++i){
	 scanf("%d %d",&u,&v);
	 u--,v--;
	 if (find_set(u)!=find_set(v)){
		union_set(u,v);
		left--;
	 }
  }
  for (int i=0; i < m && left; ++i){
	 scanf("%d %d",&u,&v);
	 u--,v--;
	 if (find_set(u)!=find_set(v)){
		union_set(u,v);
		left--;
		res++;
	 }
  }
  printf("%d\n",res);
  return 0;
}