#include<cstdio>
#include<deque>
using namespace std;
const int MAXN = 200005;
char word[MAXN];

int main(){
	scanf("%s", word);
	deque<char> S;
	for ( int i=0; word[i]; ++i ){
		if ( !S.empty() && word[i] == S.back() ){
			S.pop_back();
			continue;
		}
		S.push_back( word[i] );
	}
	while ( !S.empty() ){
		putchar( S.front() );
		S.pop_front();
	}
	puts("");
	return 0;
}
