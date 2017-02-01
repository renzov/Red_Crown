#include<iostream>
#include<map>
#include<string>
using namespace std;

int main(){
  string s,a;
  getline(cin,s);

  map<char,string> H;
  H['>'] = "1000";
  H['<'] = "1001";
  H['+'] = "1010";
  H['-'] = "1011";
  H['.'] = "1100";
  H[','] = "1101";
  H['['] = "1110";
  H[']'] = "1111";
  int res = 0;
  for (int i=0; i<s.size(); ++i){
	 a = H[s[i]];
	 for (int j=0; j < a.size(); ++j){
		res *= 2;
		res += (a[j] - '0');
		res %= 1000003;
	 }
  }
  cout << res << endl;
  return 0;
}
