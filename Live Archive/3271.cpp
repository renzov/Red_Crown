#include<cstdio>
#include<queue>
#include<climits>
#include<vector>
#include<algorithm>
using namespace std;

int n;
int deg[ 25 ];
int G[ 25 ][ 25 ];
int C[ 25 ][ 25 ];
int nj;
int J[ 15 ];
int root;
int mask;
int no_elim;
int pre[ 25 ];

int bp[25];
int bmask;
int best;

struct triple{
  int u,v,w;
  triple(){};
  triple(int U,int V,int W){ u = U; v = V; w = W; }
  bool operator<( const triple &that ) const {
	 return w >= that.w;
  }
};

priority_queue< triple > q;

void backtrack( int pos ){
  
  int i;
  int u,v,w;
  int c1,c2;
  int cost;
  
  for ( mask=1; mask < (1<<n); ++mask ){
	 if ( (no_elim & mask) == no_elim ){
			 for ( i=0; i < n; ++i ){ pre[i] = -1; }
			 q.push( triple( -2 , root, 0 ) );
			 cost = 0;
			 while ( !q.empty() ){
				u = q.top().u; 
				w = q.top().w; 
				v = q.top().v;
				q.pop();
				if ( pre[v] != -1 ) continue;
				cost += w;
				pre[v] = u; u = v;
				for ( i=0; i < deg[u]; ++i ){
				  v = G[ u ][ i ]; w = C[ u ][ i ];
				  if ( ((mask>>v)&1) && pre[v] == -1 ) q.push( triple(u,v,w) );
				}
			 }
			 bool ok = true;
			 for ( i=0; i < nj && ok; ++i ) ok &= (pre[ J[i] ] != -1);
			 if ( ok ){
				if ( cost < best ){
				  bmask = mask; best = cost;
				  for ( i=0; i < n; ++i ) bp[i] = pre[i];
				}
				else if ( cost == best ){
				  c1 = __builtin_popcount( mask ); c2 = __builtin_popcount( bmask );
				  if ( c1 <  c2 ){
					 bmask = mask;
					 for ( i=0; i < n; ++i ) bp[i] = pre[i];
				  }
				  else if ( c1 == c2 && mask < bmask ){
					 bmask = mask;
					 for ( i=0; i < n; ++i ) bp[i] = pre[i];
				  }
				}
			 }
	 }
  }
}

int main(){
  int i;
  int m;
  int u,v,w;
  int cases = 0;
  while ( scanf("%d",&n) && n>0 ){
	 cases++;
	 for ( i=0; i < n; ++i ) deg[i] = 0;
	 no_elim = 0;
	 scanf("%d",&root); root--;
	 no_elim |= ( 1<<root );
	 scanf("%d",&m);
	 for ( i=0; i < m; ++i ){
		scanf("%d %d %d",&u,&v,&w);
		u--,v--;
		G[ u ][ deg[u] ] = v;
		G[ v ][ deg[v] ] = u;
		C[ u ][ deg[u] ] = C[ v ][ deg[v] ] = w;
		deg[u]++,deg[v]++;
	 }
	 scanf("%d",&nj);
	 for ( i=0; i < nj; ++i ){ scanf("%d",J+i); J[i]--; no_elim |= (1<<J[i]); }
	 mask = 0;
	 best = INT_MAX;
	 backtrack( 1 );
	 printf("Case %d: distance = %d\n",cases,best);
	 for ( i=0; i < nj; ++i ){
		u = J[i];
		printf("   ");
		while ( u != root ){
		  v = bp[u];
		  printf("%d-",u+1);
		  u = v;
		}
		printf("%d\n",root+1);
	 }
	 putchar('\n');
  }
  return 0;
}