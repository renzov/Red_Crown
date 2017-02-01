#include<cstdio>
#include<cmath>
const double EPS = 1e-8;
int main(){
  int n;
  double d1,d2;
  double xg,yg;
  double xd,yd;
  double x,y;
  double xf,yf;
  bool found;
  while ( scanf("%d",&n) != EOF ){
	 scanf("%lf %lf %lf %lf",&xg,&yg,&xd,&yd);
	 found = false;
	 for ( int i=0; i < n; ++i ){
		scanf("%lf %lf",&x,&y);
		if ( !found ){
		  d1 = hypot( x - xg , y - yg );
		  d2 = hypot( x - xd , y - yd );
		  d1 *= 2;
		  if ( fabs( d1 - d2 ) < EPS || (d1 < d2) ){
			 found = true; xf = x; yf = y;
		  }
		}
	 }
	 if ( !found ) puts("The gopher cannot escape.");
	 else printf("The gopher can escape through the hole at (%0.3lf,%0.3lf).\n",xf,yf);
  }

  return 0;
}