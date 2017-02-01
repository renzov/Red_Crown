#include<cstdio>
#include<cstring>
long long memo[3][3][46];
int n;

int solve( int ant, int prev, int pos ){
  if ( pos == n ) return ( prev != 1 );
  if ( memo[ant][prev][pos] != -1 ) return memo[ant][prev][pos];
  memo[ant][prev][pos] = 0;
  if ( prev == 1 ){
	 if ( ant == 0 ) memo[ant][prev][pos] += solve( prev , 2 , pos + 1 );
	 else memo[ant][prev][pos] += solve( prev , 0 , pos + 1 );
  }
  else {
	 for ( int i=0;i < 3; ++i )
		 if ( i != prev )
			memo[ant][prev][pos] += solve( prev , i , pos + 1 );
  }
  return memo[ant][prev][pos];
}

int main(){
  scanf("%d",&n);
  if ( n == 1 ) printf("2\n");
  else if ( n == 2 ) printf("2\n");
  else {
	 long long res = 0;
	 memset( memo , -1 , sizeof(memo) );
	 for ( int i=0; i < 3; ++i ){
		if ( i != 1 ){
		  for ( int j=0; j < 3; ++j ){
			 if ( j != i )
				  res += solve( i , j , 2 );
		  }
		}
	 }
	 printf("%lld\n",res);
  }
  return 0;
}
