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

int val[300];

void print_roman(int n){
	if ( n >= 1000 ){
		for (int i=0; i < n/1000; ++i) putchar('M'); 
		n %= 1000;
	}
	if (n >= 900){
		putchar('C'); putchar('M'); n -= 900;
	}
	if (n >= 500){
		putchar('D'); n -= 500;
	}
	if (n >= 400){
		putchar('C'); putchar('D'); n -= 400;
	}
	if (n >= 100){
		for (int i=0; i < n / 100; ++i) putchar('C');
		n %= 100;
	}
	if (n >= 90){
		putchar('X'); putchar('C'); n -= 90;
	}
	if (n >= 50){
		putchar('L'); n -= 50;
	}
	if (n >= 40){
		putchar('X'); putchar('L'); n -= 40;
	}
	if (n >= 10){
		for (int i=0; i < n/10; ++i) putchar('X');
		n %= 10;
	}
	if (n >= 9){
		putchar('I'); putchar('X'); n-= 9;
	}
	if ( n >= 5 ){
		putchar('V'); n-= 5;
	}
	if (n >= 4){
		putchar('I'); putchar('V'); n-= 4;
	}
	for ( int i=0; i < n; ++i ) putchar('I');
	putchar('\n');
}

int number( char *s ){
	int n = 0;
	for ( int i=0; s[i] ; ++i ){
		if (val[s[i]] < val[s[i+1]] )
			n -= val[s[i]];
		else 
			n += val[s[i]];
	}
	return n;
}

int main(){
	char s[10];
	int n;
	val['\0'] = 0;
	val['M'] = 1000;
	val['D'] = 500;
	val['C'] = 100;
	val['L'] = 50;
	val['X'] = 10;
	val['V'] = 5;
	val['I'] = 1;
	
	while ( scanf("%s",&s) != EOF ){
		if (isdigit(s[0])){
			sscanf(s,"%d",&n);
			print_roman(n);
		}
		else {
			printf("%d\n",number(s));
		}
	}
	return 0;
}

