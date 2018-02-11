#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <numeric>

#define repn( i , a , b ) for( int i = ( int ) a ; i < ( int ) b ; i ++ )
#define rep( i , n ) repn( i , 0 , n ) 
#define all( x )  x.begin() , x.end()
#define rall( x ) x.rbegin() , x.rend()
#define mp make_pair
#define fst first
#define snd second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

map<string,string> M;

int main(){
	string A, B;
	int N;
	cin >> N;

	for ( int i=0; i < N; ++i ){
		cin >> A >> B;
		M[B] = A;
	}
	bool found = false;
	int cnt = 0;
	while ( !found ){
		cin >> A;
		if ( A.back() == '.' ){
			found = true;
			A.pop_back();
		}
		if ( cnt ) cout << ' ';
		if ( M.find(A) != M.end() ){
			cout << M[A];
		}
		else {
			cout << A;
		}
		if ( found ) cout << '.' << endl;
		cnt++;
	}
	return 0;
}

