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

const int MAXN = 1200;
int L[MAXN];

int main(){
	int runs = 0;
	string name;
	int N,K;
	int sum;
	while ( cin >> N >> K && N && K ){
		runs++;
		for ( int i=0; i < N; ++i ){ 
			cin >> name;
			L[i] = (int)name.size();
		}
		sort( L , L + N );
		bool ok = true;
		for ( int i=0; i < N && ok; i += K ){
			sum = 0;
			for ( int j=0; j < K; ++j ){
				sum += L[i+j];
			}
			
			for ( int j=0; j < K && ok; ++j ){
				if ( abs(L[i+j]*K - sum) > 2*K ) ok = false; 
			}
		} 
		if ( runs > 1 ) cout << endl;
		cout << "Case " << runs << ": ";
		if ( ok ) cout << "yes" << endl;
		else cout << "no" << endl;
	}

	return 0;
}

