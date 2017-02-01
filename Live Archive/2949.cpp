#include<cstdio>
#include<algorithm>
#include<climits>
using namespace std;

bool f[35];
int dp[35][35];
int pre[35][35];
int A[35][35];
int B[35][35];
int L[35];
int U[35];
/*
void precalc(){
  for ( int i=2; i < 31 ; ++i ){
		for ( int j=i+1; j <= 31; ++j ){
		  //Calcular A[i][j]
		  B[i][j] = A[i][j] = 0;
		  for ( int k=i; k <= j; ++k  ){
			 if ( f[k] ){
				if ( (k - i) <= ( j - k ) )
				  A[i][j] = max( A[i][j] , k - i );
				else
				  B[i][j] = max( B[i][j] , j - k );
			 }
		  }
		  A[i][j] *= 20; B[i][j] *= 20;
		}
  }
  for ( int i=2; i < 32; ++i ){
	 U[i] = L[i] = 0;
	 for (int j=2; j < i ; ++j){
		if ( f[j] ){
		  L[i] = ( i - j )*20;
		  break;
		}
	 }
	 for ( int j=31; j > i ;j--){
		  if ( f[j] ){
			 U[i] = ( j - i ) * 20;
			 break;
		  }
	 }
  }
}
*/
void print_path( int i ,int j ){
  if ( j == 1 ){
	 printf(" %d",i);
	 return;
  }
  print_path( pre[i][j] , j - 1 );
  printf(" %d",i);
}

int time( int floor , int stops ){
  return (floor - 1)*4 + 10*( stops - 1 );
}

int main(){
  int n;
  int x;
  int T;
  int ti,tk,tt;
  while ( scanf("%d",&n) && n ){
	 for ( int i=0; i < 32; ++i ) f[i] = false;
	 for ( int i=0; i < n; ++i ){
		scanf("%d",&x);
		f[x] = true;
	 }

	 
	 
	 for ( int i=2; i <= 31; ++i )
		for ( int j=1; j <= 31; ++j )
			dp[i][j] = INT_MAX;
	 
	 for ( int i=2; i <= 31; ++i ){
		 tt = 0;
		 for ( int j=2; j <= i; ++j ){
			if ( f[j] ){
			 ti = (j-1) * 20;
			 tk = time( i , 1 ) + ( i - j ) * 20;
			 if ( tk <= ti ) tt = max( tt , tk );
			 else tt = max( tt , ti );
		   }
		}
		dp[i][1] = tt;
	 }
    
	 for ( int i=3; i <= 31 ; ++i ){
		for ( int j=2; j < i; ++j  ){
		  for ( int k=2; k < i; ++k ){
			 if ( dp[k][j-1] >= INT_MAX ) continue;
			 tt = 0;
			 for ( int l=k+1; l <= i; ++l ){
				if ( f[l] ){
				  tk = time(k,j-1) + (l-k)*20;
				  ti = time(i,j) + (i-l)*20;
				  if ( tk <= ti ) tt = max( tt , tk );
				  else tt = max( tt , ti );
				}
			 }
			 T = max( tt , dp[k][j-1] );
			 if ( dp[i][j] > T ){
				pre[i][j] = k;
				dp[i][j] = T;
			 }
		  }
		}
	 }
	 int res = INT_MAX;
	 int bi,bj;
	 for ( int i=2; i <= 31 ; ++i ){
		for ( int j=1; j < i; ++j ){
		  if ( dp[i][j] != INT_MAX ){
			 /* Calculando U[i]*/
			 tt = 0;
			 for ( int k=i+1; k <= 31; ++k ){
				if ( f[k] ){
				  ti = time(i,j) + (k-i)*20;
				  tt = max(tt,ti);
				}
			 }
			 T = max( dp[i][j] , tt );
			 if ( T < res ){
				res = T;
				bi = i;
				bj = j;
			 }
		  }
		}
	 }
	 printf("%d\n",res);
	 printf("%d",bj);
	 print_path( bi , bj );
	 putchar('\n');
  }  
  return 0;
}