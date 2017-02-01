#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<climits>

const int INF = 1500;

char M[11][15];
bool attack[11][11];
int I[11][11];
int mask[11][11];
int dp[(1<<16) + 5];
bool in[(1<<16) + 5];
int q[(1<<16) + 5];
int dx[]={0,1,1,0,-1,-1,-1,0,1};
int dy[]={0,0,-1,-1,-1,0,1,1,1};

void put_value(int y,int x,bool v){
  int ny,nx;
  for ( int i=0; i < 9; ++i){
	 ny = y + dy[i]; nx = x + dx[i];
	 if ( ny < 0 || ny >= 10 || nx < 0 || nx >= 10 ) continue;
	 attack[ny][nx] = v;
  }
}

int get_mask( int y ,int x ){
  int res = 0;
  int nx,ny;
  for ( int i=0; i < 9; ++i){
	 ny = y + dy[i]; nx = x + dx[i];
	 if ( ny < 0 || ny >= 10 || nx < 0 || nx >= 10 ) continue;
	 if ( M[ny][nx] == 'e' )
		res |= (1<<I[ny][nx]);
  }
  return res;
}

inline int min(int x,int y){ return x<=y? x:y; }
inline int apply( int x , int y ){ return x & ~y; }

int bitcount (int n)  {
   int count = 0 ;
   while (n)  {
      count++ ;
      n &= (n - 1) ;
   }
   return count;
}


int main(){
  int n;
  int m;
  int next;
  int x;
  int runs;
  
  scanf("%d",&runs);
  while ( runs-- ){
	 
	 for ( int i=0; i < 10; ++i )
		 for ( int j=0; j < 10; ++j ){
			 I[i][j] = -1;
			 attack[i][j] = false;
		 }
	 n = 0;
	 for ( int i=0; i < 10; ++i ){
		scanf("%s",M[i]);
		for ( int j=0; j < 10; ++j )
		  if ( M[i][j] == 'e' ){
			 I[i][j] = n;
			 put_value(i,j,true);
			 n++;
		  }
	 }

	 for ( int i=0; i < 10; ++i )
		for ( int j=0; j < 10; ++j )
		  if ( M[i][j] == 'g' )
			 put_value(i,j,false);
			 
		  
	 for ( int i=0; i < 10; ++i)
		for ( int j=0; j < 10; ++j )
		  if ( attack[i][j] )
			 mask[i][j] = get_mask(i,j);
	 
	 dp[0] = 0;
	 
	 for ( int i=1; i < (1<<n); ++i ) dp[i] = INF;
	 
	 for ( int i=0; i < 10; ++i )
		for ( int j=0; j < 10; ++j ){
		  if ( attack[i][j] ){
			 for ( int k=(1<<n)-1; k >= 1; --k ){
				dp[k] = min( dp[k] , dp[ k & (~mask[i][j]) ] + 1 );
			 }
		  }
		}
	 int most = 0;
	 int t;
	 int best = 0;
	 for ( int i=1; i < (1<<n); ++i ){
		 t = bitcount( i );
		 if ( t >= most && dp[i] < INF ){
			 if ( t > most ){ most = t; best = dp[i]; }
			 else if ( best > dp[i] ) best = dp[i];
		 }
	 }
	 printf("%d %d\n",most,best);
  }
  return 0;
}