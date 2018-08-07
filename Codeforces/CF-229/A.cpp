#include<iostream>

using namespace std;

string u[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
string d[] = {"", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
string s[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};

int main(){
	int N;
	cin >> N;
	int a = N % 10;
	int b = N / 10;
	
	if ( b == 0 ){
		cout << u[a] << endl;
	}
	else if ( b == 1 ){
		cout << s[a] << endl;
	}
	else {
		if ( a == 0 ) cout << d[b] << endl;
		else cout << d[b] << "-" << u[a] << endl;
	}
	return 0;
}
