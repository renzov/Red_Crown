#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m;
int v[35];
long long S[1005];

int main(){
  int runs;
  int sum;
  int last;
  int upper,lower;
  long long res;
  int cases = 0;
  scanf("%d",&runs);
  while (runs--){
	 cases++;
	 scanf("%d %d",&n,&m);
	 for (int i=0; i < n; ++i) scanf("%d",v+i);
	 sort(v,v+n);
	 last = 0;
	 sum = 0;
	 res = 0;
	 for (int i=0; i < n && sum < m; ++i){
		if (last < v[i]){
		  upper = m - sum - last;
		  lower = m - sum - v[i] + 1;
		  if (lower <= 0){ lower = (sum == 0)? 1:0; }
		  memset(S,0,sizeof(long long)*(m+1));
		  S[0] = 1;
		  for (int j=i; j < n; ++j){
			 for (int k=upper; k >= v[j] ; --k){
				S[k] += S[ k - v[j] ];
			 }
		  }
		  for (int i=upper; i >= lower; --i) res += S[i];
		}
		sum += v[i];
		last = v[i];
	 }
	 printf("%d %lld\n",cases,res);
  }
  return 0;
}