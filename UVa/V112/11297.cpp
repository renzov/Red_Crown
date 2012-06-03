#include<cstdio>
#include<algorithm>
#include<climits>
using namespace std;

int N;
int val;
int x1,y1,x2,y2;
const int MAX = 505 * 4;
int seg_tree_2D_max[MAX][MAX];
int seg_tree_2D_min[MAX][MAX];


void build_tree_2D(int y,int x,int l,int r){
  if (l==r){
		seg_tree_2D_max[y][x] = -INT_MAX;
		seg_tree_2D_min[y][x] = INT_MAX;
		return;
  }
  int m = (l+r) >> 1;
  build_tree_2D(y,2*x,l,m);
  build_tree_2D(y,2*x+1,m+1,r);
}

void build_tree_1D( int n , int l, int r ){
  build_tree_2D( n , 1 , 1 , N );
  if (l==r) return;
  int m = (l + r) >> 1;
  build_tree_1D( 2*n , l , m );
  build_tree_1D( 2*n + 1, m+1 , r );
}

void update_2D(int y,int x,int l,int r,int p){
  if (l==r){
	 seg_tree_2D_max[y][x] = max( seg_tree_2D_max[y][x] , val );
	 seg_tree_2D_min[y][x] = min( seg_tree_2D_min[y][x] , val );
	 //printf("\t\t\tEntre X %d - %d = %d %d\n",l,r,seg_tree_2D_min[y][x], seg_tree_2D_max[y][x] );
	 return;
  }
  int m = (l+r)>>1;
  if ( p <= m )
	 update_2D(y,2*x,l,m,p);
  else
	 update_2D(y,2*x+1,m+1,r,p);

  seg_tree_2D_max[y][x] = max( seg_tree_2D_max[y][2*x], seg_tree_2D_max[y][2*x+1] );
  seg_tree_2D_min[y][x] = min( seg_tree_2D_min[y][2*x], seg_tree_2D_min[y][2*x+1] );
  //printf("\t\t\tEntre X %d - %d = %d %d\n",l,r,seg_tree_2D_min[y][x] , seg_tree_2D_max[y][x] );
}

void update_1D( int n , int l, int r, int  y, int x){
	if (l==r){
		//printf("\t\tEntre Y %d - %d\n",l, r );
		update_2D(n,1,1,N,x);
		return;
   }
	int m = (l + r) >> 1;
   if (y <= m) update_1D( 2*n, l, m, y, x );
   else update_1D(2*n+1, m+1, r, y ,x );
	//printf("\t\tEntre Y %d - %d\n",l, r );
	update_2D(n,1,1,N,x);
   //seg_tree_2D_max[n][1] = max( seg_tree_2D_max[2*n][1] , seg_tree_2D_max[2*n+1][1] );
   //seg_tree_2D_min[n][1] = min( seg_tree_2D_min[2*n][1] , seg_tree_2D_min[2*n+1][1] );
}

pair<int,int> query_2D(int y,int x,int L,int R,int l,int r){
  if (l==L && r==R){
	 return make_pair( seg_tree_2D_min[y][x] , seg_tree_2D_max[y][x] );
  }
  int m = (L+R) >> 1;
  if (r <= m) return query_2D(y,2*x,L,m,l,r);
  if (l > m) return query_2D(y,2*x+1,m+1,R,l,r);
  pair<int,int> t1 = query_2D(y,2*x,L,m,l,m);
  pair<int,int> t2 = query_2D(y,2*x+1,m+1,R,m+1,r);
  return make_pair( min( t1.first,t2.first ) , max(t1.second,t2.second) );
}

pair<int,int> query_1D(int n,int L,int R,int l,int r){
  if (L==l && r==R){
		return query_2D(n,1,1,N,x1,x2);
  }
  int m = (L + R) >> 1;
  if (r <= m)  return query_1D(2*n,L,m,l,r);
  if (l > m) return query_1D(2*n+1,m+1,R,l,r);
  pair<int,int> t1 = query_1D(2*n,L,m,l,m);
  pair<int,int> t2 = query_1D(2*n+1,m+1,R,m+1,r);
  return make_pair( min( t1.first,t2.first ) , max(t1.second,t2.second) );
}

int main(){
  int M;
  char c;
  scanf("%d %d",&N,&M);
  if (N != M) while (1);
  build_tree_1D(1,1,N);
  for (int i=1; i <= N; ++i)
	 for (int j=1; j <= N; ++j){
		scanf("%d",&val);
		x1 = j;
		y1 = i;
		update_1D(1,1,N,y1,x1);
	 }
  int q;
  pair<int,int> res;
  scanf("%d",&q);
  while (q--){
	 //printf("op = %d\n",op);
	 scanf(" %c",&c);
	 if (c=='q'){
		scanf("%d %d %d %d",&y1,&x1,&y2,&x2);
		if (N==0){ printf("0 0\n"); continue; }
		if (y1 > y2) swap(y1,y2);
		if (x1 > x2) swap(x1,x2);
		if (x1 < 0) x1 = 1;
		if (x2 > N) x2 = N;
		if (y1 < 0) y1 = 1;
		if (y2 > N) y2 = N;
		res = query_1D(1,1,N,y1,y2);
		printf("%d %d\n",res.second,res.first);
	 }
	 else {
		scanf("%d %d %d",&y1,&x1,&val);
		if (x1 >= 1 && x1 <= N && y1 >= 1 && y1 <= N)
		  update_1D(1,1,N,y1,x1);
	 }
  }
  return 0; 
}