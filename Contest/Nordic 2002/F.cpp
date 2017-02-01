#include<cstdio>
const int MAX = 1<<15;
int m;
bool nsp[1<<15 + 5];
int p[1<<15];

void sieve(){
	nsp[0] = nsp[1] = true;
	p[0] = 2;
	m = 1;
	int i,j;
	for ( j=4; j < MAX ; j+= 2 ) nsp[j] = true;
	for ( i = 3; i < MAX ; i += 2 ){
		if ( !nsp[i] ){
			p[m++] = i;
			for ( j = i*i ; j < MAX ; j += i )
				nsp[j] = true;
		}
	}
}

int main(){
	sieve();
	int n;
	int res,i;
	while ( scanf("%d",&n) == 1 && n ){
		res = 0;
		for ( i = 0; p[i] <= (n>>1) ; ++i )
			if ( !nsp[ n - p[i] ] ) res++;
		printf("%d\n",res); 
	}
	return 0;
}

