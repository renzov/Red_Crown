#include<iostream>
using namespace std;
int main(){

  int n;
  long long t[25] = {0};
  cin >> n;
  int a;

  for (int i=0; i<n; ++i){ cin >> a; t[a+10]++; }
  long long res = 0;
  for (int i=0; i < 10; ++i){
	 res += t[ i ]*t[ 20 - i ];
  }
  res += (t[10]*(t[10]-1))/2;
  cout << res << endl;
  return 0;
}