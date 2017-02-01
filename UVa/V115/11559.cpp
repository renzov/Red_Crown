#include<iostream>
#include<climits>
using namespace std;
int main(){
  int n,b,h,w;
  int res;
  int p,m,c;
  while ( cin >> n >> b >> h >> w){
	 res = INT_MAX;
	 for (int i=0; i < h; ++i){
		cin >> p;
		m = 0;
		for (int j=0; j < w; ++j){
		  cin >> c;
		  if ( c > m ) m = c;
		}
		if ( m >= n && p < res ){
		  res = p;
		}
	 }
	 if ( res == INT_MAX || (n*res) > b ) cout << "stay home" << endl;
	 else cout << res*n << endl;
  }

  return 0;
}