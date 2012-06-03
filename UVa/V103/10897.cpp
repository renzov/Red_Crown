#include<cstdio>
#include<cmath>
const double EPS = 1e-8;
const double PI = 2*acos(0);
const double R = 6371.01;

double GCDist(double pLat ,double pLon,double qLat ,double qLon){
  pLon *= PI/180; pLat *= PI/180;
  qLon *= PI/180; qLat *= PI/180;
  return  R * acos( cos(pLat)*cos(pLon)*cos(qLat)*cos(qLon) + 
						 cos(pLat)*sin(pLon)*cos(qLat)*sin(qLon) +
						 sin(pLat)*sin(qLat) ) ;
}

int main(){

  int runs;
  scanf("%d",&runs);
  double pLat,pLon,qLat,qLon;
  double a,b,c;
  char s;
  while ( runs-- ){
	 scanf("%lf %lf %lf %c",&a,&b,&c,&s); b /= 60.0; c /= 3600.0; a += b; a += c;
	 if ( s == 'S' ) a*= -1;
	 pLat = a;
	 scanf("%lf %lf %lf %c",&a,&b,&c,&s); b /= 60.0; c /= 3600.0; a += b; a += c;
	 if ( s == 'W' ) a*=-1;
	 pLon = a;
	 scanf("%lf %lf %lf %c",&a,&b,&c,&s); b /= 60.0; c /= 3600.0; a += b; a += c;
	 if ( s == 'S' ) a*= -1;
	 qLat = a;
	 scanf("%lf %lf %lf %c",&a,&b,&c,&s); b /= 60.0; c /= 3600.0; a += b; a += c;
	 if ( s == 'W' ) a*=-1;
	 qLon = a;
	 printf("%0.2lf\n",GCDist( pLat , pLon, qLat , qLon ));
  }
  return 0;
}