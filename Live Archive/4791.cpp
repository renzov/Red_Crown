#include<cstdio>
#include<cmath>

const double INF = 10e12;
struct point{
  int x,y;
};
point p[102];
double dp[102][2][102][2];
bool calc[102][2][102][2];
char move[102][2][102][2];
int b1,b2,n;

inline double Dist(int a,int  b){
  return sqrt( (p[a].x - p[b].x)*(p[a].x - p[b].x)*1.0 + (p[a].y - p[b].y)*(p[a].y - p[b].y)*1.0 );
}
inline int max(int a,int b){
  return a>=b? a:b;
}

void print_path(){
  int a[102];
  int b[102];
  int x = 0;
  int y = 0;
  int u,v;
  int next;
  int i;
  bool c1,c2;
  u = 0;
  v = 0;
  c1 = c2 = false;
  a[x++] = 0;
  b[y++] = 0;
  while ( u != (n-1) && v != (n-1) ){
	 next = max(u,v) + 1;
	 if ( move[u][c1][v][c2] == 1 ){
		u = next;
		a[x++] = next;
		if ( next == b1 || next == b2 ) c1 = true;
	 }
	 else {
		b[y++] = next;
		v = next;
		if ( next == b1 || next == b2 ) c2 = true;
	 }
  }
  if ( a[x-1] == (n-1) ){
	 for (i=0; i < x; ++i){
		if ( i > 0 ) putchar(' ');
		printf("%d",a[i]);
	 }
	 for (i=y-1; i >= 0 ; --i ){
		printf(" %d",b[i]);
	 }
  }
  else {
	 for (i=0; i < y; ++i){
		if ( i > 0 ) putchar(' ');
		printf("%d",b[i]);
	 }
	 for (i=x-1; i >= 0 ; --i ){
		printf(" %d",a[i]);
	 }
  }
}

double solve(int u,bool c1,int v,bool c2){
  if ( u == (n-1) && c1 && c2) return Dist(n-1,v);
  else if ( v == (n-1) && c1 && c2) return Dist(n-1,u);
  if ( v==(n-1) || u==(n-1) ) return INF;
  if ( calc[u][c1][v][c2] ) return dp[u][c1][v][c2];
  calc[u][c1][v][c2] = true;
  int next = max( u , v ) + 1;
  double a,b;
  if ( next != b1 && next != b2 ){
	 a = solve( next , c1 , v , c2 ) + Dist( u , next );
	 b = solve( u , c1 , next , c2 ) + Dist( v , next );
	 if ( a < b ){  dp[u][c1][v][c2] = a; move[u][c1][v][c2] = 1; }
	 else { dp[u][c1][v][c2] = b; move[u][c1][v][c2] = 2; }
  }
  else {
	 a = INF;
	 b = INF;
	 if ( !c1 ) a = solve( next , true , v , c2 ) + Dist( u , next );
	 if ( !c2 ) b = solve( u , c1 , next , true ) + Dist( v , next );
	 if ( a < b ){  dp[u][c1][v][c2] = a; move[u][c1][v][c2] = 1; }
	 else { dp[u][c1][v][c2] = b; move[u][c1][v][c2] = 2; }
  }
  return dp[u][c1][v][c2];
}

int main(){
  int i;
  int j;
  int runs = 0;
  while ( scanf("%d %d %d",&n,&b1,&b2) && n){
		runs++;
		for (i=0; i < n; ++i) scanf("%d %d",&p[i].x,&p[i].y);
		for (i=0; i < n; ++i)
		  for (j=0; j < n; ++j){
			 calc[i][0][j][0] = false;
			 calc[i][0][j][1] = false;
			 calc[i][1][j][0] = false;
			 calc[i][1][j][1] = false;
		  }
		solve(0,false,0,false);
		printf("Case %d: %0.2lf\n",runs,floor(dp[0][false][0][false]*100.0 + .5)/100);
		print_path();
		putchar('\n');
  }
  return 0;
}