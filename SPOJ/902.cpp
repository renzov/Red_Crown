#include<cstdio>
int main(){
  double v;
  double s;
  int r;
  while (scanf("%lf",&v) && v > 0.00){
		 s = 0.5;
		 r = 1;
		 while (s < v){
			 r++;
			 s += 1.0/(r+1);
		 }
		 printf("%d card(s)\n",r);
  }
  return 0;
}