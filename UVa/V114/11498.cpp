#include<iostream>
using namespace std;

int main(){

  int runs;
  int N,M;
  int x,y;
  while (cin >> runs && runs){
	 cin >> N >> M;
	 for (int i=0; i<runs; ++i){
		cin >> x >> y;
		if ( x==N || y==M ) cout << "divisa" << endl;
		else if ( x < N && y > M ){
		  cout << "NO" << endl;
		}
		else if ( x < N && y < M ){
		  cout << "SO" << endl;
		}
		else if ( x > N && y > M ){
		  cout << "NE" << endl;
		}
		else {
		  cout << "SE" << endl;
		}
	 }
  }
  return 0;
}