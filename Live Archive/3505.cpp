#include<cstdio>
#include<vector>
#include<climits>
#include<algorithm>
using namespace std;

int p[1005];
void make_set(int x){ p[x] = x; }
int find_set(int x){ return x!=p[x]? (p[x]=find_set(p[x])):x; }
void merge( int x , int y ){ p[y] = x; }
struct point{
  int x,y;
};
point P[1001];

struct edge{
  int x,y,w;
  edge(){}
  edge(int X,int Y,int W){ x = X; y = Y; w = W; }
  bool operator<( const edge &that ) const { return w < that.w; }
};

inline int sq_dist( int i ,int j ){
  return (P[i].x - P[j].x)*(P[i].x - P[j].x) + (P[i].y - P[j].y)*(P[i].y - P[j].y);
}

edge E[ 1001*1001 ];
int n,m,q;
vector<int> S[10];
int C[10];

int constraint_mst( int mask ){
  for ( int i=0; i<n; ++i ) make_set(i);
  int nset = n;
  int res = 0;
  int x,y;
  for ( int i=0; i < q; ++i ){
	 if ( (mask >> i)&1 ){
		res += C[i];
		for ( int j=0; j < S[i].size() - 1; ++j ){
		  x = find_set( S[i][j] );
		  y = find_set( S[i][j+1] );
		  if ( x!=y ){ nset--; merge(x,y); }
		}
	 }
  }
  for ( int i=0; i < m && nset > 1; ++i ){
		x = find_set(E[i].x);
		y = find_set(E[i].y);
		if ( x!=y ){ nset--; merge(x,y); res+=E[i].w; }
  }
  return res;
}

int main(){

  int runs;
  int s;
  int res;
  int best;
  scanf("%d",&runs);
  
  while ( runs-- ){
	 scanf("%d %d",&n,&q);
	 for ( int i=0; i < q; ++i ) S[i].clear();
	 for ( int i=0; i < q; ++i ){
		scanf("%d %d",&s,C+i);
		S[i].resize(s);
		for ( int j=0; j < s; ++j ){ scanf("%d",&S[i][j]); S[i][j]--; }
	 }
	 m = 0;
	 for ( int i=0; i < n; ++i ){
		scanf("%d %d",&P[i].x,&P[i].y);
		for ( int j = 0 ; j < i; ++j ){
		  E[m].x = i; E[m].y = j; E[m].w = sq_dist( i , j ); m++;
		}
	 }
	 sort( E , E + m );
	 best = INT_MAX;
	 for ( int i=0; i < (1<<q); ++i ){
		res = constraint_mst( i );
		if ( res < best ) best = res; 
	 }
	 printf("%d\n",best);
	 if ( runs ) putchar('\n');
  }
  

  return 0;
}