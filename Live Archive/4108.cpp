#include<cstdio>
#include<algorithm>
using namespace std;
const int MAX = 100000;
int seg_tree_max[4*MAX];
int seg_tree_min[4*MAX];
int query[ MAX + 2 ][3];
int inv[ MAX + 2 ];

struct point {
  int p;
  int v;
  bool operator<(const point &that) const { return v < that.v; }
};

point P[ 2*MAX + 2 ];

int update(int n,int L,int R,int l,int r,int h){
  if (seg_tree_min[n] > h) return 0;
  printf("Entramos a (%d,%d)\n",L,R);
  if (l==L && r==R && seg_tree_max[n] == seg_tree_min[n] ){ printf("Hallamos\n"); seg_tree_max[n] = seg_tree_min[n] = h; return R - L; }
  if (seg_tree_max[n] == seg_tree_min[n]){
	 seg_tree_max[n<<1] = seg_tree_max[ (n<<1) + 1 ] = seg_tree_max[n];
	 seg_tree_min[n<<1] = seg_tree_min[ (n<<1) + 1 ] = seg_tree_min[n];	 
  }
  int M = (L+R)>>1;
  int res;
  if(r <= M) res = update(n<<1,L,M,l,r,h);
  else if (l>M) res = update((n<<1)+1,M+1,R,l,r,h);
  else res = update(n<<1,L,M,l,M,h) + update((n<<1)+1,M+1,R,M+1,r,h);
  seg_tree_max[n] = max( seg_tree_max[n<<1],seg_tree_max[(n<<1)+1] );
  seg_tree_min[n] = min( seg_tree_min[n<<1],seg_tree_min[(n<<1)+1] );
  return res;
}

void build_tree(int n,int l,int r){
  seg_tree_min[n] = seg_tree_max[n] = 0;
  if (l==r) return;
  int m = (l + r) >> 1;
  build_tree( n<<1 , l , m );
  build_tree( (n<<1) + 1 , m+1, r );
}

int main(){
  int runs;
  int m,l,r;
  int last;
  int res;
  int n;
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d",&m);
	 n = 0;
	 for (int i=0; i < m; ++i){
		scanf("%d %d %d",&query[i][0],&query[i][1],&query[i][2]);
		if (query[i][1] > n) n = query[i][1];
		//P[i<<1].p = -(i+1); P[i<<1].v = l;
		//P[(i<<1) + 1].p = (i+1); P[(i<<1) + 1].v = r;
	 }
	 /*sort(P,P + (m<<1));
	 n = 1; last = P[0].v; inv[ n ] = last;
	 for (int i=0; i < (m<<1); ++i){
		if ( P[i].v != last ){ n++; last = P[i].v; inv[ n ] = last; }
		if ( P[i].p < 0 ){ query[ -P[i].p - 1 ][0] = n; }
		else { query[ P[i].p - 1 ][1] = n; }
	 }*/
	 build_tree(1,1,n);
	 res = 0;
	 int tmp;
	 printf("llegamos a querys\n");
	 for (int i=0; i<m; ++i){
		//printf("Q = (%d,%d)\n",query[i][0] , query[i][1]);
		tmp = update( 1 , 1 , n, query[i][0] , query[i][1] , query[i][2] );
		printf("Salida %d\n",tmp);
		res += tmp;
		printf("Procesamos query %d\n",i);
	 }
	 printf("%d\n",res);
  }
  return 0;
}