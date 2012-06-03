#include<iostream>
#include<string>
#include<sstream>
#include<cctype>
#include<vector>
using namespace std;

inline int value(char c){
  return isdigit(c)? (c-'0'):10;
}

int main(){
  int val;
  char c;
  string line;
  while (getline(cin,line) && line != "Game Over"){
	 vector<int> v;
	 stringstream in(line);
	 while (in >> c){
		val = value(c);
		v.push_back(val);
		if (val < 10){
		  in >> c;
		  val = value(c);
		  if (val != 10) v.push_back(val);
		  else v.push_back( 10 - v.back() );
		}
	 }

	 int res = 0;
	 for (int i=0,j=0; i < 10 ; ++i,++j){
		if (v[j] == 10){
		  res += (v[j] + v[j+1] + v[j+2]);
		}
		else if ( (v[j] + v[j+1]) == 10){
		  res += (v[j] + v[j+1] + v[j+2]);
		  j++;
		}
		else {
			 res += (v[j] + v[j+1]);
			 j++;
		}
	 }
	 cout << res << endl;
  }
  return 0;
}