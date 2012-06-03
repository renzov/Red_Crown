#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const long long LIMIT = 1000000000000000000LL;
long long A[100];
long long B[100];
long long C[100];
int size[3];

bool no_over( long long prod, long long fact ){
  //prod * fact < LIMIT
  if ( LIMIT % fact ){
	 return prod < (LIMIT / fact);
  }
  else {
	 return prod < ( LIMIT/fact + 1 );
  }
}

bool no_over2( long long a, long long b , long long c ){
  long long l;
  if ( LIMIT % c ){
	 l = (LIMIT / c);
  }
  else {
	 l = (LIMIT / c) + 1;
  }
  // a * b < l
  if ( l % b ){
	 l = l / b;
  }
  else {
	 l = l/b + 1;
  }
  return a < l;
}

int main(){
  long long p1,p2,p3;
  long long n;
  cin >> p1 >> p2 >> p3 >> n;
  //Generate powers
  A[0] = B[0] = C[0] = 1;
  size[0] = size[1] = size[2] = 1;
  long long pot = 1;
  while ( no_over(pot,p1) ){
	 pot *= p1;
	 A[ size[0]++ ] = pot;
  }
  pot = 1;
  while ( no_over(pot,p2) ){
	 pot *= p2;
	 B[ size[1]++ ] = pot;
  }
  pot = 1;
  while ( no_over(pot,p3) ){
	 pot *= p3;
	 C[ size[2]++ ] = pot;
  }
  vector<long long> a;
  for ( int i=0; i < size[0]; ++i )
	 for ( int j=0; j < size[1]; ++j )
		for ( int k=0; k < size[2]; ++k ){
		  if ( no_over2(A[i],B[j],C[k]) )
			 a.push_back( A[i]*B[j]*C[k] );
		}
  sort( a.begin() , a.end() );
  cout << a[n] << endl;
  return 0;
}