#include<cstdio>
#include<cmath>

int dist( int x,int y , int cx, int cy ){
  return (x-cx)*(x-cx) + (y-cy)*(y-cy);
}

int main(){
  int n;
  int in,out,cut;
  int cx,cy;
  int D;
  int runs = 0;
  int d1,d2,d3,d4;
  while ( scanf("%d",&n) != EOF ){
	 runs++;
	 cx = n; cy = n;
	 D = 2*n - 1;
	 D *= D;
	 in = out = 0;
	 for ( int i=0; i < 2*n; ++i ){
		for ( int j=0; j < 2*n; ++j ){
		  d1 = 4*dist( j , i , cx , cy );
		  d2 = 4*dist( j + 1 , i , cx , cy  );
		  d3 = 4*dist( j , i + 1, cx , cy );
		  d4 = 4*dist( j + 1, i + 1 , cx , cy );
		  if ( d1 <= D && d2 <= D && d3 <= D && d4 <= D ){
			 in++;
		  }
		  else if ( d1 >= D && d2 >= D && d3 >= D && d4 >= D ){
			 out++;
		  }
		}
	 }
	 cut = 4*n*n - in - out;
	 if ( runs > 1 ) puts("");
	 printf("In the case n = %d, %d cells contain segments of the circle.\n",n,cut);
	 printf("There are %d cells completely contained in the circle.\n",in);
  }
  return 0;
}