#include<string>
#include<sstream>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m;
int M[20][20];
int dp[16][ 1<<15 ];
int p,row;

inline bool get( int i ){ return (p>>i)&1; }

void search( int i , int s , int q ){
  if ( i >= n ){
	 dp[row+1][q] = max( dp[row+1][q] , dp[row][p] + s );
	 return;
  }
  
  if ( get( i ) ){
	 search( i + 1 , s , q );
	 return;
  }
  
  search( i + 1 , s , q );
  
  //Take i
  if ( i > 0 ) q |= ( 1<<(i-1) );
  if ( i+1 < n ) q |= ( 1<<(i+1) );
  q |= ( 1 << i );
  search( i + 2 , s + M[row][i] , q );

}

int find_max(){
  memset( dp , 0 , sizeof(dp) );
  
  for ( row = 0; row < n; ++row )
	 for ( p=0; p < (1<<n); ++p){
		search(0,0,0);
	 }

  int best = 0;
  for ( p = 0; p < (1<<n); ++p )
	 if ( dp[n][p] > best) best = dp[n][p];
 
  return best;
}

int main(){
  string line;
  while ( getline( cin , line ) ){
	 n = 0;
	 do {
		stringstream in( line );
		m = 0;
		while ( in >> M[n][m] ){
		  m++;
		}
		n++;
		getline( cin, line );
	 }
	 while ( line.size() );
	 
	 cout << find_max() << endl;
  }

  return 0;
}