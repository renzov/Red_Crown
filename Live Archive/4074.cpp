#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
int n;
int idx[ 1<<13 ];
int d[ 650 ][ 650 ]; //Basado en precalcular n
struct triple{
  int a,b,w;
  triple(){}
  triple(int A,int B,int W){ a = A; b = B; w = W; }
};
void init(){
  int i,j,t;
  memset(idx,-1,sizeof(idx));
  idx[0] = 0;
  n = 1;
  for ( i=1; i < (1<<13); ++i ){
	 if ( idx[i] != -1 ) continue;
	 idx[ i ] = n;
	 t = i;
	 for ( j=0; j < 12; ++j ){
		if ( (t >> 12) & 1 ){
		  t ^= (1<<12);
		  t <<= 1;
		  t |= 1;
		}
		else {
		  t <<= 1;
		}
		if ( idx[t] == -1 ) idx[t] = n;
	 }
	 n++;
  }
}

void bfs(){
  int i,j;
  memset( d , -1 , sizeof(d) );
  d[ idx[8191] ][ idx[0] ] = 0;
  queue<triple> q;
  q.push( triple(8191,0,0) );
  int u,v,w;
  int t1,t2;
  int n1,n2;
  while ( !q.empty() ){
	 u = q.front().a; v = q.front().b;
	 w = q.front().w; q.pop();
	 t1 = u;
	 for ( i=0; i < 13; ++i ){
		t2 = v;
		for ( j=0; j < 13; ++j ){
		  n2 = t2; n1 = t1;
		  
		  if ( t1 & 1 ) n2 |= 1; else n2 &= 0X1FFE;
		  if ( (t1>>1) & 1 ) n2 |= (1<<1); else n2 &= 0X1FFD;
		  if ( (t1>>2) & 1 ) n2 |= (1<<2); else n2 &= 0X1FFB;
		  
		  if ( t2 & 1 ) n1 |= 1; else n1 &= 0X1FFE;
		  if ( (t2>>1) & 1 ) n1 |= (1<<1); else n1 &= 0X1FFD;
		  if ( (t2>>2) & 1 ) n1 |= (1<<2); else n1 &= 0X1FFB;
		  
		  if ( d[ idx[n1] ][ idx[n2] ] == -1 ){ d[ idx[n1] ][ idx[n2] ] = w+1; q.push( triple(n1,n2,w+1) ); }
		  
		  if ( (t2 >> 12) & 1 ){
			 t2 ^= (1<<12); t2<<=1; t2 |= 1;
		  }
		  else {
			 t2 <<= 1;
		  }
		}
		if ( (t1 >> 12) &1 ){
		  t1 ^= (1<<12); t1<<=1; t1 |= 1;
		}
		else {
		  t1 <<= 1;
		}
	 }
  }
}

int main(){
  init();
  bfs();
  char s[ 28 ];
  int a,b,i;
  while ( scanf("%s",s) != EOF ){
	 a = b = 0;
	 for ( i=0; i < 13; ++i ){
		if ( s[i] == 'g' ) a |= (1<<i);
		if ( s[13+i] == 'g' ) b |= (1<<i);
	 }
	 printf("%d\n",d[idx[a]][idx[b]]);
  }
  return 0;
}