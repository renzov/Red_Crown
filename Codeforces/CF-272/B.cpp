#include<cstdio>

char A[16];
char B[16];

int main(){
	int p=0, n=0, q=0;

	scanf("%s %s", A, B);
		
	for (int i=0; A[i]; ++i )
		if (A[i] == '+') p++;
		else n++;

	for ( int i=0; B[i]; i++ )
		if ( B[i] == '+' )
			p--;
		else if ( B[i] == '-' )
			n--;
		else 
			q++;		
	
	if ( n < 0 || p < 0 ) puts("0");
	else if ( q == 0 ){
		puts((n || p)? "0":"1");
	}
	else {
		int total = (1 << q);
		int cnt = 0;
		for ( int i=0; i < total; i++ ){
			int zero = 0, one = 0;
			for ( int j=0; j < q; ++j ){
				if ( (i >> j) & 1 ) one++;
				else zero++;
			}
			if ( one == p && zero == n ) cnt++;
		} 
		printf("%.9f\n", (double)cnt/total);
	}
	return 0;
}
