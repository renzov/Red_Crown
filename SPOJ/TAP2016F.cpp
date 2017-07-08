#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

void process( char *s, int &type, int &cnt ){
	type = cnt = 0;
	char last = 'R';
	bool first = true;
	for ( int i=0; s[i]; ++i ){
		if ( s[i] == 'D' ){
			if ( first ){
				first = false;
			}
			last = s[i];
		}
		else if ( s[i] == 'R' ){
			if ( first ){
				type |= 1;
			}
			else if ( last == 'D' ){
				cnt++;
			}
			last = s[i];
		}
	}
	if ( !first && last == 'D' ){
		type |=  2;
	}
}

int main(){
	char name[128];
	int F;
	int type, cnt;
	int res, t;
	int T[4];
	while ( scanf("%d", &F) != EOF ){
		// Read the strings and get basic info 
		res = 0;
		T[0] = T[1] = T[2] = T[3] = 0;
		for ( int i=0; i < F; ++i ){
			scanf("%s", name);
			process(name, type, cnt );
			//printf("%s = %d - %d\n", name, type, cnt);
			res += cnt;
			T[type]++;
		}
		if ( T[3] > 0 ){
			if ( T[1] + T[2] > 0 ) res += T[3];
			else res += ( T[3] - 1 );
		}
		res += min( T[1], T[2] );
		printf("%d\n", res);
	}
	return 0;
}
