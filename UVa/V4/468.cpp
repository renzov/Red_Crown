#include<string>
#include<iostream>
#include<algorithm>
#include<map>
#include<sstream>
#include<vector>
using namespace std;

bool cmp( const pair<char,int> &a, const pair<char,int> &b ){
	return a.second > b.second;
}

char f[256];

int main(){
	string r1;
	int runs;
	cin >> runs;
	string line;
	string s;
	getline(cin,line); getline(cin,line);
	while (runs--){
		getline(cin,line);
		stringstream in(line);
		map<char,int> f1;
		while ( in >> s ){
			for ( int i=0; i < s.size(); ++i )
				if ( isalpha(s[i]) )
					f1[ s[i] ]++;
		}
		getline(cin,line);
		r1 = line; // Saving for the result
		stringstream in2(line);
		map<char,int> f2;
		while ( in2 >> s ){
			for ( int i=0; i < s.size(); ++i ){
				if ( isalpha( s[i] ) )
					f2[ s[i] ]++;
			}
		}
		vector< pair<char,int> > v1( f1.begin() , f1.end() );
		vector< pair<char,int> > v2( f2.begin() , f2.end() );
		sort( v1.begin() , v1.end() , cmp );
		sort( v2.begin() , v2.end() , cmp );
		for ( int i=0; i < v2.size(); ++i ){
			if ( i >= v1.size() ) while (1); // Error
			f[ v2[i].first ] = v1[i].first;
		}
		for ( int i=0; i < r1.size(); ++i ){
			if ( isalpha( r1[i] ) )
				r1[i] = f[ r1[i] ];
		}
		cout << r1 << endl;
		if (runs){
			getline(cin,line); // Read Blanck line
			cout << endl;
		}
	}
	return 0;
}
