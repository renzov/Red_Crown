#include<iostream>

using namespace std;

int main(){
  bool found = false;
  int r1,r2,c1,c2,d1,d2;
  cin >> r1 >> r2 >> c1 >> c2 >> d1 >> d2;
  for ( int i=1; i <= 9; ++i )
	 for ( int j=1; j <= 9; ++j )
		  for ( int k=1; k<=9; ++k )
				for ( int t=1; t <= 9; ++t ){
				  if ( (i+j) == r1 && (k+t)==r2
					 && (i+k) == c1 && (j+t)==c2
					 && (i+t) == d1 && (j+k)==d2
					 && ( i != j && i != k && i != t && j != k 
						 && j != t && k != t
					 )
				  ){
					 cout << i << " " << j << endl;
					 cout << k << " " << t << endl;
					 return 0;
 				  }
				}
  cout << -1 << endl;
  return 0;
}