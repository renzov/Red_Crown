#include<cstdio>
#include<algorithm>
using namespace std;
long long a[500];
int n;

int main(){
  int C,R;
  int runs;
  scanf("%d",&runs);
  for (int k=1; k <= runs; ++k){
	 scanf("%d %d",&C,&R);
	 printf("Case #%d:",k);
	 if (C==R) printf(" 0\n");
	 else if (C < R) putchar('\n');
	 else {
		  n = 0;
		  long long r = C - R;
		  for (long long i=1; i*i <= r; ++i){
				if (r%i == 0){
					if ( R < i ){
						a[n++] = i;
					}
				   if (r/i != i && R < r/i){
						a[n++] = r/i;
				   }
				}
		  }
		  sort(a,a+n);
		  for (int i=0; i < n; ++i) printf(" %lld",a[i]);
		  putchar('\n');
	 }
  }
  return 0;
}