#include<cstdio>
#include<queue>
#include<algorithm>
#include<climits>
using namespace std;

int val[ 7 ];
int pred[ 10 ][ 10 ][ 6 ];
int d[ 10 ][ 10 ][ 6 ];
int dx[4]={1,0,-1,0};
int dy[4]={0,-1,0,1};
int nbot[6][4] =  { { 3 , 2 , 5 , 4 } , 
						  { 3 , 4 , 5 , 2 } ,
						  { 3 , 1 , 5 , 0 } ,
						  { 2 , 0 , 4 , 1 } ,
						  { 3 , 0 , 5 , 1 } ,
						  { 4 , 0 , 2 , 1 }  
						};

/*
	 Frente - 0 
	 Atras - 1
	 Arriba - 2
	 Der - 3
	 Abajo - 4
	 Izq - 5
 */

struct tuple{
  int x,y,bot,w;
  tuple(){}
  tuple(int X,int Y,int B,int W){
	 x = X;
	 y = Y;
	 bot = B;
	 w = W;
  }
  bool operator<(const tuple &that) const{
	 return w > that.w; 
  }
};

void printPos(int x,int y){
	 putchar( (char)(x + 'a') );
	 putchar( (char)(8 - y + '0') );
}

void get_pos(char *p , int &x , int &y ){
  y =  8 - (p[1] - '0');
  x = p[0]  - 'a';
}

void printSol(int x, int y){
  if (pred[y][x][0] != -1){
	 switch(pred[y][x][0]){
		case 0: printSol(x-1,y); break;
		case 1: printSol(x,y+1); break;
		case 2: printSol(x+1,y); break;
		case 3: printSol(x,y-1); break;
	 }
	 putchar(' ');
	 printPos(x,y);
  }
  else {
	 putchar(' ');
	 printPos(x,y);
  }
}

void dijkstra(char *ini,char *fin){
  int sx,sy;
  int ex,ey;
  
  get_pos( ini , sx , sy );
  get_pos( fin , ex , ey );

  priority_queue< tuple > q;
  for (int i=0; i < 8; ++i)
	 for (int j=0; j < 8; ++j)
		for (int k=0; k < 6; ++k){
		  d[i][j][k] = INT_MAX;
		  pred[i][j][k] = -1;
		}
  d[sy][sx][4] = val[ 4 ];
  q.push( tuple(sx,sy,4,val[4]) );

  int x,y,ny,nx;
  int w,b,next;

  while (!q.empty()){

	 x = q.top().x;
	 y = q.top().y;
	 w = q.top().w;
	 b = q.top().bot;
	 q.pop();

	 if (w > d[y][x][b]) continue;
	 if (x == ex && y == ey) break;

	 for (int i=0; i < 4; ++i){
		nx = x + dx[i];
		ny = y + dy[i];
		if (nx<0||ny<0||nx>=8||ny>=8) continue;
		next = nbot[b][i];
		if ( d[ny][nx][next] > (d[y][x][b] + val[next])){
		  d[ny][nx][next] = d[y][x][b] + val[next];
		  //pred[ny][nx][next] = i;
		  q.push( tuple(nx,ny,next,d[ny][nx][next]) );
		}
	 }
  }
  printf("%d",d[ey][ex][b]);
  //printSol(ex,ey);
  putchar('\n');
}


int main(){
  char ini[5];
  char fin[5];

  scanf("%s",ini);
  scanf("%s",fin);
  for (int i=0; i < 6; ++i)
	 scanf("%d",val + i);
  swap(val[0],val[1]);
  dijkstra(ini,fin);
  return 0;
}