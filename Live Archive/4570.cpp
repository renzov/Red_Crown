#include<cstdio>

int p,s,w;
int b[50];
int e[50];
int d[50][50];

inline int min(int x,int y){ return x<=y? x:y; }

int next_jump( int x , int i ){
  while ( x >= b[i] ) i++;
  return i;
}

int jumps( int x, int y ){
  if ( x > y || x == w ) return w;
  int i = next_jump( x , 1 );
  int res = 0;
  int jp,next;
  int nx;
  while ( b[i] < y ){
	 jp = ( b[i] - 1 - x ) / s;
	 res += jp;
	 x += (jp*s);
	 if ( y - x <= s ) break;
	 next = next_jump( x + s - 1 , i );
	 for ( i = next; i > 0 && b[i]-1 == b[i-1]; --i );
	 nx = min( b[i] - 1 , x + s );
	 if ( nx == x ) return w;
	 x = nx;
	 res++;
  }
  return res + ( y + s - 1 - x ) / s;
}

int main(){
  
  while ( scanf("%d",&w) && w ){
	 scanf("%d %d",&s,&p);
	 for ( int i=1; i <= p; ++i)
		scanf("%d %d",b+i,e+i);
	 p++;
	 b[0] = e[0] = 0;
	 b[p] = e[p] = w;
	 
	 for ( int i=0; i <= p; ++i ){
		for ( int j=0; j <= p; ++j ){
		  d[i][j] = min( jumps( e[i] , b[j] ) , jumps( e[i] , e[j] ) );
		}
	 }

	 for ( int k=0; k <= p; ++k )
		for ( int i=0; i <= p; ++i )
		  for ( int j=0; j <= p; ++j )
			 d[i][j] = min( d[i][j] , d[i][k] + d[k][j] );

	 printf("%d\n",d[0][p]);
  }

  return 0;
}