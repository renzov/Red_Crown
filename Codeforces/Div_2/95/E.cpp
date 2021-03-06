#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN = 100000;

pair<int,int> q[MAXN+2];
int f[ 10 ] = {0};
int r[ MAXN + 2 ];
int c[ MAXN + 2 ];
int at[ MAXN + 2 ];
int diag1[ 2*MAXN + 2 ];
int diag2[ 2*MAXN + 2 ];

int main(){
  int n;
  int m;
  int x,y;
  int row,col;
  int idx;
  scanf("%d %d",&n,&m);
  for (int i=0; i<m; ++i){
	 scanf("%d %d",&x,&y);
	 x--,y--;
	 q[i].first = x;
	 q[i].second = y;
  }
  sort( q , q + m );
  memset(r,-1,sizeof(int)*n);
  memset(c,-1,sizeof(int)*n);
  memset(at,0,sizeof(int)*m);
  memset(diag1,-1,sizeof(int)*n*2);
  memset(diag2,-1,sizeof(int)*n*2);
  /* Proncess in row order */
  int cnt;
  for (int i=0; i < m; ++i){
	 cnt = 0;
	 row = q[i].first;
	 col = q[i].second;
	 if ( r[row] != -1 ){
		cnt++;
		idx = r[row];
		f[ at[idx] ]--;
		at[idx]++;
		f[ at[idx] ]++;
		r[row] = i; 
	 }
	 else { r[row] = i; }
	 if ( c[ col ] != -1 ){
		cnt++;
		idx = c[col];
		f[ at[idx] ]--;
		at[idx]++;
		f[ at[idx] ]++;
		c[col] = i;
	 }
	 else { c[col] = i; }
	 if (diag1[n-1 + col - row] != -1){
		cnt++;
		idx = diag1[n-1 + col - row];
		f[ at[idx] ]--;
		at[idx]++;
		f[ at[idx] ]++;
		diag1[n-1 + col - row] = i;
	 }
	 else { diag1[n-1 + col - row] = i; }
	 if ( diag2[col + row] != -1 ){
		cnt++;
		idx = diag2[col + row];
		f[ at[idx] ]--;
		at[idx]++;
		f[ at[idx] ]++;
		diag2[col + row] = i;
	 }
	 else { diag2[col + row] = i; }
	 f[ cnt ]++;
	 at[i] = cnt;
  }
  printf("%d",f[0]);
  for (int i=1;i < 9; ++i) printf(" %d",f[i]);
  putchar('\n');
  return 0;
}