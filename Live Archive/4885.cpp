#include<cstdio>
#include<cstring>
#include<climits>
int n,m;
int pos[150][150];
int neg[150][150];
int d[150];
struct edge{
  int u,v,w;
};

edge E[45005];

void read_constraints(){
  char a[50];
  char b[50];
  int u,v,w;
  scanf("%s %d",a,&u); scanf("%s %s",a,b);
  if ( b[0] == 'a' ){
	 scanf("%s %d %s",a,&w,b); scanf("%s %s",a,b);
	 scanf("%s %d",a,&v);
	 if (neg[u][v] > -w) neg[u][v] = -w;
  }
  else {
	 scanf("%d %s %s",&w,a,b);  scanf("%s %s",a,b); scanf("%s %s",a,b);
	 scanf("%s %d",a,&v);
	 if ( pos[v][u] < 0 ) pos[v][u] = w;
	 else if ( pos[v][u] > w ) pos[v][u] = w;
	 if ( neg[u][v] > 0 ) neg[u][v] = 0;
  }
  //printf("u = %d v = %d  w = %d\n",u,v,w);
}

void init(){
  for ( int i=1; i <= n; ++i )
	 for ( int j=1; j <= n; ++j ){
		pos[i][j] = -1; neg[i][j] = 1;
	 }
}

int main(){
  int u,v,w;
  while ( scanf("%d",&n) && n ){
	 scanf("%d",&m);
	 init();
	 for ( int i=0; i < m; ++i ) read_constraints();
	 m = 0;
	 for ( int i=1; i <= n; ++i ){
		 E[m].u = 0; E[m].v = i; E[m].w = 0; m++;
	 }
	 for ( int i=1; i <= n; ++i )
		for ( int j=1; j <= n; ++j ){
		  if ( pos[i][j] >= 0 ){
			 E[m].u = i; E[m].v = j; E[m].w = pos[i][j]; m++;
 		  }
		  if ( neg[i][j] <= 0 ){
			 E[m].u = i; E[m].v = j; E[m].w = neg[i][j]; m++;
		  }
		}
	 for ( int i=1; i <= n; ++i ) d[i] = INT_MAX;
	 d[0] = 0;
	 for ( int i=1; i <= n; ++i ){
		for ( int j=0; j < m; ++j ){
		  u = E[j].u; v = E[j].v; w = E[j].w;
		  if ( d[u] < INT_MAX && (d[u] + w < d[v]) ){
			 d[v] = d[u] + w;
		  }
		}
	 }
	 //Detecting cycle
	 bool cycle = false;
	 for ( int j=0; j < m && !cycle; ++j ){
		  u = E[j].u; v = E[j].v; w = E[j].w;
		  if ( d[u] + w < d[v] ){ cycle = true; }
	 }
	 if ( cycle ) puts("Impossible.");
	 else {
		int mini = INT_MAX;
		int maxi = -INT_MAX;
		int gap;
		for ( int i=1; i<= n; ++i ){
		  if ( d[i] < mini ) mini = d[i];
		  if ( d[i] > maxi ) maxi = d[i];
		}
		gap = 1 - mini;
		if ( (maxi+gap) >= 1000000 ){
		  puts("Impossible.");
		  continue;
		}
		printf("%d",d[1]+gap);
		for ( int i=2; i <= n; ++i ) printf(" %d",d[i]+gap);
		putchar('\n');
	 }
  }
  return 0;
}