#include<iostream>
#include<algorithm>
using namespace std;
typedef pair<int,int> point;

point p[8];
bool sol;
int a[8];
int b[8];
bool used[ 8 ] = {0};
point vec[8];

long long dot(point x,point y){ return 1LL*x.first*y.first + 1LL*x.second*y.second; }

bool square(){
	long long L1 = dot( vec[0] , vec[0] );
	for (int i=1; i < 4; ++i){
		if ( dot(vec[i],vec[i]) != L1 ) return false;
	}
	for (int i=0; i < 3; ++i){
		if ( dot(vec[i],vec[i+1]) != 0LL ) return false;
   }
   return ( dot(vec[0],vec[3]) == 0LL );
}

bool rectangle(){
  long long L1 = dot( vec[0] , vec[0] );
  long long L2 = dot( vec[1] , vec[1] );
  long long L3 = dot( vec[2] , vec[2] );
  long long L4 = dot( vec[3] , vec[3] );
  if ( L1 != L3 || L2 != L4 ) return false;
  for (int i=0; i < 3; ++i){
		if ( dot(vec[i],vec[i+1]) != 0LL ) return false;
   }
   return ( dot(vec[0],vec[3]) == 0LL );
}

void backtrack( int pos , int left ){
  if ( left == 0 ){
	 for (int i=0,j=0; i < 8; ++i) if (!used[i]) b[j++] = i;
	 sort(a,a+4);
	 sort(b,b+4);
	 bool sq = false;
	 bool rec = false;
	 do {
		for (int i=0; i<3; ++i){ 
		  vec[i].first = p[ a[i] ].first - p[ a[i+1] ].first;
		  vec[i].second = p[ a[i] ].second - p[ a[i+1] ].second;
		}
		vec[3].first = p[ a[3] ].first - p[ a[0] ].first;
		vec[3].second = p[ a[3] ].second - p[ a[0] ].second;
		sq = square();
	 }	
	 while ( !sq && next_permutation( a , a + 4 ) );
	 if ( !sq ) return;
	 do {
		for (int i=0; i<3; ++i){ 
		  vec[i].first = p[ b[i] ].first - p[ b[i+1] ].first;
		  vec[i].second = p[ b[i] ].second - p[ b[i+1] ].second;
		}
		vec[3].first = p[ b[3] ].first - p[ b[0] ].first;
		vec[3].second = p[ b[3] ].second - p[ b[0] ].second;
		rec = rectangle();
	 }
	 while ( !rec && next_permutation(b , b + 4) );
	 if ( !rec ) return;
	 sol = true;
	 /* Print sol */
	 cout << "YES" << endl;
	 cout << a[0] + 1;
	 for (int i=1; i < 4; ++i) cout << " " << a[i] + 1; cout << endl;
	 cout << b[0] + 1;
	 for (int i=1; i < 4; ++i) cout << " " << b[i] + 1; cout << endl;
	 return;
  }
  for (int i=pos; i <= (8-left) && !sol; ++i){
		a[4-left] = i;
		used[i] = true;
		backtrack( i + 1 , left - 1 );
		used[i] = false;
  }
}


int main(){
  sol = false;
  for (int i=0; i < 8; ++i) cin >> p[i].first >> p[i].second;
  backtrack( 0 , 4 );
  if ( !sol ) cout << "NO" << endl;
  return 0;
}