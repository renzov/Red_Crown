#include<stack>
#include<iostream>
#include<string>
#include<cctype>
using namespace std;
int prec[300];

int main(){
  int runs;
  string s;
  cin >> runs;
  
  prec['+'] = 1;
  prec['-'] = 2;
  prec['*'] = 3;
  prec['/'] = 4;
  prec['^'] = 5;

  while (runs--){
		stack<char> S;
		cin >> s;
		for (int i=0; i < s.size(); ++i){
			 if (isalpha(s[i])){
				  cout << s[i];
			 }
			 else {
				 if (s[i]=='(') S.push(s[i]);
				 else if (s[i]==')'){
					 while (S.top()!='('){
						cout << S.top();
						S.pop();
					 }
					 S.pop();
				 }
				 else {
					 if (S.empty()) S.push(s[i]);
					 else {
						  while (!S.empty() && prec[ S.top() ] > prec[ s[i] ]) {
								cout << S.top(); S.pop();
						  }
						  S.push(s[i]);
					 }
				 }
			 }
		}
		while (!S.empty()){ cout << S.top(); S.pop(); }
		cout << endl;
  }
  return 0;
}