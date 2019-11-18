#include<iostream>
#include<string>
#include<cctype>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 1028;
typedef pair<int,int> pii;

string S[MAXN];
string line;

bool cmp( const string &A, const string &B ){
	return A.length() < B.length();
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
	int N, M;
	bool ok;
	while ( cin >> N >> M &&  ( N || M ) ){
		for ( int i=0; i < N; ++i )
			cin >> S[i];

		getline(cin, line);	
		sort( S, S + N, cmp );
		
		int res = 0;
		for ( int i=0; i < M; ++i ){
			getline(cin, line);
			vector<pii> intervals;
			for ( int j=0; j < line.length(); ++j ){
				if ( isspace( line[j] ) ) continue;
				for ( int k=0; k < N; ++k ){
					if ( (S[k].length() + j) > line.length() ) continue;
					ok = true;
					for ( int l=0; ok && l < S[k].length(); ++l ){
						ok = S[k][l] == line[j + l];
					}
					if ( ok ) intervals.push_back( pii( j + S[k].length() - 1, j ) );
				}
			}
			sort( intervals.begin(), intervals.end() );
			int last = -1;
			for ( int j=0; j < (int)intervals.size(); ++j ){
				if ( last < intervals[j].second ) res++, last = intervals[j].first;
			}
		}
		cout << res << '\n';
	}
	return 0;
}
