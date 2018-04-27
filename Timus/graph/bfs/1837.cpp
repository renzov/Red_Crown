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

const int MAXN = 500;

map<string,int> idx;
int d[MAXN];
vector<int> G[MAXN];
int n = 0;

inline int get_id(const string &s){
	return ( idx.count(s) )? idx[s]:( idx[s] = n++ );
}

int main(){
	string name;
	int N;
	int a, b, c;

	cin >> N;
	for ( int i=0; i < N; ++i ){
		cin >> name;
		a = get_id(name);
		cin >> name;
		b = get_id(name);
		cin >> name;
		c = get_id(name);
		G[a].push_back(b), G[b].push_back(a);
		G[a].push_back(c), G[c].push_back(a);
		G[b].push_back(c), G[c].push_back(b);
	}
	
	fill( d, d + n, -1 );
	queue<int> q;
	
	if ( idx.count("Isenbaev") ){
		int s = get_id("Isenbaev");
		d[s] = 0;
		q.push(s);

		while ( !q.empty() ){
			a = q.front();
			q.pop();
			for ( int i=0; i < (int)G[a].size(); ++i ){
				b = G[a][i];
				if ( d[b] == -1 ){
					d[b] = d[a] + 1;
					q.push(b);
				}
			}
		}
	}

	for ( map<string,int>::iterator it=idx.begin(); it != idx.end(); ++it ){
		cout << it->first << ' ';
		if ( d[it->second] == -1 ) cout << "undefined" << endl;
		else cout << d[it->second] << endl;
	}
	return 0;
}

