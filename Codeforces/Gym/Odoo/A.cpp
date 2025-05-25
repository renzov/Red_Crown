#include<iostream>
#include<string>
#include<cctype>
#include <cstddef>

using namespace std;

int main(){
	
	string mail;

	cin >> mail;
	
	size_t p1 = mail.find_first_of("@");

	if ( p1 == string::npos ){
		cout << "no\n";
		return 0;
	}

	string S = mail.substr( 0, p1 ); 

	size_t p2 = mail.find_first_of(".", p1 + 1);

	if ( p2 == string::npos ){
		cout << "no\n";
		return 0;
	}

	string server = mail.substr( p1 + 1, p2 - p1 - 1 );
	string com = mail.substr( p2 + 1 );
	
	if ( S.length() < 2 || S.length() > 4  || server != "odoo" || com != "com" ){
		cout << "no\n";
		return 0;
	}

	for ( int i = 0; i < S.length(); ++i ){
		if ( !islower( S[i] ) ){
			cout << "no\n";
			return 0;
		}
	}

	cout << "yes\n"; 
	return 0;
}
