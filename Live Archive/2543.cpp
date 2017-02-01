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
int c;
int p[50];
int deg[50];
int n;
int rooms;
int odd;

inline void make_set( int x ){ p[x] = x; }
inline int find_set( int x ){
	return x != p[x] ? (p[x] = find_set(p[x])):x;
}
void link( int x,int y ){
	x = find_set(x);
	y = find_set(y);
	if ( x==y ) return;
	c--;
	p[y] = x;
}

void init(){
	for ( int i=0; i < n; ++i )
		make_set(i) , deg[i] = 0;
	odd = rooms = 0;
}

int main(){
	string line;
	int start;
	int end = 0;
	char s[50];
	int j;

	while (1){
		getline(cin,line);
		if ( line == "ENDOFINPUT" ) break;
		sscanf(line.c_str(),"%s %d %d",s,&start,&n);

		c = n;
		
		init();
		
		for ( int i=0; i < n; ++i ){
			getline(cin,line);
			stringstream in(line);
			while ( in >> j ){
				deg[i]++;
				deg[j]++;
				link(i,j);
				rooms++;
			}
		}

		getline(cin,line);	
		
		int zero = 0;

		for ( int i=0; i < n; ++i )
			if ( !deg[i] ) zero++;

		bool ok = true;
		
		if ( start == end && !rooms ) {
			printf("YES %d\n",rooms);
			continue;
		}

		if ( c != (1 + zero) ) ok = false;
		if ( start == end && !deg[start] && rooms ) ok = false;
		if (ok){
			for ( int i=0; i < n; ++i ){
				if ( deg[i] & 1 ){
					if ( i != start && i != end ){ 
						ok = false;
						break;
					}
					odd++;
				}
			}
			if (find_set(start) != find_set(end)) ok = false;
			else {
				if ( end == start && odd ) ok = false;
				if ( end != start && odd != 2 ) ok = false;
			}
		}
		if (ok) printf("YES %d\n",rooms);
		else puts("NO");
	}

	return 0;
}

