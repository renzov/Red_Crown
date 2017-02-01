#include<cstdio>
#include<cmath>
const double Pi = 3.1415927;
int main(){
  int r;
  int cases = 0;
  double e,v,d,t;
  while (scanf("%lf %d %lf",&d,&r,&t) && r){
	 cases++;
	 e = ( Pi * d * r )/63360;
	 t = (t)/3600;
	 v = e / t;
	 e = floor(e*100 + .5)/100;
	 v = floor(v*100 + .5)/100;
	 printf("Trip #%d: %0.2lf %0.2lf\n",cases,e,v);
  }
  return 0;
}