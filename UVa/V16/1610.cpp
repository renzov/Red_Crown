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


int main(){
	int N,m;
	while (cin >> N && N){
		vector<string> S(N);		
		for (int i=0; i<N; ++i) cin >> S[i];
		sort(all(S));
		m = (N >> 1) - 1;
		string res = "";

		string temp = S[m+1]

		for (int i=0; i<S[m].size() && i < S[m+1].size(); ++i){
			if (S[m][i] != S[m+1][i]){
				if ( abs(S[m][i] - S[m+1][i]) > 1 ){
					res += (char)(S[m][i] + 1);
					break;
				}
				else {
					res += S[m+1][i];
					break;
				}
			}
			else {
				res += S[m+1][i];
			}
		}
		if (res == S[m+1]) res = S[m];
		else if (res.size() == S[m].size() && res > S[m]) res = S[m];
		cout << res << endl;
	}
	
	return 0;
}

