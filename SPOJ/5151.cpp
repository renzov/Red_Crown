#include<cstdio>
#include<queue>
using namespace std;
int d[1<<16] = {0};
int start = (1<<16)-(1<<8);
int edge[ 32 ][ 2 ] = { {0,1} , {0,2} , {0,8} , {0,4} ,
						    {1,5} , {1,3} , {1,9} , {2,3} ,
							 {2,10} , {2,6} , {3,7} , {3,11} ,
							 {4,6} , {4,5} , {4,12} , {5,13} ,
							 {5,7} , {6,7} , {6,14} , {7,15} ,
							 {8,12} , {8,10}, {8,9} , {9,11} ,
							 {9,13} , {10,14} , {10,11} , {11,15} ,
							 {12,14} , {12,13} , {13,15} , {14,15}
						  };
int shl[16] = { 1 , 1<<1 , 1<<2 , 1<<3 , 1<<4 , 1<<5, 1<<6, 1<<7, 
					 1<<8, 1<<9, 1<<10, 1<<11, 1<<12, 1<<13, 1<<14, 1<<15 };

void bfs(){
  queue<int> q;
  int u = start;
  int v;
  d[ u ] = 0;
  q.push( u );
  int x,y;
  int a,b;
  while ( 1 ){
	 u = q.front();
	 q.pop();
	 if ( d[u] == 3 ) break;
	 for (int i=0; i < 32; ++i){
		x = edge[i][0]; y = edge[i][1];
		a = u & shl[x]; b = u & shl[y];
		if (a==0 && b>0){
		  v = u ^ shl[x] ^ shl[y];
		  if (d[v] == 0 && v != start){ d[v] = d[u] + 1; q.push(v); }
		}
		else if (a>0 && b==0){
		  v = u ^ shl[x] ^ shl[y];
		  if ( d[v] == 0 && v != start){ d[v] = d[u] + 1; q.push(v); }
		}
	 }
  }
}

int main(){
  int runs;
  int state;
  int b;
  bfs();
  scanf("%d",&runs);
  for (int k=1; k <= runs; ++k){
	 state = 0;
	 for (int i=0; i < 16; ++i){
		scanf("%d",&b);
		if (b) state |= shl[i];
	 }
	 if ( state == start ) printf("Case #%d: 0\n",k);
	 else if ( d[state] == 0 ) printf("Case #%d: more\n",k);
	 else printf("Case #%d: %d\n",k,d[state]);
  }
  return 0;
}