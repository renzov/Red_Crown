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
#include <climits>

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

const int MAXN = 22;
const int MAXL = 35;

map<string,int> id;
int N,M;
int cnt;
char name[MAXN][MAXL];
vector<pii> matches;
int point[MAXN];

int low[MAXN];
int high[MAXN];
int ord[MAXN];

bool cmp( const int &a, const int &b ){
	return point[a] > point[b];
}

void backtrack( int idx ){
	if ( idx == cnt ){
		for ( int i=0; i < N; ++i ) ord[i] = i;
		sort( ord , ord + N , cmp );
		high[ ord[0] ] = min( high[ord[0]] , 1 );
		low[ ord[0] ] = max( low[ord[0]] , 1 );
		int last = 1;
		for ( int i=1; i < N; ++i ){
			if ( point[ ord[i] ] != point[ ord[i - 1] ] ){
				last = i + 1;
			}
			high[ ord[i] ] = min( high[ord[i]] , last );
			low[ ord[i] ] = max( low[ord[i]] , last );
		}
		return;
	}
	int id1 = matches[idx].first;
	int id2 = matches[idx].second;
	// Team 1 wins
	point[id1] += 3;
	backtrack( idx + 1 );
	point[id1] -= 3;
	// Team 2 wins
	point[id2] += 3;
	backtrack(idx + 1);
	point[id2] -= 3;
	// Draw
	point[id1]++, point[id2]++;
	backtrack(idx + 1);
	point[id1]--, point[id2]--;
}

void print( int pos ){
	printf("%d",pos);
	if ( pos == 1 ) printf("st");
	else if ( pos == 2 ) printf("nd");
	else if ( pos == 3 ) printf("rd");
	else printf("th");
}

int main(){
	char tmp[5];
	char t1[MAXL];
	char t2[MAXL];
	int id1,id2;
	int g1,g2;
	int cases = 0;

	while (scanf("%d %d",&N,&M) && N && M){
		cases++;
		id.clear();
		matches.clear();
		cnt = 0;

		if ( cases > 1 ) puts("");

		for ( int i=0; i < N; ++i ){
			point[i] = 0;
			high[i] = INT_MAX;
			low[i] = -1;
			scanf("%s",name[i]);
			id[ name[i] ] = i;
		}
		for ( int i=0; i < M; ++i ){
			scanf("%s %s %s",t1,tmp,t2);
			t2[strlen(t2) - 1] = '\0';
			id1 = id[t1]; id2 = id[t2];
			scanf("%d %d",&g1,&g2);
			if ( g1 == -1 || g2 == -1 ){
				cnt++;
				matches.push_back(make_pair(id1,id2));
			}
			else {
				if ( g1 > g2 ) point[id1] += 3;
				else if ( g2 > g1 ) point[id2] += 3;
				else point[id1]++, point[id2]++;
			}
		}
		backtrack(0);
		for ( int i=0; i < N; ++i ){
			printf("Team %s can finish as high as ",name[i]);
			print( high[i] );
			printf(" place and as low as ");
			print( low[i] );
			puts(" place.");
		}
	}
	return 0;
}
