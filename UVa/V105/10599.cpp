#include<cstdio>
#include<set>
#include<algorithm>
using namespace std;
struct point{
  int x,y;
  point(){}
  point(int X,int Y){ x=X; y=Y; }
  bool operator<(const point &that) const {
	 if (x!=that.x) return x<that.x;
	 return y < that.y;
  }
};

point P[ 101*101 ];
int dp_len[ 101*101 ];
int pred[ 101*101 ];
int dp_com[ 101*101 ];
int n,m;

void print_path(int x){
  if ( pred[x] == -1 ){
	 printf(" %d",(P[x].x-1)*m + P[x].y);
	 return;
  }
  print_path( pred[x] );
  printf(" %d",(P[x].x-1)*m + P[x].y);
}

int main(){
  int x,y;
  int N;
  int runs = 0;
  while (scanf("%d %d",&n,&m) && n >= 0 ){
	 N = 0;
	 runs++;
	 while (1){
		scanf("%d %d",&P[N].x,&P[N].y);
		if (P[N].x == 0) break;
		dp_len[N] = 1;
		dp_com[N] = 1;
		pred[N] = -1;
		N++;
	 }
	 sort( P , P + N );
	 int mx = 1;
	 x = 0;
	 for (int i=1; i < N; ++i){
		for (int j=i-1; j >= 0; --j){
		  if ( P[j].x <= P[i].x && P[j].y <= P[i].y ){
				if ( dp_len[i] < (dp_len[j] + 1) ){
				  dp_len[i] = dp_len[j] + 1;
				  dp_com[i] = dp_com[j];
				  pred[i] = j;
				  if ( mx < dp_len[i] ){ mx = dp_len[i]; x = i; }
				}
				else if ( dp_len[i] == (dp_len[j] + 1) ){
					dp_com[i] += dp_com[j];
				}
		  }
		}
	 }
	 int nc = 0;
	 for (int i=0; i < N; ++i){
		if (dp_len[i] == mx) nc += dp_com[i];
	 }
	 printf("CASE#%d: %d %d",runs,mx,nc);
	 print_path( x );
	 putchar('\n');
  }
  return 0;
}