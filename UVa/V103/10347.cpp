#include<cstdio>
#include<cmath>
const double EPS = 1e-8;

bool valid( double a, double b, double c ){
  double d1 = a - b - c;
  double d2 = b - a - c;
  double d3 = c - a - b;
  if ( fabs(d1) < EPS || fabs(d2) < EPS || fabs(d3) < EPS )
	 return false;
  return ((a+b)>c) && ((a+c)>b) && ((b+c)>a);
}

int main(){
  
  double ma,mb,mc;
  double sa,sb,sc;
  double a,b,c,s,A;

  while ( scanf("%lf %lf %lf",&ma,&mb,&mc) != EOF ){
	 if ( fabs(ma) < EPS || fabs(mb) < EPS || fabs(mc) < EPS ){
		printf("-1.000\n"); continue;
	 }
	 if ( ma < 0 || mb < 0 || mc < 0 ){
		printf("-1.000\n"); continue;
	 }
	 sa = -ma*ma + 2*mb*mb + 2*mc*mc;
	 sb = -mb*mb + 2*ma*ma + 2*mc*mc;
	 sc = -mc*mc + 2*ma*ma + 2*mb*mb;
	 if ( fabs(sa) < EPS || fabs(sb) < EPS || fabs(sc) < EPS ){
		printf("-1.000\n"); continue;
	 }
	 if ( sa < 0 || sb < 0 || sc < 0 ){
		printf("-1.000\n"); continue;
	 }
	 a = (2.0/3.0)*sqrt(sa); b = (2.0/3.0)*sqrt(sb); c = (2.0/3.0)*sqrt(sc);
	 if ( !valid(a,b,c) ){
		printf("-1.000\n"); continue;
	 }
	 s = (a+b+c)*0.5;
	 A = sqrt( s*(s-a)*(s-b)*(s-c) );
	 A = floor( A*1000 + .5 )/1000;
	 printf("%0.3lf\n",A);
  }
  return 0;
}