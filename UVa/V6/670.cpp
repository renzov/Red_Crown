#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
const int MAXN = 128;
const double EPS = 1e-12;
vector<int> L[MAXN];		//Left-set of vertices
bool visited[MAXN];		//Mark visited on Right vertices
int LA[MAXN];				// Left Assignment
int RA[MAXN];				// Right Assignment
int n,m;						// n = size(Left) , m = size(Right)

int XL[MAXN];
int XR[MAXN];
int YL[MAXN];
int YR[MAXN];

bool AlternatePath( int u ){
  int v;
  for ( int i=0; i < L[u].size(); ++i ){
	 v = L[u][i];
	 if ( visited[v] ) continue;
	 visited[v] = true;
	 if ( RA[v] < 0 || AlternatePath( RA[v] ) ){ //Found valid assignment
		RA[v] = u;
		LA[u] = v;
		return true;
	 }
  }
  return false;
}

double get_dist_sq( double x1,double y1, double x2, double y2 ){
  return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

int main(){
  int runs;
  int x;
  double a,b,c;
  scanf("%d",&runs);
  while ( runs-- ){
	 scanf("%d %d",&n,&m);
	 for ( int i=0; i < n; ++i ){
		scanf("%d %d",XL+i,YL+i);
		L[i].clear();
		LA[i] = -1;
	 }
	 for ( int i=0; i < m; ++i ){
		scanf("%d %d",XR+i,YR+i);
		RA[i] = -1;
	 }
	 // Set the Graph
	 for ( int i=0; i < (n-1); ++i ){
		for ( int j=0; j < m; ++j ){
		  a = get_dist_sq( (double)XL[i] , (double)YL[i] , (double)XR[j] , (double)YR[j] );
		  b = get_dist_sq( (double)XL[i+1], (double)YL[i+1] , (double)XR[j] , (double)YR[j] );
		  c = get_dist_sq( (double)XL[i+1] , (double)YL[i+1] , (double)XL[i] , (double)YL[i] );
		  if ( (2*c + EPS) > (a+b) ){
			 L[i].push_back(j);
		  }
		}
	 }
	 int res = 0;
	 for ( int i=0; i < n; ++i ){
		fill( visited , visited + n , false );
		if ( AlternatePath(i) ) res++;
	 }
	 printf("%d\n",n+res);
	 for ( int i=0; i < n; ++i ){
		if ( i ) putchar(' ');
		printf("%d %d",XL[i],YL[i]);
		if ( LA[i] >= 0 ){
		  x = LA[i];
		  printf(" %d %d",XR[x],YR[x]);
		}
	 }
	 putchar('\n');
	 if ( runs ) putchar('\n');
  }
  return 0;
}