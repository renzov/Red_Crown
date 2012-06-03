#include<cstdio>
#include<climits>
#include<cstring>
int dp[11][11][11][11][11][11]={0};
bool calc[11][11][11][11][11][11]={0};
int C[8][8];
int H[8][8];
int m;

int solve(int *type){
  if ( calc[ type[1] ][ type[2] ][ type[3] ][ type[4] ][ type[5] ][ type[6] ] ) return dp[ type[1] ][ type[2] ][ type[3] ][ type[4] ][ type[5] ][ type[6] ];
  calc[ type[1] ][ type[2] ][ type[3] ][ type[4] ][ type[5] ][ type[6] ] = true;
  int t = 0;
  for (int i=1; i <= m; ++i) t += type[i];
  if (t==1){
	 dp[ type[1] ][ type[2] ][ type[3] ][ type[4] ][ type[5] ][ type[6] ] = 0;
	 return dp[ type[1] ][ type[2] ][ type[3] ][ type[4] ][ type[5] ][ type[6] ];
  }
  int min = INT_MAX,tmp;
  for (int i=1; i <= m; ++i)
	 for (int j=1; j <= m ; ++j){
		if ( (i!=j) && type[i] > 0 && type[j] > 0 ){
		  type[i]--,type[j]--;
		  type[ C[i][j] ]++;
		  tmp = solve( type );
		  if ( tmp < INT_MAX && (tmp + H[ i ][ j ]) < min ) min = tmp + H[ i ][ j ];
		  type[i]++,type[j]++;
		  type[ C[i][j] ]--;
		}
	 }
  for (int i=1; i<=m; ++i){
	 if (type[i] > 1){
		type[i]-=2;
		type[ C[i][i] ]++;
		tmp = solve( type );
		if ( tmp < INT_MAX && (tmp + H[ i ][ i ]) < min ) min = tmp + H[ i ][ i ];
		type[ C[i][i] ]--;
		type[i]+=2;
	 }
  }
  dp[ type[1] ][ type[2] ][ type[3] ][ type[4] ][ type[5] ][ type[6] ] = min;
  return dp[ type[1] ][ type[2] ][ type[3] ][ type[4] ][ type[5] ][ type[6] ];
}

int main(){
  int n;
  int runs;
  int c;
  char ch;
  int type[8] = {0};
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d",&m);
	 for (int i=1; i <= m; ++i)
		for (int j=1; j <= m; ++j)
			 scanf("%d %d",&C[i][j],&H[i][j]);
	 scanf("%d",&n);
	 for (int i=0; i < n; ++i){
		scanf("%d",&c);
		type[c]++;
	 }
	 printf("%d\n",solve(type));
	 if (runs){
		memset(type,0,sizeof(type));
		memset(calc,0,sizeof(calc));
	 }
	 scanf(" %c",&ch);
  }
  
  return 0;
}