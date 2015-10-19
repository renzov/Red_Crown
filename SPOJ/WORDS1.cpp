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

const int MAXC = 27;

int out[MAXC];
int in[MAXC];
int comp;
int p[MAXC];

int find(int x){ return (p[x] == x)? x:( p[x] = find(p[x]) ); }
void link(int u, int v){
	if (u==v) return;
	comp--;
	p[u] = v;
}

int main(){
	int runs;
	char word[1005];
	int u,v;
	int N;

	scanf("%d",&runs);

	while (runs--){
		scanf("%d",&N);
		for ( int i=0; i < 26; ++i ){
			in[i] = out[i] = 0;
			p[i] = i;
		}
		
		comp = 26;

		for ( int i=0; i<N; ++i ){
			scanf("%s",word);
			u = word[0] - 'a';
			v = word[strlen(word) - 1] - 'a';
			in[v]++, out[u]++;
			link( find(u) , find(v) );
		}

		bool ok = true;
		int I=0, O=0;
		int zero = 0;

		for ( int i=0; i<26 && ok; ++i ){
			if ( in[i] > out[i] ){
				if ((in[i] - out[i]) > 1) ok = false;
				else I++; 
			}
			else if (out[i] > in[i]){
				if ( (out[i] - in[i]) > 1 ) ok = false;
				else O++;
			}
			else if (in[i] == 0) zero++;
		}

		if (I > 1 || O > 1) ok = false;

		if (!ok) puts("The door cannot be opened.");
		else if ((comp-zero) != 1) puts("The door cannot be opened.");
		else puts("Ordering is possible.");
	}
	return 0;
}

