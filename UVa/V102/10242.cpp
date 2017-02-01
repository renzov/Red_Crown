#include<cstdio>
#include<cmath>
const double EPS = 0.0001;
struct point{
  double x,y;
  point(){}
  point(double X,double Y){ x = X; y = Y; }
  bool operator==(const point &that) const {
	 return (fabs( x - that.x ) < EPS) && (fabs( y - that.y ) < EPS);
  }
};

struct vect{
  double a,b;
  vect(){};
  vect( double A , double B ){ a = A; b = B; }
  point translate( const point &p ){
	 return point( p.x + a , p.y + b );
  }
};

int main(){
  point p[4];
  point res;
  int n;
  int rep,next,prev;
  bool f;
  while ( scanf("%lf %lf",&p[0].x,&p[0].y) == 2 ){
	 n = 1; rep = -1;
	 for(int j=0; j < 3; ++j){
		scanf("%lf %lf",&p[n].x,&p[n].y);
		f = false;
		for ( int i=0; i < n; ++i ){
		  if ( p[n] == p[i] ){ rep = i; f = true; break; }
		}
		if ( !f ) n++;
	 }
	 next = ( rep + 1 )%3;
	 prev = ( rep + 2 )%3;
	 vect a( p[prev].x - p[rep].x , p[prev].y - p[rep].y );
	 res = a.translate( p[next] );
	 printf("%0.3lf %0.3lf\n",res.x,res.y);
  }
  return 0;
}

