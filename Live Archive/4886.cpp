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
	char line[2000];
	char *token;
	int n,low,high;
	int last,res;
	vector< pii > I;
	while ( scanf("%d",&n) && n > 0 ){
		I.clear();
		while (getchar() != '\n');
		gets(line);
		token = strtok(line, ",");
   		while( token != NULL ){
      		if ( strchr(token,'-') != NULL ){
				sscanf(token,"%d-%d",&low,&high);
			}
			else {
				sscanf(token,"%d",&low);
				high = low;
			}
			if ( low <= high && low <= n ){
				low = max( 1 , low );
				high = min( n , high );
				I.push_back( make_pair(low,high) );
			}
    		token = strtok(NULL, ",");
   		}
		sort( all(I) );
		last = 0;
		res = 0;
		for ( int i=0; i < I.size(); ++i ){
			//printf("%d %d -> ",I[i].first,I[i].second);
			if ( I[i].first <= last ){
				if ( I[i].second > last ){
					res += I[i].second - last;
					last = I[i].second;
				}
			}
			else {
				res += I[i].second - I[i].first + 1;
				last = I[i].second;
			}
			//printf("%d\n",res);
		}
		printf("%d\n",res);
	}
	return 0;
}

