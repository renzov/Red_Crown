#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> S[14];
const int MAXB = 2000000;

bool ispalin( int x, const int &base ){
	int dig[20];
	int p = 0;
	while ( x > 0 ){
		dig[p++] = x % base;
		x /= base;
	}
	for ( int l=0, r = p - 1; l < r; l++,r-- )
		if ( dig[l] != dig[r] ) return false;
	return true;
}

int main(){
	// Precalc every palindromic number in base 2, then in base 2 and 3
	// for base > 3, the only palindromes are 0 and 1
	for ( int i=2; i <= MAXB; ++i ) 
		if ( ispalin( i , 2 ) )
			S[2].push_back( i );

	for ( int j=0; j < (int)S[2].size(); ++j ){
		if ( ispalin( S[2][j] , 3 ) )
			S[3].push_back( S[2][j] );
	}
	//

	int A, B, J;
	int res = 0;
	scanf("%d %d %d", &A, &B, &J);
	
	if ( A == 0 ) res++;
	if ( A < 2 && B >= 1 ) res++;

	if ( J > 3 ){
		printf("%d\n", res);
	}
	else {
		vector<int>::iterator b = lower_bound( S[J].begin(), S[J].end(), A );
		vector<int>::iterator e = upper_bound( S[J].begin(), S[J].end(), B );
		printf("%d\n", res + (e - b));
	}
	return 0;
}
