#include<iostream>
#include<string>
using namespace std;

bool isvowel( const char &c ){
	return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int countV( string &w ){
	int cnt = 0;
	for ( int i=0; i < w.size(); ++i )
		if ( isvowel( w[i] ) ) cnt++;
	return cnt;
}

int main(){
	string word;
	int res = 0;
	while ( cin >> word ){
		res += countV(word);
		if ( word.back() == 'y' ) res++;
	}
	cout << res << endl;
}
