#include<cstdio>
#include<iostream>
#include<cstring>
#include<cctype>
#include<string>
#include<algorithm>
#include<cmath>
#include<queue>
#include<vector>
#include<stack>
#include<set>
#include<map>
#include<list>
#include<climits>
using namespace std;
#define forn(i,n) for ( int i=0; i < (int)(n); ++i )
const double EPS = 1e-8;
double arr[ 100005 ];

int main(){
  int n,a,d;
  double ari;
  int v,t;
  double t2,t3,t4;
  double d2,d3;
  scanf("%d %d %d",&n,&a,&d);
  forn(i,n){
	 scanf("%d %d",&t,&v);
	 d2 = ((double)v*v) / (2*a);
	 if ( d2 > d || fabs(d2-d) < EPS ){
		t3 = sqrt((double)2*d / a);
		t4 = t3 + t;
	 }
	 else {
		  d3 = d - d2;
		  t2 = d3 / v;
		  t3 = ((double)v)/a;
		  t4 = t3 + t2 + t;
	 }
	 
	 if ( i ) arr[i] = max(  t4 , arr[i-1] );
	 else arr[i] = t4;
  }
  forn(i,n){
	 printf("%lf\n",arr[i]);
  }
  return 0;
}