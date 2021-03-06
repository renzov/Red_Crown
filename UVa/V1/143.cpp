#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
struct point {
  int x,y;
  point(){}
  point( int X , int Y ){ x=X; y=Y; }
  bool operator==(const point &that) const{
	 return x == that.x && y == that.y; 
  }
};

struct vect{
  int a,b;
  vect(){}
  vect( point p1 , point p2 ){ 
	 a = p2.x - p1.x; 
	 b = p2.y - p1.y;  
  }
  int cross( const vect &v2 ) const{
	 return a*v2.b - b*v2.a;
  }
};

bool angcmp(const point &a,const point &b){
  int det = a.x*b.y - a.y*b.x;
  if ( det != 0 ) return det > 0;
  return (a.x*a.x + a.y*a.y) < (b.x*b.x + b.y*b.y); 
}

int round_down( int x ){
  if ( x % 100 ) x -= (x%100);
  return min(x,9900);
}

int round_up(int x){
  if ( x % 100 ) x += (100 - (x%100));
  return max(100,x);
}

int main(){
  point zero(0,0);
  point p[3];
  double x,y;
  int res;
  int darea,tarea;
  int xmin,ymin,xmax,ymax;
  while ( 1 ){
	 for (int i=0; i < 3; ++i){
		scanf("%lf %lf",&x,&y); p[i].x = (int)floor(x*100 + .5); p[i].y = (int)floor(y*100 + .5);
	 }
	 if ( p[0]==zero && p[1]==zero && p[2]==zero ) break;
	 //sort(p,p+3,angcmp);
	 xmin = min( p[0].x , min(p[1].x,p[2].x) );
	 ymin = min( p[0].y , min(p[1].y,p[2].y) );
	 xmax = max( p[0].x , max(p[1].x,p[2].x) );
	 ymax = max( p[0].y , max(p[1].y,p[2].y) );
	 xmin = round_up(xmin);
	 ymin = round_up(ymin);
	 xmax = round_down(xmax);
	 ymax = round_down(ymax);
	 vect AB(p[0],p[1]); 
	 vect BC(p[1],p[2]);
	 vect CA(p[2],p[0]);
	 darea = abs( AB.cross(BC) );
	 res = 0;
	 point test;
	 for ( int i=ymin; i <= ymax; i+=100 ){
		for ( int j=xmin; j <= xmax; j+=100 ){
		  test.x = j; test.y = i;
		  vect PA(test,p[0]);
		  vect PB(test,p[1]);
		  vect PC(test,p[2]);
		  tarea = abs( PA.cross(AB) );
		  tarea += abs( PB.cross(BC) );
		  tarea += abs( PC.cross(CA) );
		  if ( darea == tarea ) res++;
		}
	 }
	 printf("%4d\n",res);
  }
  return 0;
}