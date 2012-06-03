#include<stack>
#include<string>
#include<iostream>
#include<cctype>
using namespace std;

int main(){
  int runs;
  string l;
  string a,b,c;
  cin >> runs;
  while (runs--){
	 cin >> l;
	 stack<string> s;
	 for (int i=0; i < l.size(); ++i){
		  if (islower(l[i])){
				c = ""; c += l[i];
				s.push( c );
		  }
		  else {
			 b = s.top(); s.pop();
			 a = s.top(); s.pop();
			 c = a; c += l[i]; c += b;
			 s.push(c);
		  }
	 }
	 cout << s.top() << endl;
  }
  return 0;
}