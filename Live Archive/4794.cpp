#include<cstdio>
#include<cstring>
#define forn(i,n) for( int i=0; i < (int)(n); ++i )
int n;
int memo[1<<15][102];
int sum[1<<15];
int a[1<<15];
int solve(int c, int m);

inline int max(int x,int y){ return x>=y? x:y; }

bool backtrack(int pos, int t , int s,int m){
  if ( pos == n ){
	 if ( t == 0 || t == s ) return 0;
	 int b = s - t;
	 int sa = sum[t];
	 int sb = sum[b];
	 int total = sum[s];
	 int col = total / m;
	 int row = m;
	 int la,lb;
	 // Partition the chocolate
	 if ( sa % row == 0 ){
		la = sa / row;
		lb = sb / row;
		if ( solve(t, max(la,sa/la) ) && solve(b, max(lb,sb/lb) ) ) return 1; 
	 }
	 if ( sa % col == 0 ){
		la = sa / col;
		lb = sb / col;
		if ( solve(t,max(la,sa/la)) && solve(b,max(lb,sb/lb)) ) return 1;
	 }
	 return 0;
  }
  if ( backtrack(pos+1,t,s,m) ) return 1;
  if ( ((s>>pos)&1) && backtrack(pos+1,t|(1<<pos),s,m) ) return 1;
  return 0;
}

int solve( int c, int m ){
  if ( memo[c][m] != -1 ) return memo[c][m];
  if ( c == (c&-c) ){
	 return memo[c][m] = 1;
  }
  memo[c][m] = backtrack(0,0,c,m);
  return memo[c][m];
}

int main(){
  int r,c;
  int total;
  int cases = 0;
  while ( scanf("%d",&n) && n ){
	 cases++;
	 scanf("%d %d",&r,&c);
	 total = 0;
	 forn(i,n){ scanf("%d",a+i); total += a[i]; }
	 if ( total != (r*c) ){
		printf("Case %d: No\n",cases);
		continue;
	 }
	 forn(i,1<<n){
		sum[i] = 0; 
		forn(j,n){
		  if ( (i >> j)&1 ) sum[i] += a[j];
		}
	 }
	 memset(memo,-1,sizeof(memo));
	 if ( solve( (1<<n)-1 , max(r,c) ) )
		printf("Case %d: Yes\n",cases);
	 else 
		printf("Case %d: No\n",cases);
  }
  return 0;
}