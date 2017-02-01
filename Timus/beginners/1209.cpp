#include<cstdio>
#include<cmath>

int main(){
  long long x;
  int n;
  int f;
  double m;
  
  scanf("%d",&n);

  while (n--){
	 scanf("%lld",&x);
	 m = sqrt((double)8*x - 7);
	 f = (int)ceil(m);
	 if (m==f) putchar('1');
	 else putchar('0');
	 if (n) putchar(' ');
  }
  
  return 0;
}