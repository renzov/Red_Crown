#include<sstream>
#include<string>
#include<algorithm>
#include<set>
#include<iostream>
using namespace std;

int main(){
  string line;
  int N,M,I;
  int x;
  while ( getline(cin,line) ){
	 N = M = I = 0;
	 stringstream in(line);
	 set<int> S;
	 while ( in >> x ) S.insert(x); 
	 N = S.size();
	 getline( cin, line );
	 stringstream in2(line);
	 while ( in2 >> x ){
		M++;
		if ( S.find( x ) != S.end() ) I++;
	 }
	 if ( I == 0 ) cout << "A and B are disjoint" << endl;
	 else if ( I == N && I == M ){
		cout << "A equals B" << endl;
	 }
	 else if ( N == I ){
		cout << "A is a proper subset of B" << endl;
	 }
	 else if ( M == I ){
		cout << "B is a proper subset of A" << endl;
	 }
	 else {
		cout << "I'm confused!" << endl;
	 }
  } 

  return 0;
}