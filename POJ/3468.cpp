#include<cstdio>
#include<algorithm>
using namespace std;
const int MAX = 100000 * 4;
long long prop[ MAX ];
long long seg_tree[ MAX ];
int a[100003];

void build_tree(int n,int l,int r){
  prop[n] = 0;
  if (l==r){  seg_tree[n] = a[l]; return; }
  int m = (l+r)>>1;
  build_tree(n<<1,l,m);
  build_tree((n<<1)+1,m+1,r);
  seg_tree[n] = seg_tree[n<<1] + seg_tree[ (n<<1) + 1 ];
}

void update(int n,int L,int R,int l,int r,int v){
  if (r < L || R < l ) return;
  if (L==l && r==R){
	 seg_tree[n] += (long long)v * (R - L + 1);
	 prop[n] += v;
	 return;
  }
  int M = (L + R) >> 1;
  if (prop[n] != 0){
	 seg_tree[n<<1] += (prop[n] * (M - L + 1));
	 seg_tree[(n<<1) + 1] += (prop[n] * (R - (M+1) + 1));
	 prop[(n<<1) + 1] += prop[n];
	 prop[n<<1] += prop[n];
	 prop[n] = 0;
  }
  if (r <= M) update( n<<1 , L , M , l , r , v);
  else if (M < l) update( (n<<1) + 1, M + 1, R , l , r , v );
  else {
	 update( n<<1 , L , M , l , M , v);
	 update( (n<<1) + 1, M + 1, R , M + 1 , r , v );
  }
  seg_tree[n] = seg_tree[n<<1] + seg_tree[ (n<<1) + 1 ];
}

long long query(int n,int L,int R,int l,int r){
  if (r < L || R < l ) return 0;
  if (l==L && r==R) return seg_tree[n];
   int M = (L + R) >> 1;
  if (prop[n] != 0){
	 seg_tree[n<<1] += (prop[n] * (M - L + 1));
	 seg_tree[(n<<1) + 1] += (prop[n] * (R - (M+1) + 1));
	 prop[(n<<1) + 1] += prop[n];
	 prop[n<<1] += prop[n];
	 prop[n] = 0;
  }
  if (r <= M) return query( n<<1 , L , M , l , r);
  if (M < l) return query( (n<<1) + 1, M + 1, R , l , r);
  return query(  n<<1 , L , M , l , M ) + query( (n<<1) + 1, M + 1, R , M + 1 , r);
}

int main(){

  int n;
  int q;
  int l,r,v;
  char c;
  while (scanf("%d %d",&n,&q) != EOF){
	 for (int i=1; i <= n; ++i) scanf("%d",a+i);
	 build_tree(1,1,n);
	 for (int i=0; i < q; ++i){
		scanf(" %c %d %d",&c,&l,&r);
		if ( c == 'Q' ){
		  printf("%lld\n",query(1,1,n,l,r));
		}
		else {
		  scanf("%d",&v);
		  update( 1 , 1 , n , l , r , v );
		}
	 }
  }
  return 0;
}