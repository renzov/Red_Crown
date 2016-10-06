#include<string>
#include<iostream>
using namespace std;

int main(){
	int cases = 0;
	string inp;
	while ( cin >> inp && inp != "#" ){
		cases++;
		cout << "Case " << cases << ": "; 
		if ( inp == "HOLA" ){
			cout << "SPANISH" << endl;
		}
		else if ( inp == "HELLO" ){
			cout << "ENGLISH" << endl;
		}
		else if ( inp == "CIAO" ){
			cout << "ITALIAN" << endl;
		}
		else if ( inp == "HALLO" ){
			cout << "GERMAN" << endl;
		}
		else if ( inp == "BONJOUR" ){
			cout << "FRENCH" << endl;
		}
		else if ( inp == "ZDRAVSTVUJTE" ){
			cout << "RUSSIAN" << endl;
		}
		else {
			cout << "UNKNOWN" << endl; 
		}
	}

	return 0;
}
