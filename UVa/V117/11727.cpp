#include<iostream>
#include<algorithm>
using namespace std;
int main(){
  int a,b,c;
  int runs;
  cin >> runs;
  for (int i=1; i <= runs; ++i){
	 cin >> a >> b >> c;
	 cout << "Case " << i << ": ";
	 if ( a > b ) swap(a,b);
	 if ( c < a ) swap(a,c);
	 if ( c < b ) swap(c,b);
	 cout << b << endl;
  }
  return 0;
}