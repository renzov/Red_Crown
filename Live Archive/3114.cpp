#include<cstdio>
#include<queue>
#include<climits>
using namespace std;

int n,m;
int d[55][55];
int res[55];

int main(){
  int u,v,w,k;
  int best;
  int cut;
  int a,b;
  int n,x,gap;
  int total;

  while ( scanf("%d %d",&n,&m) != EOF ){
	 for ( int i=0; i < n; ++i )
		for ( int j=0; j < n; ++j )
		  d[i][j] = INT_MAX;
	 for ( int i=0; i<m; ++i ){
		scanf("%d %d %d",&u,&v,&w);
		u--,v--;
		if ( d[u][v] > w ) d[u][v] = w;
		if ( d[v][u] > w ) d[v][u] = w;
	 }
	 for ( int i=0; i < n; ++i ) d[i][i] = 0;
	 //Floyd
	 for ( k=0; k < n; ++k )
		for ( int i=0; i < n; ++i ){
		  if ( d[i][k] < INT_MAX ){
			 for ( int j=0; j < n; ++j ){
				if ( d[k][j] < INT_MAX && d[i][j] > (d[i][k]+d[k][j]) )
				   d[i][j] = d[i][k] + d[k][j];
			 }
		  }
		}

	 best = INT_MAX;
	 priority_queue< pair<int,int> > q;
	 a = 0;
	 b = 1;
	 for ( int i=0; i < n; ++i )
		for ( int j=i+1; j < n; ++j ){
			 total = 0;
			 for ( k=0; k < n; ++k ) 
				if ( k != i && k != j ){ 
				  total += 2*(n-1)*d[k][i];
				  q.push( make_pair( d[k][i] - d[k][j] , k ) );
				}
			 x = n-1;
			 while ( !q.empty() ){
				k = q.top().second; q.pop();
				total -= 2*(n-1)*d[k][i];
				total += 2*(n-1)*d[k][j];
				x--;
				gap = 2*(n-x)*x*d[i][j];
				if ( (total + gap) < best ){
				  best = total + gap; a = i; b = j;
				  cut = x;
				}
			 }
		}
		
		for ( int i=0; i < n; ++i ){
		  res[i] = a + 1;
		}
		res[a] = res[b] = 0;
		for ( k=0; k < n; ++k ) 
		  if ( k != a && k != b ){ 
			 q.push( make_pair( d[k][a] - d[k][b] , k ) );
		  }
		x = n-1;
		while ( !q.empty() && x != cut){
			 k = q.top().second; q.pop();
			 x--;
			 res[k] = b+1;
		}
		printf("%d",res[0]);
		for ( int i=1; i < n; ++i )
		  printf(" %d",res[i]);
		putchar('\n');
  }
  return 0;
}