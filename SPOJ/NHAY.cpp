#include<cstdio>

int M;
char *B;
int *p;

void prefix_function(){
	p = new int[M + 1];
	p[0] = 0;
	for ( int i = 1; i <= M; ++i ){
		int j = p[i - 1];
		while ( j > 0 && B[j] != B[i] )
			j = p[ j - 1 ];
		if ( B[i] == B[j] )
			j++;
		p[i] = j;
	}
}

int main(){
	int runs = 0;
	while ( scanf("%d", &M) == 1 ){
		if ( runs++ ) puts("");

		B = new char[M + 1];
		scanf("%s", B);
		getchar(); // reads EOLN
		prefix_function();
		// find the occurences
		int cnt = 0;
		int i = 0;
		int j;
		char c;
		while ( ( c = getchar() ) != '\n' ){
			j = cnt;
			while ( j > 0 && c != B[j] )
				j = p[j - 1];
			if ( c == B[j] )
				j++;
			cnt = j;
			if ( cnt == M )
				printf("%d\n", i - M + 1);
			i++;
		}
		// free memory
		delete[] B;
		delete[] p;
	}

	return 0;
}
