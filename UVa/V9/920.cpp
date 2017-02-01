#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define forn(i,n) for(int i=0; i < (int)(n); ++i)
const double EPS = 1e-8;
const double PI = 2*acos(0);
struct ipoint{
  int x,y;
  ipoint(){}
  ipoint(int X,int Y){ x = X; y = Y; }
  bool operator==(const ipoint &that) const {
	 return x == that.x && y == that.y;
  }
  bool operator<(const ipoint &that) const {
	 return (x != that.x)? (x > that.x):(y < that.y);
  }
};

//*** Rectas

struct line{
  double a,b,c;
  line(){};
  line( const ipoint &p1 , const ipoint &p2 ){
	 if ( p1.x == p2.x  ){ //Vertical line
		b = 0; a = 1; c = -p1.x;
	 }
	 else {
		b = 1; a = -((double)( p1.y - p2.y ))/( p1.x - p2.x );
		c = -a*p1.x - b*p1.y;
	 }
  }
  double get_X( int Y ){
	 return -((double)(b*Y + c))/a;
  }
};

ipoint P[105];
line L[105];

int main(){
  int n;
  double x,y;
  int runs;
  scanf("%d",&runs);
  while ( runs-- ){
	 scanf("%d",&n);
	 forn(i,n){
		scanf("%d %d",&P[i].x,&P[i].y);
	 }
	 sort(P,P+n);
	 forn(i,n-1){
		L[i] = line( P[i] , P[i+1] );
	 }
	 double res = hypot( (double)(P[0].x - P[1].x) , (double)(P[0].y - P[1].y) );
	 int act = 0;
	 int maxY;
	 int actMaxY = max( P[0].y , P[1].y );
	 for ( int i=1; i < (n-1); ++i ){
		maxY = max( P[i].y , P[i+1].y );
		if ( maxY > actMaxY ){
		  y = actMaxY; x = L[i].get_X( actMaxY );
		  res += hypot( P[i+1].x - x ,  P[i+1].y - y );
		  actMaxY = maxY; act = i;
		}
	 }
	 printf("%0.2lf\n",res);
  }
  return 0;
}