#include<cstdio>
#include<set>
using namespace std;

const int ZERO = 32000;
char dp[102][64005];
int v[105];

inline int abs(int x){ return x<0? -x:x; }

void print_path( int p , int x ){
  if ( p==0 ){ printf("%d",v[0]); }
  else {
	 int prev,t;
	 if ( dp[p][x] == '+' ){
		prev = x - v[p];
	 }
	 else if ( dp[p][x] == '-' ){
		prev = x + v[p];
	 }
	 else if ( dp[p][x] == '*' ){
		t = x - ZERO;
		t /= v[p];
		prev = t + ZERO;
	 }
	 else if ( dp[p][x] == '/' ){
		t = x - ZERO;
		t *= v[p];
		prev = t + ZERO;
	 }
	 print_path( p-1 , prev );
	 printf("%c%d",dp[p][x],v[p]);
  }
}

int main(){

  int runs;
  int n;
  int last;
  int x;
  int next;
  int t;
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d",&n);
	 for (int i=0; i < n; ++i) scanf("%d",v+i);
	 scanf("%d",&last);
	 last += ZERO;
	 for (int i=0; i < n; ++i)
		for (int j=0; j <= 64000; ++j)
		  dp[i][j] = -1;
	 set<int> state[2];
	 state[0].insert( v[0] + ZERO );
	 dp[0][ v[0] + ZERO ] = 0;
	 x = 0;
	 for (int i=1; i < n; ++i){
		state[1-x].clear();
		for (set<int>::iterator it = state[x].begin(); it != state[x].end() ; it++){
		  t = *it - ZERO;
		  if ( ( abs(t) % abs(v[i]) ) == 0 ){
			 next = (t/v[i]) + ZERO;
			 if ( next >= 0 && next <= 64000 ){
				state[1-x].insert(next);
				dp[i][next] = '/';
			 }
		  }
		  next = *it + v[i];
		  if ( next >= 0 && next <= 64000 ){
			 state[1-x].insert(next);
			 dp[i][next] = '+';
		  }
		  next = *it - v[i];
		  if ( next >= 0 && next <= 64000 ){
			 state[1-x].insert(next);
			 dp[i][next] = '-';
		  }
		  t = *it - ZERO;
		  next = (t * v[i]) + ZERO;
		  if ( next >= 0 && next <= 64000 ){
			 state[1-x].insert(next);
			 dp[i][next] = '*';
		  }
		}
		x = 1 - x;
	 }
	 if (dp[n-1][last] == -1) puts("NO EXPRESSION");
	 else  { print_path( n-1 , last ); printf("=%d\n",last-ZERO); }
  }
  return 0;
}