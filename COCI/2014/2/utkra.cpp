#include<iostream>
#include<string>
#include<set>
using namespace std;

int main(){
	int N;
	string name;
	cin >> N;
	multiset<string> S;
	multiset<string>::iterator it;

	for ( int i=0; i < N; ++i ){
		cin >> name;
		S.insert(name);
	}
	for ( int i=1; i < N; ++i ){
		cin >> name;
		it = S.find( name );
		S.erase( it );
	}
	cout << *S.begin() << endl;
	return 0;
}
