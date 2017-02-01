#include<cstdio>
int G[50][50];
int n;
struct point{
  int x,y;
};

struct seg{
  point A;
  point B;
};

seg S[50];

void floyd(){
	 for (int k=0; k < n; ++k)
		  for (int i=0; i < n; ++i)
				for (int j=0; j < n; ++j)
					 G[i][j] |= (G[i][k] & G[k][j]);
  
}


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

int main(){
  int a,b;
  int runs;
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d",&n);
	 for (int i=0; i < n; ++i){
		G[i][i] = 1;
		for (int j=i+1; j < n; ++j)
		  G[i][j] = G[j][i] = 0;
	 }
	 
	 for (int i=0; i < n; ++i){
		  scanf("%d %d %d %d",&S[i].A.x,&S[i].A.y,&S[i].B.x,&S[i].B.y);
	 }
	 for (int i=0; i < n; ++i){
		  for (int j=i+1; j < n; ++j){
				if (DoLineSegmentsIntersect(S[i].A.x,S[i].A.y,S[i].B.x,S[i].B.y, S[j].A.x,S[j].A.y,S[j].B.x,S[j].B.y ))
				  G[i][j] = G[j][i] = 1;
		  }
	 }
	 floyd();
	 while (scanf("%d %d",&a,&b) && (a && b)){
		  if (G[a-1][b-1]) puts("CONNECTED");
		  else puts("NOT CONNECTED");
	 }
	 if (runs) putchar('\n');
  }

  return 0;
}