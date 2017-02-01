#include<cstdio>
#include<cmath>
const long double INF = 10e20;
struct line{
  long double b,m;
  int x1,x2,y1,y2;
};

void find_data(line &l){
  if (l.x1 == l.x2){
		l.m = INF;
		l.b = l.x1;
  }
  else if (l.y1 == l.y2){
		l.b = l.y1;
		l.m = 0.0;
  }
  else {
		l.m = (long double)(l.y1 - l.y2)/(l.x1-l.x2);
		l.b = l.y1 - l.m * l.x1;
  }
}

int main(){


  line l1,l2;
  int runs;
  long double x,y;

  scanf("%d",&runs);
  puts("INTERSECTING LINES OUTPUT");
  while (runs--){
	 scanf("%d %d %d %d",&l1.x1,&l1.y1,&l1.x2,&l1.y2);
	 scanf("%d %d %d %d",&l2.x1,&l2.y1,&l2.x2,&l2.y2);
	 find_data(l1);
	 find_data(l2);
	 if (fabs(l1.m - l2.m) < 0.00001){	/* Paralelo o igual */
		  if (fabs(l1.b - l2.b) < 0.00001) puts("LINE");
		  else puts("NONE");
	 }
	 else {
		  if (fabs(l1.m - INF) < 0.0001){
				x = l1.b;
				if (fabs(l2.m) < 0.0001 ){ y = l2.b; }
				else y = l2.m * x + l2.b;
		  }
		  else if (fabs(l2.m - INF) < 0.0001){
				x = l2.b;
				if (fabs(l1.m) < 0.0001 ){ y = l1.b; }
				else y = l1.m * x + l1.b;
		  }
		  else if ( fabs(l1.m) < 0.0001 ){
				y = l1.b;
				if (fabs(l2.m - INF) < 0.0001){ x = l2.b; }
				else x = (y - l2.b) / l2.m;
		  }
		  else if (fabs(l2.m) < 0.0001){
				y = l2.b;
				if (fabs(l1.m - INF) < 0.0001){ x = l1.b; }
				else x = (y - l1.b) / l1.m;
		  }
		  else {
				x = (l2.b - l1.b) / (l1.m - l2.m);
				y = l1.m * x + l1.b;
		  }
		  printf("POINT %0.2Lf %0.2Lf\n",x,y);
	 }
  }
  puts("END OF OUTPUT");
  return 0;
}