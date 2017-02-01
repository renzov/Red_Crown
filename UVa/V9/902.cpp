#include<string>
#include<iostream>
#include<map>
using namespace std;

int main(){
  int n;
  int v;
  string s;
  int maxi;
  string tmp;
  string best;
  while (cin >> n >> s){
	 maxi = 0;
	 map<string,int> hash;
	 for (int i=0; i < (s.size() - n + 1); ++i){
		tmp = s.substr(i,n);
		v = ++hash[tmp];
		if (v > maxi) maxi = v,best = tmp;
	 }
	 cout << best << endl;
  }
  return 0;
}