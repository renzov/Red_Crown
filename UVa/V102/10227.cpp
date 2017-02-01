#include<cstdio>
#include<bitset>
using namespace std;
int p[105];
int rank[105];
bool used[105];
bitset<101> b[105];
void make_set(int x){ used[x] = false; b[x].reset(); p[x] = x; rank[x] = 0; }
int find_set(int x){ x!=p[x]? (p[x]=find_set(p[x])):p[x]; }
void link(int x,int y){
  (rank[x]>rank[y]) ? (p[y]=x):(p[x]=y);
  if (rank[x]==rank[y]) rank[y]++;
}

int main(){

  int runs;
  int P,T;
  int x,y;
  char line[105];
  scanf("%d",&runs);
  while (runs--){
		scanf("%d %d",&P,&T);
		for (int i=0; i < P; ++i){
		  make_set(i);
		}
		while (getchar() != '\n');
		while (gets(line)){
			 if (!line[0]) break;
			 sscanf(line,"%d %d",&x,&y);
			 x--,y--;
			 b[x].set(y);
		}
		int res = 0;
		for (int i=0; i<P; ++i){
		  if (!used[i]){
			 used[i] = true;
			 res++;
			 for (int j=i+1; j < P; ++j){
				  x = find_set(i);
				  y = find_set(j);
				  if (!used[j] && x != y && b[x] == b[y]){
					 used[j] = true;
					 link(x,y);
				  }
			 }
		  }
		}
		printf("%d\n",res);
		if (runs) putchar('\n');
  }

  return 0;
}