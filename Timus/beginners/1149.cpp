#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

string A[205];

string toString(int n){
  string res = "";
  char dig;
  while (n){
	 dig = (char)((n%10) + '0'); 
	 n/=10;
	 res += dig;
  }
  reverse(res.begin(),res.end());
  return res;
}

void generate_A(string p,int k,int n){
	 if (k > 1){
		if (k%2) p += '+';
		else p += '-';
	 }
	 p += "sin(" + toString(k);
	 if ((k+1) <= n) generate_A(p,k+1,n);
	 for (int i=0; i < k; ++i) p += ')';
	 A[k] = p;
}

string generate_S(int k,int n){
  string tmp = A[n] + "+" + toString(k);
  if (n>1){
	 tmp = '(' + generate_S(k+1,n-1) + ')' + tmp;
  }
  return tmp;
}

int main(){
  int n;
  cin >> n;
  generate_A("",1,n);
  cout << generate_S(1,n) << endl;
  return 0;
}