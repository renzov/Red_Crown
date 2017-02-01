#include<iostream>
using namespace std;

int turn(int a,int b,bool d){
  if ( d ){
	 return b > a? (b-a):(40-a+b);
  }
  return a > b? ( a-b ):( 40 - b + a );
}

int main(){
  int a,b,c,d;
  int res;
  while (cin >> a >> b >> c >> d){
	 if (!a && !b && !c && !d) return 0;
	 res = 120;
	 res += turn( a , b , false );
	 res += turn( b , c, true );
	 res += turn( c , d , false );
	 cout << res*9 << endl;
  }
  return 0;
}