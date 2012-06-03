#include<string>
#include<algorithm>
#include<iostream>
using namespace std;

int main(){
  int n;
  string a[60];
  while (cin >> n && n){
		for (int i=0; i < n; ++i) cin >> a[i];
		for (int i=0; i < n-1; ++i){
			 for (int j=i+1; j < n; ++j){
				  if ( (a[i] + a[j]) < (a[j]+a[i]) ){
					 swap(a[i],a[j]);
				  }
			 }
		}
		for (int i=0; i < n; ++i) cout << a[i];
		cout << endl;
  }
  return 0;
}
