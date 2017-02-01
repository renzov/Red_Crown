#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
int main(){
  int maxi; 
  int runs;
  string s[15];
  int r[15];
  cin >> runs;
  for (int k=1; k <= runs; ++k){
	 maxi = -1;
	 for (int i=0; i < 10; ++i){
		cin >> s[i] >> r[i];
		if (r[i] > maxi) maxi = r[i];
	 }
	 cout << "Case #" << k << ":" << endl;
	 for (int i=0; i < 10; ++i){
		if ( r[i] == maxi ) cout << s[i] << endl;
	 }
  }
  return 0;
}