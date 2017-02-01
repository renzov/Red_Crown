#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

struct edge{
  int x,y,w;
  edge(){}
  edge(int X,int Y,int W){ x = X; y = Y; w = W; }
  bool operator<(const edge &that) const {
	 return w < that.w;
  }
};

char line[1000];
edge E[26*26 + 5];
int res[30];
int p[30];

bool cmp(int a,int b){
  if ( E[a].w != E[b].w ) return E[a].w < E[b].w;
  if ( E[a].x != E[b].x ) return E[a].x < E[b].x;
  return E[a].y < E[b].y;
}

inline void make_set(int x){ p[x] = x; }
int find_set(int x){ return x==p[x]? x:(p[x]=find_set(p[x])); }
inline void union_set(int x,int y){ p[y] = x; }

int main(){
  int runs;
  char *ptr;
  int v,x,y;
  int i,j;
  int m,n,r;
  int cases=0;
  scanf("%d",&runs);
  while (runs--){
	 cases++;
	 scanf("%d",&n);
	 while (getchar() != '\n');
	 m = 0;
	 for (i=0; i < n; ++i){
		make_set(i);
		gets(line);
		ptr = strtok( line , " ," );
		for (j=0; j < n; ++j){
		  if ( j > i ){
			 v = atoi(ptr);
			 if (v) E[m++] = edge( i ,j , v );
		  }
		  ptr = strtok(NULL," ,");
		}
	 }
	 r = 0;
	 sort( E , E + m );
	 for (i=0,j=n-1;i < m && j > 0; ++i){
		x = find_set(E[i].x);
		y = find_set(E[i].y);
		v = E[i].w;
		if ( x != y ){
		  union_set( x , y );
		  j--;
		  res[r++] = i;
		}
	 }
	 sort(res,res + r,cmp);
	 printf("Case %d:\n",cases);
	 for (i=0; i < r; ++i){
		printf("%c-%c %d\n", (char)('A'+E[ res[i] ].x) , (char)('A'+E[ res[i] ].y) , E[ res[i] ].w );
	 }
  }
  return 0;
}