#include<string>
#include<iostream>
#include<map>
using namespace std;

string a,b;
int p,q;

map<string,string> H;
map<char,string> B;
void init(){
  H["0000"] = "0"; H["0001"] = "1"; H["0010"] = "2"; H["0011"] = "3";
  H["0100"] = "4"; H["0101"] = "5"; H["0110"] = "6"; H["0111"] = "7";
  H["1000"] = "8"; H["1001"] = "9"; H["1010"] = "A"; H["1011"] = "B"; 
  H["1100"] = "C"; H["1101"] = "D"; H["1110"] = "E"; H["1111"] = "F";
  B['0'] = "0000"; B['1'] = "0001"; B['2'] = "0010"; B['3'] = "0011";
  B['4'] = "0100"; B['5'] = "0101"; B['6'] = "0110"; B['7'] = "0111";
  B['8'] = "1000"; B['9'] = "1001"; B['A'] = "1010"; B['B'] = "1011";
  B['C'] = "1100"; B['D'] = "1101"; B['E'] = "1110"; B['F'] = "1111";
}

string add(){
  string res = "";
  bool eq = true;
  if ( a[p] == '1' && b[q] == '1' ){
	 p++; q++;
	 res = "1";
	 res = (a[p] == b[q])? (res+a[p]):"10";
	 p++,q++;
	 return res;
  }
  else {
	 if ( a[p] == '0' && b[q] == '1' ){
		p++;
		string ul = add(); q-=2;
		string ur = add(); q-=2; 
		string ll = add(); q-=2;
		string lr = add();
		if (  ul[0] == '0' || ur[0] == '0' || ll[0] == '0' || lr[0] == '0' ) eq = false;
		if ( !eq ) return "0" + ul + ur + ll + lr;
		else if ( ul[1] == ur[1] && ul[1] == ll[1] && ul[1] == lr[1] ){
		  res = "1";
		  return res + ul[1];
		}
		else {
		  return "0" + ul + ur + ll + lr;
		}
	 }
	 else if ( a[p] == '1' && b[q] == '0' ){
		q++;
		string ul = add(); p-=2;
		string ur = add(); p-=2;
		string ll = add(); p-=2;
		string lr = add();
		if (  ul[0] == '0' || ur[0] == '0' || ll[0] == '0' || lr[0] == '0' ) eq = false;
		if ( !eq ) return "0" + ul + ur + ll + lr;
		else if ( ul[1] == ur[1] && ul[1] == ll[1] && ul[1] == lr[1] ){
		  res = "1";
		  return res + ul[1];
		}
		else {
		  return "0" + ul + ur + ll + lr;
		}
	 }
	 else {
		p++,q++;
		string ul = add();
		string ur = add();
		string ll = add();
		string lr = add();
		if (  ul[0] == '0' || ur[0] == '0' || ll[0] == '0' || lr[0] == '0' ) eq = false;
		if ( !eq ) return "0" + ul + ur + ll + lr;
		else if ( ul[1] == ur[1] && ul[1] == ll[1] && ul[1] == lr[1] ){
		  res = "1";
		  return res + ul[1];
		}
		else {
		  return "0" + ul + ur + ll + lr;
		}
	 }
  }
}

string to_hex(string s){
  string res = "";
  for (int i=0; i < s.size(); i+=4){
	 res += H[ s.substr(i,4) ];
  }
  return res;
}

string to_bin(string s){
  string res = "";
  for (int i=0; i < s.size(); ++i)
	res += B[ s[i] ];
  return res;
}

int main(){
  init();
  int cases = 0;
  string x,y;
  while ( cin >> x >> y ){
	 cases++;
	 if ( x == "0" && y == "0" ) break;
	 a = to_bin(x);
	 b = to_bin(y);
	 p=q=0;
	 for ( ; a[p] != '1' ; p++ );
	 p++;
	 for ( ; b[q] != '1' ; q++ );
	 q++;
	 string res = add();
	 res = "1" + res;
	 while ( res.size() % 4 ){
		res = "0" + res; 
	 }
	 if ( cases > 1 ) cout << endl;
	 cout << "Image " << cases << ":" << endl; 
	 cout << to_hex( res ) << endl;
  }
  return 0;
}