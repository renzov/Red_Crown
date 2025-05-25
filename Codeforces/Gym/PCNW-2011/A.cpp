#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

int main(){
	int N;
	string name;

	cin >> N;
	getline(cin, name);		// reads the newline
	while ( N-- ){
		getline(cin, name);
		int Bs = count( name.begin(), name.end(), 'b' ) +  count( name.begin(), name.end(), 'B' );
		int Gs = count( name.begin(), name.end(), 'g' ) +  count( name.begin(), name.end(), 'G' );
		if ( Bs > Gs ) cout << name << " is A BADDY" << endl;
		else if ( Gs > Bs ) cout << name << " is GOOD" << endl;
		else cout << name << " is NEUTRAL" << endl;
	}
	return 0;
}
