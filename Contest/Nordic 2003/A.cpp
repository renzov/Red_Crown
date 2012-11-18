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
#include <cstdlib>

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

int f[100000][10] = {0};

void precalc(){
	int i,t;
	for ( i = 0; i < 10; ++i ) f[i][i] = 1;
	for ( i = 10; i < 100000; ++i ){
		t = i;
		while ( t ){
			f[i][t%10]++;
			t /= 10;
		}
	}
}

inline void add( int *R, int *F ){
	R[0] += F[0], R[1] += F[1], R[2] += F[2], R[3] += F[3], R[4] += F[4],
	R[5] += F[5], R[6] += F[6], R[7] += F[7], R[8] += F[8], R[9] += F[9]; 
}

int main(){
	char s[5000];
	char name[1000];
	char num[1000];
	int runs;
	int tmp;
	int x,y,z;

	precalc();

	scanf("%d",&runs); gets(s);
	while ( runs-- ){
		gets(name);
		gets(num);
		sscanf(num,"%d",&tmp);
		int res[10] = {0};
		while ( tmp ){
			gets(s);
			if ( s[0] == '+' ){
				sscanf(s,"+ %d %d %d",&x,&y,&z);
				for ( int i=x; i <= y; i += z ){
					add(res,f[i]);
					tmp--;
				}
			}
			else {
				sscanf(s,"%d",&x);
				add(res,f[x]);
				tmp--;
			}
		}
		puts(name);
		puts(num);
		int total = 0;
		for ( int i=0; i < 10; ++i ){
			printf("Make %d digit %d\n",res[i],i);
			total += res[i];
		}
		if ( total > 1 )
			printf("In total %d digits\n",total);
		else 
			printf("In total 1 digit\n");
	}
	return 0;
}

