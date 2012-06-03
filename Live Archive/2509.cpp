#include<cstdio>
#include<cstring>
#include<climits>

int D[15];
int C[15];
bool F[100002];

int main(){
  int n;
  int m;
  int x;
  bool found;

  while (scanf("%d",&m) == 1){
	 scanf("%d",&n);
	 for (int i=0; i < n; ++i){
		scanf("%d %d",C+i,D+i);
	 }
	 int maxi = 0;
	 memset(F,false,sizeof(bool)*(m+1));
	 F[0] = true;
	 if (m == 0) found = true;
	 else found = false;
	 for (int i=0; i < n && !found; ++i){
		  for (int j=m-1; j >= 0 && !found; --j){
			 if ( F[j] ){
				  x = j;
				  for (int k=1; k <= C[i] && !found; ++k){
					 x += D[i];
					 if ( x > m ) break;
					 F[x] = true;
					 if (x > maxi) maxi = x;
					 if (x==m) found = true;
				  }
			 }
		  }
	 }
	 printf("%d\n",maxi);
  }
  return 0;
}