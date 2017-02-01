#include<iostream>
using namespace std;
int main(){
  int runs;
  long long a,b;
  cin >> runs;
  while (runs--){
	 cin >> a >> b;
	 if ( a < b ) cout << "<" << endl;
	 else if ( a > b ) cout << ">" << endl;
	 else cout << "=" << endl;
  }
  return 0;
}