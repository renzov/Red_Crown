#include<iostream>
#include<cstdio>
using namespace std;
const int MAXN = 100000;
bool nsp[ MAXN + 2 ] = {0};
long long p[ 10000 ];
long long fact[ 100000 ];
int n;

void sieve(){
  p[0] = 2;
  n = 1;
  long long i,j;
  for ( i=4; i <= MAXN; i+=2 ) nsp[i] = true;
  for ( i=3; i < MAXN; i+=2 ){
	 if ( !nsp[i] ){
		p[n++] = i;
		for ( j=i*i; j < MAXN; j+=i)
		  nsp[j] = true;
	 }
  }
}

int main(){
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);  
  sieve();
  long long k,tmp;
  cin >> k;
  int i;
  tmp = k;
  long long sum = 0;
  long long pot;
  int m = 0;
  
  if ( k == 1 ){
	 cout << 1 << endl << 1 << endl;
	 return 0;
  }
  for( i=0; i < n && ((p[i]*p[i]) <= k) && (tmp > 1) ; ++i ){
	 pot = 1;
	 while ( (tmp%p[i]) == 0 ){
		tmp /= p[i]; pot *= p[i];
	 }
	 if ( pot > 1 ){ sum += pot; fact[m++] = pot; }
  }
  if ( tmp > 100000 ){
	 cout << "No solution" << endl;
  }
  else {
	 if ( tmp > 1 ){
		sum += tmp;
		fact[m++] = tmp;
	 }
	 if ( sum > MAXN ){
		 cout << "No solution" << endl;
	 }
	 else {
		bool first = true;
		cout << sum << endl;
		long long base = 1;
		for ( int i=0; i < m; ++i ){
		  for ( int j=1; j < fact[i]; ++j ){
			 if ( !first ) cout << ' ';
			 else first = false;
			 cout << base + j;
		  }
		  if ( !first ) cout << ' ';
		  cout << base;
		  base += fact[i];
		}
		cout << endl;
	 }
  }
}