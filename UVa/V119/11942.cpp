#include<iostream>
using namespace std;
int main(){
  int a[15];
  int runs;
  bool ok;
  int ord;
  cin >> runs;
  cout << "Lumberjacks:" << endl;
  while (runs--){
	 for (int i=0; i<10; ++i) cin >> a[i];
	 ord = 0;
	 ok = true;
	 for (int i=1; i < 10 && ok; ++i){
		if ( ord > 0 ){
		  if ( a[i] < a[i-1] ) ok = false;
		}
		else if ( ord < 0 ){
		  if ( a[i] > a[i-1] ) ok = false;
		}
		else {
		  if ( a[i] > a[i-1] ) ord = 1;
		  else if ( a[i] < a[i-1] ) ord = -1;
		}
	 }
	 if ( ok ) cout << "Ordered" << endl;
	 else cout << "Unordered" << endl;
  }

  return 0;
}