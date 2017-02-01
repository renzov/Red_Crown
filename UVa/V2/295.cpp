#include<cstdio>
#include<cmath>
using namespace std;
int L,W,N;

struct point{
  double x,y;
  point(){}
  point( double X,double Y ){ x = X; y = Y; }  
};

bool lower;
bool upper;
double d[105][105];
point P[105];
bool visited[105];
double D;

double Dist(int a,int b){
  return sqrt( (P[a].x - P[b].x)*(P[a].x - P[b].x) + (P[a].y - P[b].y)*(P[a].y - P[b].y) );
}

void dfs(int u,int p){
  visited[u] = true;
  if ( ((double)W - P[u].y) <= (D/2.0) ) upper = true;
  for (int v=0; v < N && ( !lower || !upper ); ++v){
	 if ( v != u && v != p && !visited[v] && d[u][v] <= D)
		dfs(v,u);
  }
}

bool is_possible( double dim ){
  lower = upper = false;
  D = dim;

  for(int i=0; i < N; ++i) visited[i] = false;

  for (int i=0; i < N && ( !lower || !upper ) ; ++i){
	 if ( !visited[i] && P[i].y <= (D/2.0) ){
		lower = true;
		dfs( i , -1 );
	 }
  }
  return lower && upper;
}

int main(){
  int runs;
  scanf("%d",&runs);
  for (int k=1; k <= runs; ++k){
	 scanf("%d %d",&L,&W);
	 scanf("%d",&N);
	 for (int i=0; i<N; ++i){
		scanf("%lf %lf",&P[i].x,&P[i].y);
	 }
	 for (int i=0; i<N; ++i){
		d[i][i] = 0.0;
		for (int j=i+1; j < N; ++j){
		  d[i][j] = d[j][i] = Dist( i , j );
		}
	 }
	 if (L==0){
		printf("Maximum size in test case %d is %d.0000.\n",k,W);
		continue;
	 }
	 double r = (double)W;
	 double l = 0.0;
	 double m;
	 for (int i=0; i < 100; ++i){
		m = (l+r)/2.0;
		if ( is_possible( m ) ) r = m;
		else l = m;
	 }
	 l = floor( l*10000.0 + .5)/10000.0;
	 printf("Maximum size in test case %d is %0.4lf.\n",k,l);
  }
  return 0;
}