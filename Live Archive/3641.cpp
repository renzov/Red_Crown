#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <numeric>

#define repn( i , a , b ) for( int i = ( int ) a ; i < ( int ) b ; i ++ )
#define rep( i , n ) repn( i , 0 , n ) 
#define all( x )  x.begin() , x.end()
#define rall( x ) x.rbegin() , x.rend()
#define mp make_pair
#define fst first
#define snd second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

bool vis[30];
int l[30];

int main(){
	char s[30];
	int p[30];
	int runs;
	int size, act;
	bool ok;

	scanf("%d",&runs);
	while ( runs-- ){
		scanf("%s",s);
		for ( int i=0; s[i] ; ++i ){
			p[i] = s[i]-'A';
			vis[i] = false;
			l[i] = 0;
		}
		l[26] = 0;
		for ( int i=0; i<26; ++i )
			if ( !vis[i] ){
				size = 0;
				act = i;
				while ( !vis[act] ){
					size++;
					vis[act] = true;
					act = p[act];
				}
				l[size]++;
			}
		ok = true;
		
		for ( int i=2; i <= 26; i += 2 )
			if ( l[i]&1 ) ok = false;

		if (ok) puts("Yes");
		else puts("No");
	}

	return 0;
}

