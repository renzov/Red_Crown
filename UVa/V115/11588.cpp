#include<cstdio>
#include<algorithm>
using namespace std;

int main(){
  int runs;
  int R,C,N,M;
  char s[30];

  scanf("%d",&runs);
  for (int k=1; k <= runs; ++k){
		scanf("%d %d %d %d",&R,&C,&M,&N);
		int frec[27] = {0};
		for (int i=0; i < R; ++i){
			scanf("%s",s);
			for (int j=0; s[j]; ++j) frec[ s[j] - 'A']++;
		}
		int m = *max_element(frec,frec + 26);
		int res = 0;
		for (int i=0; i < 26; ++i){
			 if (frec[i]){
				  res += frec[i] * ( frec[i] != m ? N:M);
			 }
		}
		printf("Case %d: %d\n",k,res);
  }
  return 0;
}