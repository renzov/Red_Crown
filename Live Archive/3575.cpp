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
const int SPADES = 0;
const int HEARTS = 1;
const int DIAMONDS = 2;
const int CLUBS = 3;
const int NO_TRUMP = 4;

int hcp;
int size[4];
int d[4];
int card[ 4 ][ 15 ];


int balance[3][4] = { {3,3,3,4} , {2,3,4,4} , {2,3,3,5} };
char suit[][15] = { "Spades" , "Hearts" , "Diamonds" , "Clubs" , "No Trump" };

void init(){
	memset( card , 0 , sizeof(card) );
	memset( size , 0 , sizeof(size) );
	hcp = 0;
}

void add( pii c ){
	if ( c.second >= 11 ) hcp += (c.second - 10); 
	size[ c.first ]++;
	card[ c.first ][ c.second ]++;
}

pii get_card( char *s ){
	pii res;
	switch ( s[0] ){
		case 'S' : res.first = 0; break;
		case 'H' : res.first = 1; break;
		case 'D' : res.first = 2; break;
		case 'C' : res.first = 3; break;
	}
	if ( isdigit( s[1] ) ){
		res.second = s[1] - '0';
	}
	else {
		switch ( s[1] ){
			case 'T' : res.second = 10; break;
			case 'J' : res.second = 11; break;
			case 'Q' : res.second = 12; break;
			case 'K' : res.second = 13; break;
			case 'A' : res.second = 14; break;
		}
	}
	return res;
}

bool isBalanced(){
	bool ok;
	for ( int i=0; i < 3; i++ ){
		ok = true;
		for ( int j=0; j < 4 && ok ; j++ ){
			ok &= ( d[j] == balance[i][j] );
		}
		if ( ok ) return true;
	}
	return false;
}

bool isStopped( int suit ){
	if ( card[suit][14] > 0 ) return true;
	if ( card[suit][13] > 0 && size[suit] > 1 ) return true;
	if ( card[suit][12] > 0 && size[suit] > 2 ) return true;
	if ( card[suit][11] > 0 && size[suit] > 3 ) return true;
	return false;
}

pii solve(){
	//Test condition 1
	if ( hcp >= 10 && d[3] >= 8 ){
		for ( int i=0; i < 4; ++i ){
			if ( size[i] == d[3] ){ return make_pair( 4 , i ); }
		}
	}
	//Test condition 2
	if ( hcp >= 10 && hcp <= 13	&& d[3] == 7 ){
		for ( int i=0; i < 4; ++i ){
			if ( size[i] == d[3] ){ return make_pair( 3 , i ); }
		}
	}
	//Test condition 3
	if ( hcp >= 8 && hcp <= 9 && d[3] >= 7 ){
		for ( int i=0; i < 4; ++i ){
			if ( size[i] == d[3] && i <= 1 ){ return make_pair( 2  , i ); }
		}
	}
	//Test condition 4
	if ( hcp >= 8 && hcp <= 11 && d[3] == 6 && (size[SPADES] == 6 || size[HEARTS] == 6 ) ){
		if ( size[SPADES] == 6 ) return make_pair( 2 , SPADES );
		return make_pair( 2 , HEARTS );
	}
	//Test condition 5
	if ( hcp >= 11 && hcp <= 15 && d[1] >= 4 && size[SPADES] >= 4 ){
		return make_pair( 2 , DIAMONDS );
	}
	//Test condition 6
	if ( hcp >= 15 && hcp <= 17 && isBalanced() ){
		int cnt = 0;
		for ( int i=0; i < 4; ++i )
			if ( isStopped( i ) ) cnt++;
		if ( cnt >= 3 ) return make_pair( 1 , NO_TRUMP );
	}
	//Test condition 7
	if ( hcp >= 20 && hcp <= 22 && isBalanced() ){
		return make_pair( 2 , NO_TRUMP );
	}
	//Test condition 8
	if ( hcp >= 22 ){
		return make_pair( 2 , CLUBS );
	}
	//Test condition 9
	if ( hcp >= 13 && hcp <= 16 ){
		if ( size[SPADES] >= 5 || size[HEARTS] >= 5 ){
			if ( size[HEARTS] > size[SPADES] ) return make_pair( 1 , HEARTS );
			if ( size[HEARTS] < size[SPADES] ) return make_pair( 1 , SPADES );
			//Both have equal size
			return make_pair( 1 , SPADES ); //Assuming SPADES is the higher ranking suit
		}
		else {
			if ( size[DIAMONDS] > size[CLUBS] ) return make_pair( 1 , DIAMONDS );
			if ( size[DIAMONDS] < size[CLUBS] ) return make_pair( 1 , CLUBS );
			//Equal size
			return make_pair( 1 , DIAMONDS );
		}
	}
	//Test condition 10
	if ( hcp >= 17 ){
		int best = 0;
		for ( int i=1; i < 4; ++i ){
			if ( size[i] >= size[best] )
				best = i;
		}
		return make_pair( 1 , best );
	}
	//Rule 11
	return make_pair( -1 , -1 );
}

int main(){

	int runs = 0;
	char s[5];

	while ( scanf("%s",s) != EOF ){
		runs++;
		init();
		add( get_card(s) );
		for ( int i=1; i < 13; ++i ){
			scanf("%s",s);
			add( get_card(s) );	
		}
		for ( int i=0; i < 4; ++i ) d[i] = size[i];
		sort( d , d + 4 );
		printf("Hand #%d: ",runs);
		pii res = solve();
		if ( res.first < 0 ){
			puts("Pass");
		}
		else {
			printf("%d %s\n",res.first , suit[ res.second ]);
		}
	}
	return 0;
}

