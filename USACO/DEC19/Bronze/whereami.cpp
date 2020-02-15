#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<set>
using namespace std;

string word;
int N;

bool test( const int &size ){
	set<string> S;
	string sub;
	for ( int i=0; i <= (N - size); ++i ){
		sub = word.substr( i, size );
		if ( S.find( sub ) != S.end() ) return false;
		S.insert(sub);
	}
	return true;
}

int main(){

	freopen ("whereami.in", "r", stdin);
	freopen ("whereami.out", "w", stdout);

	cin >> N;
	cin >> word;
	int l = 0;
	int r = N;
	int m;
	while ( r - l > 1 ){
		m = ( l + r  ) >> 1;
		if ( test(m) )
			r = m;
		else
			l = m;
	}
	cout << r << endl;
	return 0;
}
