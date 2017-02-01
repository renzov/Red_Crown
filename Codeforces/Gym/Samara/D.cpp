#include<cstdio>
#include<iostream>
using namespace std;
int main(){
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  long long n,k;
  long long m,next;
  cin >> n >> k;
  int res = 0;
  m = 1;
  while ( m < n ){
	 next = m * k;
	 m += next;
	 res++;
  }
  cout << res << endl;
  return 0;
}