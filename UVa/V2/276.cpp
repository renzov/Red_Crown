#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

long long to_number(string &s){
  long long num = 0;
  for (int i=0; i < s.size(); ++i){
		switch (s[i]){
			 case '|' : num++; break;
			 case 'n' : num += 10; break;
			 case '9' : num += 100; break;
			 case '8' : num += 1000; break;
			 case 'r' : num += 10000; break;
		}
  }
  return num;
}

string to_string(long long p){
  string res = "";
  while (p >= 10000){ p-=10000; res += 'r'; }
  if (p>=1000 && res != "") res += ' ';
  while (p >= 1000){ p-=1000; res += '8'; }
  if (p>=100 && res != "") res += ' ';
  while (p >= 100){ p-=100; res += '9'; }
  if (p>=10 && res != "") res += ' ';
  while (p >= 10){ p-=10; res += 'n'; }
  if (p>=1 && res != "") res += ' ';
  while (p >= 1){ p--; res += '|'; }
  reverse(res.begin(),res.end());
  return res;
}

int main(){
  long long a,b,c;
  long long p;
  string line;
  string res;
  while (getline(cin,line)){
		a = to_number(line);
		getline(cin,line);
		b = to_number(line);
		//cout << "a = " << a << " b = " << b << endl;
		if (a==0 || b==0) break; 
		c = a * b;
		p = 1;
		while (p <= b){
			 res = to_string(p);
			 if (b & p){
				  res += " *";
			 }
			 while (res.size() < 34) res+=' ';
			 res += to_string((long long)(p*a)%100000);
			 cout << res << "\n";
			 p<<=1;
		}
		//cout << (a*b)%100000 << " " << a*b << endl;
		cout << "The solution is: " << to_string(c%100000) << "\n";
  }
  return 0;
}