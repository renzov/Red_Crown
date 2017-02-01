#include<iostream>
#include<string>
using namespace std;

int main(){
  int runs;
  int n;
  string s;

  cin >> runs;
  for (int k=1; k <= runs; ++k){
		cin >> n >> s;
		if (n >= 1) s.erase(n-1,1);
		cout << k << " " << s << endl;
  }
  return 0;
}