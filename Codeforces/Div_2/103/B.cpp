#include<cstdio>
#include<iostream>
#include<cmath>
#include<string>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<algorithm>
using namespace std;
#define forn(i,n) for(int i=0; i < (int)(n); ++i )
const double EPS = 1e-8;
int cx[1005];
int cy[1005];
int r[1005];

int D( int x, int y ){
  return x*x + y*y;
}

int main(){
  int n;
  int xmin,xmax,ymin,ymax;
  int res = 0;
  cin >> xmin >> ymin >> xmax >> ymax;
  if ( xmax < xmin ) swap(xmax,xmin);
  if ( ymax < ymin ) swap(ymax,ymin);
  cin >> n;
  bool f;
  forn(i,n){ cin >> cx[i] >> cy[i] >> r[i]; }  
  for ( int i=xmin; i <= xmax ; ++i ){
	 f = false;
	 for( int j=0; j < n && !f ; ++j ){
		if ( D(i-cx[j],ymin-cy[j]) <= r[j]*r[j] ){
		  f = true;
		}
	 }
	 if ( !f ){ res++; }
	 f = false;
	 for( int j=0; j < n && !f ; ++j ){
		if (D(i-cx[j],ymax-cy[j]) <= r[j]*r[j]){
		  f = true;
		}
	 }
	 if ( !f ){ res++; }
  }
  for ( int i=ymin+1; i < ymax; ++i ){
	 f = false;
	 for( int j=0; j < n && !f ; ++j ){
		if ( D(xmin-cx[j],i-cy[j]) <= r[j]*r[j] ){
		  f = true;
		}
	 }
	 if ( !f ){ res++; }
	 f = false;
	 for( int j=0; j < n  && !f; ++j ){
		if ( D(xmax-cx[j],i-cy[j]) <= r[j]*r[j] ){
		  f = true;
		}
	 }
	 if ( !f ){ res++; }
  }
  cout << res << endl;
  return 0;
}