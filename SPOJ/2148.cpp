#include<cstdio>
int main(){
  long long a;
  long long n;
  long long s;
  int runs;
  scanf("%d",&runs);
  while (runs--){
	 scanf("%lld",&n);
	 s = 0;
	 for (long long i=0; i < n; ++i){ 
		scanf("%lld",&a); 
		s = ((s%n) + (a%n))%n;
	 }
	 if (s) puts("NO");
	 else puts("YES");
  }
  return 0;
}