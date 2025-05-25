#include<iostream>
#include<string>
#include<list>
using namespace std;

list<char> res;
list<char>::iterator act;

void insert( const char &c ){
	res.insert( act, c );
}

void del(){
	if ( act != res.begin() ){
		list<char>::iterator e = act;
		e--;
		res.erase(e);
	}
}

void go_front(){
	if ( act != res.end() )
		act++;
}

void go_back(){
	if ( act != res.begin() )
		act--;
}

void process(){
	string op;
	cin >> op;

	act = res.begin();	
	for ( int i = 0; i < (int)op.size(); ++i ){
		switch (op[i]){
			case '-' : del(); break;
			case '<' : go_back(); break;
			case '>' : go_front(); break;
			default: insert( op[i] ); 
		}
	}
	for ( list<char>::iterator it = res.begin(); it != res.end(); ++it )
		cout << *it;
	cout << endl;
	res.clear();
}

int main(){
	int runs;

	cin >> runs;
	while ( runs-- )
		process();
	return 0;
}
