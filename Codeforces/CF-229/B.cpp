#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

int size[] = {0, 2, 4, 8, 16, 32, 64, 128, 256, 512}; 

int main(){
	string num;
	cin >> num; 
	reverse( num.begin(), num.end() );
	
	int base = 0; 
	int extra = 0;
	for ( int i=0; i < num.length(); ++i ){
		base += size[i];
		if ( num[i] == '7' ) extra += ( 1 << i );
	}
	cout << base + extra + 1 << endl;
	return 0;
}
