#include<cstdio>
#include<cmath>
int main(){
  int runs;
  double x;
  char s[5];
  scanf("%d",&runs);
  for (int k=1; k <= runs; ++k){
	 scanf("%lf %s",&x,s);
	 if (s[0] == 'k'){
		x *= 2.2046;
		x = floor(x*10000 + 0.5)/10000;
		printf("%d %.4lf lb\n",k,x);
	 }
	 else if (s[0] == 'g'){
		x *= 3.7854;
		x = floor(x*10000 + 0.5)/10000;
		printf("%d %.4lf l\n",k,x);
	 }
	 else if (s[1] == 'b'){
		x *= 0.4536;
		x = floor(x*10000 + 0.5)/10000;
		printf("%d %.4lf kg\n",k,x);
	 }
	 else {
		x *= 0.2642;
		x = floor(x*10000 + 0.5)/10000;
		printf("%d %.4lf g\n",k,x);
	 }
  }
  return 0;
}