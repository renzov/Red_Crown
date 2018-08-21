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
const int MAXN = 5005;
char S[MAXN];
vector<int> pos[256];
set<string> W;
int K;

void add_strings( const char &c ){
	for ( int i=0; i < (int)pos[c].size(); ++i ){
		int j = pos[c][i];
		string s = "";
		for ( ; S[j] ; j++ ){
			s += S[j];
			W.insert(s);
		}
	}
}

void print_ans(){
	set<string>::iterator it = W.begin();
	while ( --K ) it++;
	printf("%s\n", it->c_str());
}

int main(){

	scanf("%s %d", S, &K);
	for ( int i=0; S[i]; ++i ) pos[ S[i] ].push_back(i);
	for ( char c='a'; c <= 'z'; ++c ){
		if ( !pos[c].empty() ){
			add_strings(c);
			if ( (int)W.size() >= K ){ 
				print_ans(); 
				break;
			}
		}
	}
	return 0;
}

