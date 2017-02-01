#include<cstdio>
#include<cmath>
#define forn(i,n) for( int i=0; i < (int)(n); ++i )
const double EPS = 1e-8;
inline double min(double x,double y){ return x<=y? x:y; }
inline double max(double x,double y){ return x>=y? x:y; }
struct point{
  double x,y;
  point(){}
  point(double X,double Y){ x = X; y = Y; }
  bool operator==(const point &that) const {
	 return fabs( x - that.x ) < EPS && fabs( y - that.y ) < EPS;
  }
};

bool inside_circle( point center, double r, point t ){
  double d = hypot( center.x - t.x , center.y - t.y );
  if ( fabs( d - r ) < EPS ) return false;
  return d < r;
}

bool inside_rect( point *P , point test ){
  double xmin = min( P[0].x , P[1].x );
  double xmax = max( P[0].x , P[1].x );
  double ymin = min( P[0].y , P[1].y );
  double ymax = max( P[0].y , P[1].y );
  if ( fabs(test.x-xmin) < EPS ) return false;
  if ( fabs(test.x-xmax) < EPS ) return false;
  if ( fabs(test.y-ymin) < EPS ) return false;
  if ( fabs(test.y-ymax) < EPS ) return false;
  return (test.x >= xmin) && (test.x <= xmax) && (test.y >= ymin) && (test.y <= ymax);
}

double Area2( point &a, point &b, point &c ){
  return fabs( (b.x - a.x)*(c.y - a.y) - (c.x - a.x)*(b.y - a.y) );
}

bool inside_tri( point *P , point test ){
  //(b0 - a0)*(c1-a1) - (c0-a0)*(b1-a1)
  double darea = Area2(P[0],P[1],P[2]);
  double a1 = Area2(test,P[0],P[1]); 
  double a2 = Area2(test,P[1],P[2]);
  double a3 = Area2(test,P[0],P[2]);
  if ( fabs( darea - a1 - a2 - a3 ) < EPS ){
	 return fabs(a1)>EPS && fabs(a2)>EPS && fabs(a3)>EPS;
  }
  return false;
}

struct figure {
  char type;
  point P[3];
  double r;
  bool inside( const point test ){
	 if ( type == 'r' ) return inside_rect( P , test );
	 else if ( type == 'c' ) return inside_circle( P[0] , r , test );
	 else return inside_tri( P , test );
  }
};


int main(){
  int n = 0;
  point final(9999.9,9999.9);
  char type;
  figure F[ 100 ];
  bool found;
  point test;
  while ( scanf(" %c",&type) && type != '*' ){
	 F[n].type = type;
	 if ( type == 'r' ){
		forn(i,2) scanf("%lf %lf",&F[n].P[i].x,&F[n].P[i].y);
	 }
	 else if ( type=='t' ){
		forn(i,3) scanf("%lf %lf",&F[n].P[i].x,&F[n].P[i].y);
	 }
	 else {
		 scanf("%lf %lf %lf",&F[n].P[0].x,&F[n].P[0].y,&F[n].r);
	 }
	 n++;
  }
  int m = 0;
  while ( scanf("%lf %lf",&test.x,&test.y) && !(test == final) ){
	 m++;
	 found = false;
	 forn(i,n){
		if ( F[i].inside(test) ){ found = true; printf("Point %d is contained in figure %d\n",m,i+1); }
	 }
	 if ( !found ) printf("Point %d is not contained in any figure\n",m);
  }
  return 0;
}