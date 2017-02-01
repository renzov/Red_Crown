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

const char FUEL = 0;
const char LEAK = 1;
const char MECH = 2;
const char GAS = 3;
const char GOAL = 4;

struct event{
	char type;
	int pos;
	int val;
	event(){}
	event( int P, char T, int V ){ pos = P, type = T, val = V; }
};

int n;
event E[ 100 ];

void read_event(event &e){
	char word[50];
	scanf("%d",&e.pos);
	scanf("%s",word);
	if ( word[0] == 'F' ){
		scanf("%s",word);
		scanf("%d",&e.val);
		e.type = FUEL;
	}
	else if (word[0] == 'L'){
		e.type = LEAK;
	}
	else if (word[0] == 'M'){
		e.type = MECH;
	}
	else if ( word[1] == 'a' ){
		e.type = GAS;
		scanf("%s",word);
	}
	else {
		e.type = GOAL;
	}
}

bool possible( double maxcap ){
	double coms = E[0].val / 100.0;
	int leaks = 0;
	int pos = 0;
	double tank = maxcap;
	int d;
	for ( int i=1; i < n; ++i ){
		d = E[i].pos - pos;
		if ( d > 0 ){
			tank -= ( leaks + coms ) * d;
		}
		if (tank < 0 && fabs(tank) > 0.0001) return false;
		switch (E[i].type){
			case FUEL : coms = E[i].val / 100.0;  break;
			case LEAK : leaks++; break;
			case MECH : leaks = 0; break;
			case GAS : tank = maxcap; break;
		}
		pos = E[i].pos;
	}
	return true;
}

int main(){
	event e;
	while ( 1 ){
		read_event(e);
		if (e.val == 0) break;
		n = 0;
		E[n++] = e;
		while (1){
			read_event(e);
			E[n++] = e;
			if ( e.type == GOAL ) break;
		}
		double l = 0.0;
		double r = E[n-1].pos * 10000.0;
		double m;
		while ( (r - l) > 0.0001 ){
			m = ( l + r ) / 2.0;
			if ( possible(m) ) r = m;
			else l = m;
		}
		printf("%0.3lf\n",r);
	}
	return 0;
}

