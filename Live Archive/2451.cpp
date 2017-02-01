#include<string>
#include<iostream>
#include<cstring>
using namespace std;
const int IN_SIG = -2;
const int IN_PRE = -3;
int memo[105][105];
int move[105][105];
int n;
string s;

string print_sol(int l,int r){
  if ( l > r ) return "";
  if ( l==r ){
	 if ( s[l] == '(' || s[l] == ')'  ){ return "()"; }
	 return "[]";
  }
  if ( move[l][r] == IN_PRE ){
	 string res = print_sol( l + 1 , r );
	 if ( s[l] == ')' ) res = "()" + res;
	 else res = "[]" + res;
	 return res;
  }
  if ( move[l][r] == IN_SIG ){
	 string res = print_sol( l + 1 , r );
	 if ( s[l] == '(' ) res = "()" + res;
	 else res = "[]" + res;
	 return res;
  }
  else {
	 int k = move[l][r];
	 string res = s[l] + print_sol( l+1, k-1 );
	 res = res + s[k];
	 res = res + print_sol(k+1,r);
	 return res;
  }
}

int solve(int l,int r){
  if ( r < l ) return 0;
  if ( l == r ){
	 if ( s[l] == '(' || s[l] == '[' ){ move[l][r] = IN_SIG; return 1; }
	 move[l][r] = IN_PRE; return 1;
  }
  if ( memo[l][r] != -1 ) return memo[l][r];
  int k;
  char next;
  int tmp;
  if ( s[l] == '(' || s[l] == '[' ){
	 memo[l][r] = 1 + solve( l+1 , r );
	 move[l][r] = IN_SIG;
	 next = (s[l] == '(') ? ')':']';
	 for (k=l+1; k <= r; ++k){
		if ( s[k] == next ){
		  tmp = solve( l+1 ,k-1) + solve( k+1 , r );
		  if ( tmp < memo[l][r]){
			 memo[l][r] = tmp;
			 move[l][r] = k;
		  }
		}
	 }
  }
  else {
	 memo[l][r] = 1 + solve(l+1,r);
	 move[l][r] = IN_PRE;
  }
  return memo[l][r];
}

int main(){
  int runs;
  int i,j;
  cin >> runs;
  getline(cin,s);
  while (runs--){
	 getline(cin,s);
	 getline(cin,s);
	 n = s.size();
	 if (n==0) cout << endl;
	 else {
		for (i=0; i < n; ++i)
		for (j=0; j < n; ++j)
		  memo[i][j] = -1;
		solve( 0 , n-1 );
		cout << print_sol(0,n-1) << endl;
	 }
	 if (runs) cout << endl;
  }

  return 0;
}