#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<cctype>
#include<algorithm>
using namespace std;
#define forn(i,n) for(int i=0; i < (int)(n); ++i )
const int MAX = 100005;

char s[ MAX ];
char p[ MAX ];
int fp[ 28 ] = {0};
int fs[ 28 ] = {0};
int main(){
  int n,m;
  scanf("%s",s);
  scanf("%s",p);
  n = strlen( s ); m = strlen(p);
  if ( m > n ){ cout << 0 << endl; return 0; }
  forn(i,m){ 
	 fp[p[i]-'a']++; 
	 if ( isalpha( s[i] ) ){
		fs[ s[i]-'a' ]++;
	 }
	 else {
		fs[ 26 ]++;
	 }
  }
  int i = 0;
  int res = 0;
  bool ok;
  int gap;
  while ( (i+m) <= n ){
	 gap = 0;
	 ok = true;
	 forn(j,26){
		if ( fs[j] > fp[j] ) ok = false;
		else gap += abs( fs[j] - fp[j] );
	 }
	 if ( ok && gap == fs[26] ){
		res++;
		//cout << i << endl;
	 }
	 //update
	 if ( isalpha( s[i] ) ){
		fs[ s[i]-'a' ]--;
	 }
	 else {
		fs[ 26 ]--;
	 }
	 if ( (i + m) < n ){
		if ( isalpha( s[i+m] ) ){
		  fs[ s[i+m]-'a' ]++;
		}
		else {
		  fs[ 26 ]++;
		}
	 }
	 i++;
  }
  cout << res << endl;
  return 0;
}