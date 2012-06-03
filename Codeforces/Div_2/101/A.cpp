#include<iostream>
#include<string>
using namespace std;
#define forn(i,n) for (int i=0; i < (int)(n); ++i)

int main(){
  string a,b,c;

  int A[26]={0};
  int B[26]={0};

  cin >> a >> b >> c;
  forn(i,a.size()){
	 A[ a[i] - 'A' ]++;
  }
  forn(i,b.size()){
	 A[ b[i]-'A' ]++;
  }
  forn(i,c.size()){
	 B[ c[i]-'A' ]++;
  }
  bool ok = true;
  forn(i,26){
	 ok &= ( A[i] == B[i] );
  }
  if ( ok ) cout << "YES" << endl;
  else cout << "NO" << endl;

  return 0;
}