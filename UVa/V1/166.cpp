#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAX = 1001;

int v[6];
int dp[MAX];
int coin[] = {5,10,20,50,100,200};
int min_coins[MAX];

int main(){

  for (int i=0; i < MAX; ++i)
	 min_coins[i] = 999999999;
  min_coins[0] = 0;
  for(int i=0; i < 6; ++i){
    min_coins[coin[i]] = 1;
    for(int j=coin[i]; j < MAX; ++j) {
      min_coins[j] = min(min_coins[j], min_coins[j - coin[i]] + 1);
    }
  }


  bool fin;
  int x,y;
  int z;
  while (1){
	 fin = true;
	 for (int i=0; i < 6; ++i){ 
		scanf("%d",v+i);
		if (v[i] > 0) fin = false;
	 }
	 if (fin) break;
	 memset(dp,-1,sizeof(dp));
	 dp[0] = 0;
	 scanf("%d.%d",&x,&y);
	 z = x*100 + y;
	 for (int i=0; i < 6; ++i){
		  for (int j=z; j >= 0; --j){
				if (dp[j]==-1) continue;
				for (int k=1; k <= v[i] && ((j + k*coin[i]) < MAX); ++k){
					 if (dp[j + k*coin[i]]==-1 || ((dp[j] + k) < dp[ j + k*coin[i] ]))
						dp[ j + k*coin[i] ] = dp[j] + k;
				}
		  }
	 }
	 
	 int best = 999999999;
	 int tmp;
	 
	 for (int i=z; i < MAX; ++i){
		  if (dp[i] != -1){
				tmp = dp[i] + min_coins[ i - z ];
				if (best > tmp) best = tmp;
		  }
	 }
	 printf("%3d\n",best);
  }
  return 0;
}