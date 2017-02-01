#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;

vector< vector<int> > A;
vector< vector<int> > B;
vector< vector<bool> > vis;
int m;
 
struct inst {
  int dest;
  char type;
};

inst I[100005];
int idx[100005];
int lbl[100005];

int get_index( int x ){
  return (lower_bound( lbl , lbl + m , x ) - lbl); 
}

int compress( vector< vector<int> > &V , int ni ){
  int nexti;
  if ( idx[ ni ] != -1 ) return idx[ ni ];
  if ( I[ni].type == '0' ) return 0;
  if ( I[ni].type == '1' ) return 1;
  if ( I[ni].type == 'J' ){
	 nexti = get_index( I[ni].dest );
	 return compress( V , nexti );
  }
  nexti = get_index( I[ni].dest );
  int left = compress( V , nexti );
  int right = compress( V , ni + 1 );
  if ( left == right ) return left;
  //Create a node
  V.push_back( vector<int>() );
  int i = V.size() - 1;
  idx[ni] = i;
  V[i].push_back(left); V[i].push_back(right);
  return i;
}

int process( vector< vector<int> > &V ){
  m = 0;
  char s[25];
  while ( 1 ){
	 scanf("%s",s);
	 if ( s[0] == 'E' ) break;
	 sscanf(s,"%d",&lbl[m]);
	 scanf("%s",s);
	 if ( s[0] == 'R' ){
		I[m].type = s[3];
	 }
	 else {
		scanf("%d",&I[m].dest); I[m].type = s[0];
	 }
	 m++;
  }
  V.clear(); V.resize(2);
  memset( idx , -1 , sizeof(int)*m );
  return compress( V , 0 );
}

void print( vector< vector<int> > &V , int root ){
	 printf("root = %d\n",root);
	 for ( int i=0; i < V.size(); ++i ){
		printf("%d ->",i);
		for ( int j=0; j < V[i].size(); ++j ){
		  printf(" %d",V[i][j]);
		}
		puts("");
	 }
}

bool dfs( int a , int  b ){
  if ( a == 0 || b == 0 ) return a==b;
  if ( a == 1 || b == 1) return a==b;
  return dfs( A[a][0] , B[b][0] ) && dfs( A[a][1] , B[b][1] );
}

int main(){
  int p,b;
  int ra,rb;
  int runs;
  scanf("%d",&runs);
  while ( runs-- ){
	 scanf("%d",&p);
	 for ( int i=0; i < p; ++i ){
		scanf("%d",&b);
		ra = process(A);
		rb = process(B);
		if ( dfs(ra,rb) ) puts("1");
		else puts("0");
	 }
	 if ( runs ) putchar('\n');
  }
  return 0;
}