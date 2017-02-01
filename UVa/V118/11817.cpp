#include<cstdio>
#include<cmath>
const double EPS = 1e-8;
const double PI = M_PI;
const double R = 6371009;

double GCDist(double pLat ,double pLon,double qLat ,double qLon){
  return  R * acos( cos(pLat)*cos(pLon)*cos(qLat)*cos(qLon) + 
						 cos(pLat)*sin(pLon)*cos(qLat)*sin(qLon) +
						 sin(pLat)*sin(qLat) ) ;
}

void toPoint( double Lat, double Lon, double &x, double &y , double &z ){
  x = cos(Lon) * cos(Lat);
  y = cos(Lat) * sin(Lon);
  z = sin(Lat);
}

int main(){
  double pLat,pLon,qLat,qLon;
  int runs;
  double d1,d2;
  double x1,x2,y1,y2,z1,z2;
  scanf("%d",&runs);
  while ( runs-- ){
	 scanf("%lf %lf %lf %lf",&pLat,&pLon,&qLat,&qLon);
	 pLon *= PI/180; pLat *= PI/180;
	 qLon *= PI/180; qLat *= PI/180;
	 d1 = GCDist( pLat , pLon , qLat , qLon );
	 toPoint( pLat, pLon , x1, y1 , z1 );
	 toPoint( qLat, qLon , x2, y2 , z2 );
	 d2 = R * sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2) );
	 printf("%0.0lf\n",d1-d2);
  }
  return 0;
}