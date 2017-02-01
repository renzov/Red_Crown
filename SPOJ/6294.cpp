#include<cstdio>
#include<string>
#include<map>
using namespace std;
int seg_tree[4 * 30005];
string w[30005];

void build_tree(int n,int l,int r){
  seg_tree[n] = 0;
  if (l==r) return;
  int m=(l+r)>>1;
  build_tree(2*n,l,m); build_tree(2*n+1,m+1,r);
}

int query( int n , int L , int R, int l , int r ){
  if (l==L && r==R) return seg_tree[n];
  int m = (L+R)>>1;
  if (r <= m) return query( 2*n , L , m, l, r );
  if (l > m) return query(2*n + 1, m+1, R, l, r);
  return query(2*n, L,m,l,m) + query(2*n+1,m+1,R,m+1,r);
}

void update(int N, int p){
  int l = 1;
  int r = N;
  int n = 1;
  int m;
  while ( l!=r ){
	 m = (l+r)>>1;
	 if (p <= m){ n <<= 1; r = m; }
	 else { n<<=1; n++; l = m+1; }
  }
  seg_tree[n]++;
  while (n > 1){
	 n >>= 1;
	 seg_tree[n] = seg_tree[2*n] + seg_tree[2*n + 1];
  }
}

int main(){
  int runs;
  int n;
  int idx;
  char s[22];
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d",&n);
	 build_tree(1,1,n);
	 for (int i=0; i < n; ++i){
		  scanf("%s",s);
		  w[i] = string(s);
	 }
	 map<string,int> m;
	 for (int i=0; i < n; ++i){
		scanf("%s",s);
		m[string(s)] = i+1;
	 }
	 long long res = 0;
	 for (int i=0; i < n; ++i){
		idx = m[ w[i] ];
		res += query( 1 , 1 , n, idx , n );
		update(n,idx);
	 }
	 printf("%lld\n",res);
  }
  return 0;
}