#include<cstdio>

bool lucky(int x){
	while ( x ){
		if ( ((x % 10) != 4) && ((x % 10) != 7) )
			return false;
		x /= 10;
	}
	return true;
}

int main(){
	int N;
	bool found = false;
	scanf("%d", &N);

	for ( int i=4; i <= N && !found; ++i )
		if ( lucky(i) && N % i == 0 )
			found = true;
	
	puts(found? "YES":"NO");
	return 0;
}
