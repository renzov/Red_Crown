#include<cstdio>
#include<algorithm>
using namespace std;
bool IsOnSegment(int xi, int yi, int xj, int yj,
                        int xk, int yk) {
  return (xi <= xk || xj <= xk) && (xk <= xi || xk <= xj) &&
         (yi <= yk || yj <= yk) && (yk <= yi || yk <= yj);
}

char ComputeDirection(int xi, int yi, int xj, int yj,
                             int xk, int yk) {
  int a = (xk - xi) * (yj - yi);
  int b = (xj - xi) * (yk - yi);
  return a < b ? -1 : a > b ? 1 : 0;
}

/** Do line segments (x1, y1)--(x2, y2) and (x3, y3)--(x4, y4) intersect? */
bool DoLineSegmentsIntersect(int x1, int y1, int x2, int y2,
                             int x3, int y3, int x4, int y4) {
  char d1 = ComputeDirection(x3, y3, x4, y4, x1, y1);
  char d2 = ComputeDirection(x3, y3, x4, y4, x2, y2);
  char d3 = ComputeDirection(x1, y1, x2, y2, x3, y3);
  char d4 = ComputeDirection(x1, y1, x2, y2, x4, y4);
  return (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
          ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) ||
         (d1 == 0 && IsOnSegment(x3, y3, x4, y4, x1, y1)) ||
         (d2 == 0 && IsOnSegment(x3, y3, x4, y4, x2, y2)) ||
         (d3 == 0 && IsOnSegment(x1, y1, x2, y2, x3, y3)) ||
         (d4 == 0 && IsOnSegment(x1, y1, x2, y2, x4, y4));
}

bool inside(int x1,int x2,int y1,int y2,int xl,int xr,int yl,int yr){
  return (x1 >= xl && x1 <= xr) && (x2 >= xl && x2 <= xr) && (y1 <= yl && y1 >= yr) && (y2 <= yl && y2 >= yr);
}

int main(){
  
  int runs;
  int x1,x2,y1,y2;
  int xl,xr,yl,yr;

  scanf("%d",&runs);
  while (runs--){
	 scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
	 scanf("%d %d %d %d",&xl,&yl,&xr,&yr);
	 if (xl > xr) swap(xl,xr);
	 if (yl < yr) swap(yl,yr);
	 if (DoLineSegmentsIntersect(x1,y1,x2,y2,xl,yl,xl,yr) ||
        DoLineSegmentsIntersect(x1,y1,x2,y2,xl,yl,xr,yl) ||
        DoLineSegmentsIntersect(x1,y1,x2,y2,xl,yr,xr,yr) ||
		  DoLineSegmentsIntersect(x1,y1,x2,y2,xr,yl,xr,yr) ||
		  inside(x1,x2,y1,y2,xl,xr,yl,yr)
	 )
		puts("T");
	 else
		puts("F");
  }
  return 0;
}