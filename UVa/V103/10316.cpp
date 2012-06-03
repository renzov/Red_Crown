#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;
const double PI = 2*acos(0);
const double EPS = 1e-8;
double GCDist(double pLat ,double pLon,double qLat ,double qLon){
  pLon *= PI/180; pLat *= PI/180;
  qLon *= PI/180; qLat *= PI/180;
  return 	 acos( cos(pLat)*cos(pLon)*cos(qLat)*cos(qLon) + 
						 cos(pLat)*sin(pLon)*cos(qLat)*sin(qLon) +
						 sin(pLat)*sin(qLat) ) ;
}

int main(){
  int res;
  double d,t,mini;
  int n;
  double C[1005][2];
  while ( cin >> n ){
	 for ( int i=0; i < n; ++i ) cin >> C[i][0] >> C[i][1];
	 mini = 10e10;
	 for ( int i=0; i < n; ++i ){
		t = 0.0;
		for ( int j=0; j < n; ++j ){
		  if ( i != j ){
			 d = GCDist( C[i][0], C[i][1] , C[j][0], C[j][1] );
		  }
		  else d = 0.0;
		  if ( t < d ) t = d;
		}
		if ( fabs( t - mini ) < EPS ){
		  res = i;
		}
		else if ( t < mini ){
		  res = i; mini = t;
		}
	 }
	 cout << setiosflags(ios::fixed) << setprecision(2) << C[res][0] << " " << C[res][1] << endl;
  }
  return 0;
}