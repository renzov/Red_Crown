#include<cstdio>
#include<climits>
using namespace std;

struct triple{
  int x,y;
};

triple p[100005];
long long dp[100005] = {0};
long long sp[100005] = {0};
int q[100005];
int w[100005];
int qf,qt;

inline int abs(int x){ return x<0? -x:x; }

int main(){
  int i,j,k;
  int runs;
  int n;
  int m;
  long long A,B;
  
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d",&m);
	 scanf("%d",&n);
	 sp[0] = 0; 
	 p[0].x = p[0].y = w[0] = 0;
	 for (i=1; i <= n; ++i){
		scanf("%d %d %d",&p[i].x,&p[i].y,&w[i]);
		sp[i] = abs( p[i].x - p[i-1].x ) + abs( p[i].y - p[i-1].y ) + sp[i-1]; 
		w[i] += w[i-1];
	 }
	 qf = qt = 0;
	 q[qt++] = 0;
	 for (i=1; i <= n; ++i){
		while ( qf < qt && ( w[i] - w[ q[qf] ] ) > m ) qf++;
		j = q[qf];
		dp[i] = (sp[i] - sp[j+1]) + dp[j] + abs( p[j+1].x - p[0].x ) + abs( p[j+1].y - p[0].y ) + abs( p[i].x - p[0].x ) + abs(p[i].y - p[0].y);
		if (i==n) break;
		B = dp[i] + abs(p[i+1].x - p[0].x) + abs(p[i+1].y - p[0].y) - sp[i+1];
		while (qf < qt){
		  j = q[qt-1];
		  A = dp[j] + abs(p[j+1].x - p[0].x) + abs(p[j+1].y - p[0].y) - sp[j+1];
		  if ( A >= B ) qt--;
		  else break;
		}
		q[qt++] = i;
	 }
	 printf("%lld\n",dp[n]);
	 if (runs) putchar('\n');
  }
  return 0;
}