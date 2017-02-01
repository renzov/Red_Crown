#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

bool nsp[32005] = {0};
int p[32000];  
int P = 0;
int n = 0;
int v[ 200 ];
vector<int> t[200];

void sieve(){
  int i,j;
  p[P++] = 2;
  for ( i=4; i <= 32000; i+=2 ) nsp[i] = true;
  for ( i=3; i <= 32000; i+=2 ){
	 if ( !nsp[i] ){
		p[P++] = i;
		for ( j=2*i; j<=32000 ; j+=i ) nsp[j] = true;
		if ( P >= 3 && (p[P-1] - p[P-2]) == (p[P-2] - p[P-3]) ){
		  if ( n == 0 ){
			 v[n] = p[P-3];
			 t[n].push_back( p[ P-3 ] ); t[n].push_back( p[ P-2 ] ); t[n].push_back( p[ P-1 ] );
			 n++;
		  }
		  else {
			 if ( t[n-1].back() == p[ P-2 ] ){
				t[n-1].push_back( p[P-1] );
			 }
			 else {
				v[n] = p[P-3];
				t[n].push_back( p[ P-3 ] ); t[n].push_back( p[ P-2 ] ); t[n].push_back( p[ P-1 ] );
				n++;
			 }
		  }
		}
	 }
  }
}

int main(){
  sieve();
  int a,b;
  int idx;
  while ( scanf("%d %d",&a,&b) && ( a || b ) ){
	 if ( a > b ) swap(a,b);
	 idx = lower_bound( v , v + n , a ) - v;
	 if ( idx < n ){
		while ( idx < n && t[idx].back() <= b ){
		  for ( int i=0; i < t[idx].size(); ++i ){
			 if ( i ) putchar(' ');
			 printf("%d",t[idx][i]);
		  }
		  putchar('\n');
		  idx++;
		}
	 }
	 else putchar('\n');
  }
  return 0;
}