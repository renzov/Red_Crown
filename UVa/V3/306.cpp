#include<cstdio>
#include<cstring>
int a[505];
char men[505];
int n;

void f( int *p, int k ){
	if ( k == 0 ){
		for ( int i=0; i < n; ++i ) p[i] = i;
		return;
	}
	if ( k == 1 ){
		for ( int i=0; i < n ; ++i ){
			p[ i ] = a[i];
		}
		return;
	}
	int tmp[n];
	if ( k & 1 ){
		f( tmp , k - 1 );
		for ( int i=0; i < n; ++i ){
			p[ i ] = a[ tmp[i] ];
		}
	}
	else {
		f( tmp , k >> 1 );
		for ( int i=0; i < n; ++i ){
			p[ i ] =  tmp[ tmp[i] ]; 
		}
	}
}

int main(){
	int k;
	int res[505];
	char s[505];
	while ( scanf("%d",&n) && n ){
		for (int i=0; i < n; ++i){
			scanf("%d",a+i); a[i]--;
		}
		while ( scanf("%d",&k) && k ){
			getchar(); // Reading separator
			for ( int i=0;  ; i++){
				men[i] = getchar();
				if ( men[i] == '\n' ){
					men[i] = '\0'; break;
				}
			}
			for ( int i=strlen(men); i < n ; ++i ) men[i] = ' ';
			men[n] = '\0';
			f( res , k );
			for ( int i=0; i < n; ++i )
				s[ res[i] ] = men[ i ];
			s[n] = '\0';
			puts(s);
		}
		puts("");
	}
	return 0;
}

