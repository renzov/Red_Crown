#include<string>
#include<stack>
#include<iostream>
using namespace std;

int main(){
  string s;
  while (cin >> s){
	 stack< pair<char,int> > S;
	 pair<char,int> p;
	 bool ok = true;
	 int pos = 0;
	 for (int i=0; i < s.size() && ok; ++i,pos++){
		  switch (s[i]){
			 case '(' :  if (i+1 < s.size() && s[i+1] == '*'){
								S.push( make_pair('#',pos) );
								i++;
							 }
							 else {
								S.push( make_pair(s[i],pos) );
							 }
							 break;
			 case '[' :  S.push( make_pair(s[i],pos) ); break;
			 case '{' :  S.push( make_pair(s[i],pos) ); break;
			 case '<' :  S.push( make_pair(s[i],pos) ); break;
			 
			 case '*' :  if (i+1 < s.size() && s[i+1] == ')'){
								if (S.empty()){ ok = false; }
								else {
									 p = S.top();
									 S.pop();
									 ok = p.first == '#'; 
								}
								p.second = pos;
								i++;
							 } 
							 break;
			 case ')' :  if (S.empty()){ ok = false; }
							 else {
									 p = S.top();
									 S.pop();
									 ok = p.first == '('; 
							 }
							 p.second = pos;
							 break;
			 case ']' :  if (S.empty()){ ok = false; }
						    else {
								p = S.top();
								S.pop();
								ok = p.first == '[';
						    }
						    p.second = pos;
                      break;
			 case '}' :  if (S.empty()){ ok = false; }
						    else {
								p = S.top();
								S.pop();
								ok = p.first == '{'; 
						    }
						    p.second = pos;
						    break;
			 case '>' :  if (S.empty()){ ok = false; }
						    else {
								p = S.top();
								S.pop();
								ok = p.first == '<'; 
								
						    }
						    p.second = pos;
							 break;
		  }
		  //if (!ok) cout << "char = " << s[i-1] << " " << s[i] << endl;
	 }
	 if (ok && !S.empty()){
		p.second = pos;
		ok = false;
	 }
	 if (ok) cout << "YES" << endl;
	 else cout << "NO " << p.second + 1 << endl;
	 //cout << "pos = " << pos << endl;
  }
  return 0;
}