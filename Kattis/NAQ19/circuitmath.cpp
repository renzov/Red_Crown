#include<stack>
#include<cstdio>
#include<cctype>
using namespace std;

bool V[32];
int N;
stack<bool> S;

int main(){
	char c;
	bool u, v;
	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf(" %c", &c);
		if ( c == 'T' ) V[i] = true;
	}
	while ( scanf(" %c", &c) == 1 ){
		if ( isalpha(c) ){
			S.push( V[ c - 'A'] );
		}
		else {
			switch (c){
				case '+': 
						u = S.top(); S.pop();
						v = S.top(); S.pop();
						S.push( u or v );
						break;
				case '-': 
						u = S.top(); S.pop();
						S.push( not u );
						break;
				case '*':
						u = S.top(); S.pop();
						v = S.top(); S.pop();
						S.push( u and v );
						break;
			} 
		}
	}
	if ( S.top() ) puts("T");
	else puts("F");
	return 0;
}
