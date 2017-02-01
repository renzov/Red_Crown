#include<cstdio>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;
#define forn(i,n) for (int i=0; i < (int)(n); ++i)
int H,A;
int T[255][255];
int C[255];
int TC[255];
int B[255];
int TB[255];
int bound[255][255];

int RA[255];
int LA[255];
bool vis[255];
int X;

bool alternate(int u){
  forn(v,A){
	 if ( bound[u][v] <= (X-T[u][v]) ){
		if ( vis[v] ) continue;
		vis[v] = true;
		if ( RA[v] < 0 || alternate(RA[v]) ){
		  RA[v] = u; LA[u] = v; return true;
		}
	 }
  }
  return false;
}

bool feasible( int cap ){
  fill(LA,LA+H,-1);
  fill(RA,RA+A,-1);
  int res = 0;
  X = cap;
  forn(i,H){
	 fill(vis,vis+A,false);
	 if ( alternate(i) ) res++;
	 if ( res >= A ) break;
  }
  return res >= A;
}

int get_time( int a , int mx , int b , int my , int ex ){
  int num = b + my*ex - a;
  int den = mx - my;
  if ( den <= 0 ){
	 if ( num <= 0 ) return 0;
	 return INT_MAX;
  }
  else {
	 if ( num <= 0 ) return 0;
	 return ( num % den )? ( num/den + 1 ):(num/den);
  }
}

int main(){
  while ( scanf("%d %d",&H,&A) && ( H && A ) ){
	 forn(i,H) scanf("%d %d",C+i,TC+i);
	 forn(i,A) scanf("%d %d",B+i,TB+i);
	 forn(i,H)
		forn(j,A){
		  scanf("%d",&T[i][j]);
		  bound[i][j] = get_time( C[i] , TC[i] , B[j] , TB[j] , T[i][j] );
		}
	 if ( H < A ){ puts("IMPOSSIBLE"); continue; }
	 int l,r,m;
	 r = 1000000;
	 l = 0;
	 if ( feasible(l) ) printf("0\n");
	 else if ( !feasible(r) ) puts("IMPOSSIBLE");
	 else {
		while ( (r-l) > 1 ){
		  m = ( l + r ) >> 1;
		  if ( feasible(m) ) r = m;
		  else l = m;
		}
		printf("%d\n",r);
	 }
  }
  return 0;
}