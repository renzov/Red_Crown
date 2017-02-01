#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

int a[105];
bool used[105]={0};
void print(vector<int> &pre,int s){
  int idx = pre[s];
  used[idx] = true;
  if ( s == a[idx] ){
	 return;
  }
  print(pre,s-a[idx]);
}

int main(){
  int sum;
  int n;
  int total = 0;
  scanf("%d",&sum);
  scanf("%d",&n);
  for ( int i=0; i < n; ++i ){
	 scanf("%d",a+i);
	 total += a[i];
  }
  vector<int> dp(sum+2,0);
  vector<int> pre(sum+2,-1);
  dp[0] = 1;
  for ( int i=0; i<n; ++i ){
	 for ( int j=sum; j >= a[i]; --j ){
		if ( dp[ j - a[i] ] ){ 
		  dp[ j ] += dp[ j - a[i] ];  
		  if ( dp[j] > 2 ) dp[j] = 2;
		  if ( pre[j] == -1 ) pre[ j ] = i; 
		}
	 }
  }
  if ( total == sum ) printf("0\n");
  else if ( dp[ sum ] == 0 ) printf("0\n");
  else if ( dp[sum] > 1 ) printf("-1\n");
  else {
	 print(pre,sum);
	 bool first = true;
	 for( int i=0; i < n; ++i ) 
		 if ( !used[i] ){
			if (first) first = false;
			else printf(" ");
			printf("%d",i+1);
		}
	 puts("");
  }

  return 0; 
}