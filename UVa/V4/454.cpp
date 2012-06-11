#include<string>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n;
string w[105];
string cp[105];

bool cmp( const pair<int,int> &a, const pair<int,int> &b ){
	if ( w[a.first] != w[b.first] ) return w[a.first] < w[b.first];
	return w[a.second] < w[b.second];
}

string get_cp( int p ){
	string res = "";
	for ( int i=0; i < w[p].size(); ++i )
		if ( !isspace(w[p][i]) )
			res += w[p][i];
	sort( res.begin(),res.end() );
	return res;
}

int main(){
	int runs;
	bool eq;
	string line;
	cin >> runs;
	getline(cin,line);
	getline(cin,line);
	while ( runs-- ){
		n = 0;
		while ( getline(cin,line) ){
			if ( !line.size() ) break;
			w[n] = line;
			cp[n] = get_cp(n);
			n++;
		}
		vector< pair<int,int> > v;
		for ( int i=0; i < n; ++i )
			for ( int j=i+1; j < n; ++j ){
				if ( cp[i] == cp[j] ){
					if ( w[i] <= w[j] ) v.push_back( make_pair(i,j) );
					else v.push_back( make_pair(j,i) );
				}		
			}
		sort( v.begin() , v.end() , cmp );
		for ( int i=0; i < v.size(); ++i ){
			cout << w[ v[i].first ] << " = " << w[ v[i].second ] << endl;
		}
		if ( runs ) cout << endl;
	}
	return 0;
}
