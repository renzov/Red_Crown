#include<cstdio>
#include<algorithm>
using namespace std;
int ans[10];
int dp[10][1000];
int best;
const int INF = 1000000;
int find_length(int k,int Max,int n,int *tmp){
	 int limit = n*Max + 1;
	 int res = 0;
	 for (int i=0;i < limit; ++i) dp[0][i] =  i;
	 for (int i=1; i <= k; ++i){
		  for (int j=0; j < limit; ++j){
				if (j >= tmp[i]) dp[i][j] = min(dp[i-1][j],dp[i][j-tmp[i]] + 1);
				else dp[i][j] = dp[i-1][j];
		  }
	 }
	 for (int i=0; i < limit; ++i)
		if (dp[k][i] <= n) res = i;
		else break;
	 return res;
}

bool better(int kind,int *tmp){
  int s1=0,s2=0;
  for (int i=0; i < kind; ++i)
	 s1 += tmp[i],s2 += ans[i];
  return (s1 < s2);
}

void backtrack(int m,int used,int last,int tmpAns,int n,int *tmp){
  if (used==m){
		if (best < tmpAns){
			 best = tmpAns;
			 for (int i=0; i < used; ++i) ans[i] = tmp[i];
		}
		else if (tmpAns == best && better(used,tmp)){
			 best = tmpAns;
			 for (int i=0; i < used; ++i) ans[i] = tmp[i];
		}
		return;
  }
  int i= last + 1;
  while (i <= ((last+1)*n)){
		tmp[used] = i;
		int next = find_length(used,i,n,tmp); /* Usamos subset sum para calcular maxima longuitud 1..K que se puede obtener con las monedas */
		if (next <= tmpAns){ i++; continue; }
		tmp[used] = i;
		backtrack(m,used + 1,i,next,n,tmp);
		i++;
  }
}

int main(){
  int n,m;
  int tmp[10];
  while (scanf("%d %d",&n,&m) && (n || m)){
		for (int i=0; i < 9; ++i) ans[i] = INF;
		for (int i=0; i < 9; ++i){
			 for (int j=0; j < 1000; ++j)
				dp[i][j] = INF;
		}
		tmp[0] = 1;
		best = 0;
		for (int i=0; i <= n; ++i) dp[0][i] = i;
		backtrack(m,1,1,n,n,tmp);
		for (int i=0; i < m; ++i)
		  printf("%3d",ans[i]);
		printf(" ->%3d\n",best);
  }

  return 0;
}