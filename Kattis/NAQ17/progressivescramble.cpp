#include<string>
#include<iostream>
#include<cctype>
using namespace std;

int val[128];

int get( const char &c ){
	if ( isspace(c) ) return 0;
	return (c - 'a') + 1;
}

char chr( const int &v ){
	if ( !v ) return ' ';
	return (char)((v - 1) + 'a');
}

int main(){
	int runs;
	char opt;
	string line;

	cin >> runs;
	while ( runs-- ){
		cin >> opt;
		cin.get();
		getline( cin, line );
		if ( opt == 'e' ){
			val[0] = get(line[0]);		
			for ( int i=1; i < (int)line.size(); ++i ){
				val[i] = val[i-1] + get(line[i]);
			}
		}
		else {
			val[0] = get(line[0]);
			int sum = val[0];
			for ( int i=1; i < (int)line.size(); ++i ){
				val[i] = get(line[i]) - sum;
				if ( val[i] < 0 ) val[i] += 27;
				sum += val[i];
				sum %= 27;
			}
		}

		for (int i=0; i < (int)line.size(); ++i ){
			cout << chr( val[i] % 27 );
		}
		cout << endl;
	}
	return 0;
}
