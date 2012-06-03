#include<algorithm>
#include<iostream>
using namespace std;
int main(){
  int n;
  int runs;
  int a[105];
  cin >> runs;
  for(int i=1; i <= runs; ++i){
	 cin >> n;
	 for (int j=0; j < n; ++j) cin >> a[j];
	 cout << "Case " << i << ": " << *max_element(a,a+n) << endl;
  }
  return 0;
}