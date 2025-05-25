#include<cstdio>
#include<algorithm>
#include<list>
using namespace std;

char s[15];

int main(){
	int N, P;

	scanf("%d %d", &N, &P);
	P--;

	list<int> L;
	int a;

	for ( int i = 0; i < N; ++i ){
		scanf("%d", &a);
		L.push_back(a);
	}
	
	// pointer to the initial position
	list<int>::iterator act = L.begin();
	while ( P-- ) act++;

	// simulate the operations
	int Q, x;
	list<int>::iterator nxt;

	scanf("%d", &Q);
	while ( Q-- ){
		scanf("%s", s);
		if ( s[0] == 'p' ) printf("%d\n", *act);
		else if ( s[0] == 'm' ){	// move operation
			if ( s[4] == 'L' ){
				if ( act != L.begin() ) act--;
			}
			else {
				act++;
				if ( act == L.end() ) act--;
			}
		}
		else {	// insert operation
			scanf("%d", &x);
			if ( s[6] == 'L' ){
				L.insert( act, x );
			}
			else {
				nxt = act;
				nxt++;
				L.insert( nxt, x );
			}
		}
	}
	return 0;
}
