#include<cstdio>
#include<cmath>
const double PI = 2*acos(0);
const double EPS = 1e-8;
int main(){
  char w[10];
  double R,theta;
  double d,s;
  double cord,arc;
  while ( scanf("%lf %lf %s",&s,&d,w) != EOF ){
	 R = 6440 + s;
	 if ( w[0] == 'm' ){
		d /= 60.0;
	 }
	 if ( fabs( d - 180.0 ) > EPS && d > 180.0 ) d = 360 - d;
	 theta = (PI/180)*d;
	 cord = sqrt( 2*R*R*( 1 - cos( theta ) ) );
	 arc = theta * R;
	 printf("%0.6lf %0.6lf\n",arc,cord);
  }
  return 0;
}