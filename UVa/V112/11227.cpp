#include<cstdio>
#include<cmath>
const double EPS = 1e-8;

#define forab(i,x,y) for(int i=(int)(x); i < (int)(y); ++i)
#define forn(i,n) for(int i=0; i < (int)(n); ++i)

struct point{
  double x,y;
  point(){}
  point(double X,double Y){ x = X; y = Y; }
  bool operator==(const point &that) const {
	 return (fabs( x - that.x ) < EPS) && (fabs( y - that.y ) < EPS);
  }
};

bool colinear( const point &a, const point &b, const point &c ){
  return fabs(a.x*b.y + a.y*c.x + b.x*c.y - b.y*c.x - b.x*a.y - a.x*c.y) < EPS; 
}

int main(){

  point p[ 105 ];
  int n;
  int m;
  bool f;
  int runs;
  int cnt;
  scanf("%d",&runs);
  forab(k,1,runs+1){
	 scanf("%d",&n);
	 m = 0;
	 forn(i,n){
		scanf("%lf %lf",&p[m].x,&p[m].y);
		f = false;
		forn(j,m){
		  if ( p[m] == p[j] ){ f = true; break; }
		}
		if ( !f ) m++;
	 }
	 printf("Data set #%d contains",k);
	 if ( m == 1 ) printf(" a single gnu.\n");
	 else {
		int maxi = 0;
		forn(i,m){
		  forab(j,i+1,m){
			 cnt = 2;
			 forn(t,m){
				if ( t != i && t != j && colinear( p[i] , p[j] , p[t] ) ) cnt++;
			 }
			 if ( maxi < cnt ) maxi = cnt;
		  }
		}
		printf(" %d gnus, out of which a maximum of %d are aligned.\n",m,maxi);
	 }
  }
  return 0;
}