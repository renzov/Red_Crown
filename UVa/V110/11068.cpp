#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

int main(){
  int a,b,c,d,r,s;
  double x,y;
  while ( 1 ){
	 scanf("%d %d %d",&a,&b,&r);
	 scanf("%d %d %d",&c,&d,&s);
	 if ( !a && !b && !c && !d && !r && !s ) break;
	 if ( (a*d - b*c) == 0 ){
		if ( (!a && !b) || (!c && !d) ){
		  if ( r==0 && s==0 ){
			 printf("The fixed point is at 0.00 0.00.\n");
		  }
		  else {
			 puts("No fixed point exists.");
		  }
		}
		else {
		  puts("No fixed point exists.");
		}
	 }
	 else {
		x = ((double)(s*b - d*r)) / (c*b - a*d);
		if ( b ){
		  y = (r - a*x)/b;
		}
		else {
		  y = (s - c*x)/d;
		}
		printf("The fixed point is at %0.2lf %0.2lf.\n",x,y);
	 }
  }
  return 0;
}