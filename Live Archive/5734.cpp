#include<cstdio>
#include<algorithm>
#include<climits>
using namespace std;
const int MAXN = 300002;

char s[ MAXN ];
char st[ MAXN * 2 ];
int n,t;
int p[MAXN * 2 ],r[MAXN * 2],h[MAXN * 2];

bool comp(int i, int j) {
   return p[i + t] < p[j + t];
}

void fix_index(int *b, int *e) {
  int pkm1, pk, np, i, d, m;
  pkm1 = p[*b + t];
  m = e - b; d = 0;
  np = b - r;
  for(i = 0; i < m; i++) {
	 if (((pk = p[*b+t]) != pkm1) && !(np <= pkm1 && pk < np+m)) {
		pkm1 = pk;
		d = i;
	 }
	 p[*(b++)] = np + d;
  }
}


void suffix_array() {
  int i, j, bc[256];
  t = 1;
  for(i = 0; i < 256; i++) bc[i] = 0;
  for(i = 0; i < n; i++) ++bc[int(st[i])];
  for(i = 1; i < 256; i++) bc[i] += bc[i - 1];
  for(i = 0; i < n; i++) r[--bc[int(st[i])]] = i;
  for(i = n - 1; i >= 0; i--) p[i] = bc[int(st[i])];
  for(t = 1; t < n; t *= 2) {
	 for(i = 0, j = 1; i < n; i = j++) {
		while(j < n && p[r[j]] == p[r[i]]) ++j;
		  if (j - i > 1) {
			 sort(r + i, r + j, comp);
			 fix_index(r + i, r + j);
		  }
	 }
  }
}

int main(){
  int i;
  int m;
  int best;
  while ( scanf("%s",s) != EOF ){
	 for (i=0; s[i+1]; ++i){
		st[i] = ( s[i] <= s[i+1] )? (s[i+1]-s[i]) : (8  + s[i+1] - s[i]);
	 }
	 st[i] = ( s[i] <= s[0] )? (s[0]-s[i]) : (8 + s[0] - s[i]);
	 /* concat */
	 n = i + 1;
	 m = n;
	 for ( i = n; i < (n<<1) ; ++i ) st[ i ] = st[ i-n ];
	 n<<=1;
	 st[n++] = '$' ;
	 suffix_array();
	 for ( i = 0 ;  ; ++i ){
		 if ( r[i] < m ){
			best = r[i];
			break;
		}
	 }
	 for (i=0; i < m; ++i)
		putchar('0' + st[best+i]);
	 putchar('\n');
  }
  return 0;
}