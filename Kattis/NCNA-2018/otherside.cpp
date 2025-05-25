#include<iostream>
using namespace std;

string ans( const int &W, const int &S, const int &C, const int &K ){
	if ( K == 0 ) return "NO";
	if ( S < K ) return "YES";
	if ( W + C < K ) return "YES";
	if ( S == K && W + C <= 2*K ) return "YES";
	if ( W + C == K && S <= 2*K ) return "YES";
	return "NO";
}

int main(){
	int W, S, C, K;

	cin >> W >> S >> C >> K;
	cout << ans( W, S, C, K ) << endl;
	return 0;
}
