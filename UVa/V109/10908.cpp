#include<cstdio>
#include<numeric>
#include<algorithm>
using namespace std;

int M[105][105];
int dp[105][105][105];
int n,m,q;
int res;

bool its_ok(int y,int x,int rad){
  int a = x - rad;
  int b = x + rad;
  int mask = dp[y-rad][a][b];
  for (int j=(y-rad + 1); j <= (y + rad); ++j){
	 mask |= dp[j][a][b];
	 if (__builtin_popcount(mask) > 1) return false;
  }
  return true;
}

int find_best(int y,int x){
  int l = 0;
  int r = min( min(y,(n-1)-y) , min(x,(m-1)-x) );
  for (int i=l+1 ; i <= r; i++){
	 if (its_ok(y,x,i)){
		l = i;
	 }
	 else break;
  }
  
  return l;
}

int main(){
  int runs;
  int r,c;
  char color;
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d %d %d",&n,&m,&q);
	 printf("%d %d %d\n",n,m,q);
	 for (int i=0; i < n; ++i)
		for (int j=0; j < m; ++j){
			 scanf(" %c",&color);
			 M[i][j] = 1 << (color-'a');
		}
	 for (int i=0; i < n; ++i){
		  for (int j=0; j < m; ++j){
				dp[i][j][j] = M[i][j];
				for (int k=j+1; k < m; ++k){
					 dp[i][j][k] = dp[i][j][k-1] | M[i][k];
				}
		  }
	 }
	 
	 for (int i=0; i < q; ++i){
		  scanf("%d %d",&r,&c);
		  res = find_best(r,c);
		  printf("%d\n",2*res + 1);
	 }
  }

  return 0;
}