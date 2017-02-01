#include<iostream>
using namespace std;

int main(){

  int n;
  int s[105];
  int sum = 0;
  cin >> n;
  for (int i=0; i < n; ++i){
	 cin >> s[i];
	 sum += s[i];
  }
  int res = 0;
  for (int i=0; i < n; ++i){
	 if ( (sum - s[i]) % 2 == 0 ) res++;
  }
  cout << res << endl;
  return 0;
}