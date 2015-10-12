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

int main(){
	int runs;
	char name[50];
	int y1,y2,m1,m2,d1,d2,cour;

	scanf("%d",&runs);
	while (runs--){
		scanf("%s %d/%d/%d %d/%d/%d %d", name, &y1,&m1,&d1, &y2, &m2, &d2, &cour);
		if (y1 >= 2010 || y2 >= 1991){
			printf("%s eligible\n",name);
		}
		else if (cour >= 41){
			printf("%s ineligible\n",name);
		}
		else {
			printf("%s coach petitions\n",name);
		}
	}
	return 0;
}

