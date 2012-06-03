#include<cstdio>

inline long long max(long long a,long long b){
  return (a>=b)? a : b;
}

struct resp{
  long long r,l,s;
  resp(){}
  resp(long long x,long long y,long long z){ l = x; r = y; s = z; }
};

const int MAX = 50000;
const int INF = MAX * 10;
long long sum[ 4 * MAX ];
long long left[ 4 * MAX ];
long long right[ 4 * MAX ];
bool elim[MAX + 2] = {0};
int st[MAX+2];

void build_tree(int n,int l,int r){
  right[n] = left[n] = sum[n] = r - l + 1;
  if (l==r) return;
  int m = (l+r) >> 1;
  build_tree(n<<1,l,m); build_tree((n<<1) + 1,m+1,r);
}

void update(int n,int l,int r,int p,int v){
  if (l==r){
	 right[n] = left[n] = sum[n] = v;
	 return;
  }
  int m = (l+r)>>1;
  if (p<=m) update( n<<1 , l , m, p , v );
  else update( (n<<1) + 1 , m+1, r , p , v);
  sum[n] = sum[n<<1] + sum[(n<<1) + 1];
  left[n] = max( left[ n<<1 ] , sum[n<<1] + left[ (n<<1) + 1 ] );
  right[n] = max( right[ (n<<1) + 1] , sum[(n<<1) + 1] + right[n<<1] );
}

resp query(int n,int L,int R,int l,int r){
  if (L==l && r==R) return resp( left[n] , right[n] , sum[n] );
  int M = (L + R) >> 1;
  if (r <= M) return query( n<<1 , L , M , l , r );
  if (M < l) return query( (n<<1) + 1 , M + 1 , R , l , r );
  resp a = query(  n<<1 , L , M , l , M );
  resp b = query( (n<<1) + 1 , M + 1, R , M + 1, r );
  resp c;
  c.l = max( a.l , a.s + b.l );
  c.r = max( b.r , b.s + a.r );
  c.s = a.s + b.s;
  return c;
}

int main(){
  int n,m,p;
  char c;
  int last;
  resp a,b;
  int sp = 0;
  scanf("%d %d",&n,&m);
  build_tree(1,1,n);
  for (int i=0; i < m; ++i){
	 scanf(" %c",&c);
	 if ( c == 'R' ){
		 if (sp > 0){
		   last = st[--sp]; 
		   update( 1 , 1 , n, last , 1 );
			elim[last] = false;
		 }
	 }
	 else if (c == 'Q'){
		  scanf("%d",&p);
		  if (elim[p]) puts("0");
		  else {
				a = query( 1 , 1 , n , 1 , p );
				//if ( a.r < 0 ) a.r = 0;
				b = query( 1 , 1 , n , p , n );
				//if ( b.l < 0 ) b.l = 0;
				printf("%lld\n",a.r + b.l - 1);
		  }
	 }
	 else {
		  scanf("%d",&p);
		  update( 1 , 1 , n, p , -INF );
		  st[sp++] = p;
		  elim[p] = true;
	 }
  }
  return 0;
}