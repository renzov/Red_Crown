#include<iostream>
using namespace std;

int main(){
  
	int n,x;
	int a[200];
	
	cin >> n;
	for (int i=1; i <= n; ++i){
		cin >> x;
		a[x-1] = i;
	}
	for (int i=0; i < n; ++i){
		if ( i > 0) cout << " ";
		cout << a[i];
	}
	cout << endl;
	return 0;
}
