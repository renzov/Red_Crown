#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXP = 305;
int n;
struct ipoint{
  int x,y;
  ipoint(){}
  ipoint(int X,int Y){ x = X; y = Y; }
  bool operator<(const ipoint &that) const {
	 return ( x != that.x )? (x<that.x):(y<that.y);
  }
};

bool colinear( const ipoint &a, const ipoint &b, const ipoint &c ){
  return (a.x*b.y + a.y*c.x + b.x*c.y - b.y*c.x - b.x*a.y - a.x*c.y) == 0; 
}

ipoint p[ MAXP ];
bool test[MAXP][MAXP];
int used[ MAXP ];

int main(){
  int cnt;
  int lines;
  while ( scanf("%d %d",&p[0].x,&p[0].y) && ( p[0].x || p[0].y ) ){
	 n = 1;
	 while ( scanf("%d %d",&p[n].x,&p[n].y) && ( p[n].x || p[n].y ) ) n++;
	 sort(p,p+n);
	 //Init test matrix
	 for (int i=0; i < n; ++i)
		for ( int j=0; j < n; ++j )
		  test[i][j] = false;
	 lines = 0;
	 //Begin of search
	 for( int i=0; i < n-2; ++i ){
		for ( int j=i+1; j < n-1; ++j ){
		  if ( !test[i][j] ){
			 //Testing line (i,j)
			 cnt = 2;
			 used[0] = i; used[1] = j; 
			 for ( int k=j+1; k < n; ++k ){
				if ( colinear( p[i] , p[j] , p[k] ) ){ 
				  used[cnt] = k; cnt++; 
				}
			 }
			 if ( cnt > 2 ){
				for ( int k = 0; k < cnt; ++k ){
				  for ( int t = 0; t < cnt; ++t  )
					 test[ used[k] ][ used[t] ] = true;
				}
				if ( !lines ){ puts("The following lines were found:");  }
				for ( int k=0; k < cnt; ++k ){
				  printf("(%4d,%4d)",p[ used[k] ].x,p[ used[k] ].y);
				}
				putchar('\n');
				lines++;
			 }
		  }
		}
	 }
	 if ( !lines ) puts("No lines were found");
  }
  return 0;
}