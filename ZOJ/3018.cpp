#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <numeric>

#define repn( i , a , b ) for( int i = ( int ) a ; i < ( int ) b ; i ++ )
#define rep( i , n ) repn( i , 0 , n ) 
#define all( x )  x.begin() , x.end()
#define rall( x ) x.rbegin() , x.rend()
#define mp make_pair
#define fst first
#define snd second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;
const int MAXNODE = 110010;
const int MAX = 20000;

struct node {
	int xmin,xmax,ymin,ymax;
	int sum;
	int reg[4];
};
int size;
node qtree[ MAXNODE ];

int getNode( int x1 , int x2 , int y1, int y2 ){
	node &ref = qtree[size];
	ref.xmin = x1; ref.xmax = x2; ref.ymin = y1; ref.ymax = y2;
	ref.sum = 0;
	for ( int i=0; i < 4; ++i ) ref.reg[i] = -1;
	return size++;
}

int query( int vertex , int x1 , int x2 , int y1 , int y2 ){
	if ( qtree[vertex].xmin >= x1 && qtree[vertex].xmax <= x2 &&
		 qtree[vertex].ymin >= y1 && qtree[vertex].ymax <= y2 ){
		 	return qtree[vertex].sum;
		 }
	
	int xmid = (qtree[vertex].xmax + qtree[vertex].xmin) >> 1;
	int ymid = (qtree[vertex].ymax + qtree[vertex].ymin) >> 1;
	int res = 0;
	
	if ( x1 <= xmid && y1 <= ymid && qtree[vertex].reg[0] != -1 ){
		res += query( qtree[vertex].reg[0] , x1 , x2, y1, y2 );
	}
	if ( x2 > xmid && y1 <= ymid && qtree[vertex].reg[1] != -1 ){
		res += query( qtree[vertex].reg[1] , x1 , x2 , y1 , y2 );
	}
	if ( x1 <= xmid && y2 > ymid && qtree[vertex].reg[2] != -1 ){
		res += query( qtree[vertex].reg[2] , x1 , x2 , y1 , y2 );
	}
	if ( x2 > xmid && y2 > ymid && qtree[vertex].reg[3] != -1 ){
		res += query( qtree[vertex].reg[3] , x1 , x2 , y1 , y2 );
	}
	return res;
}

void update( int vertex , int x , int y, int val ){

	if ( qtree[vertex].xmin == qtree[vertex].xmax &&
		 qtree[vertex].ymin == qtree[vertex].ymax ){
		qtree[vertex].sum += val;
		return;
	}

	int xmid = (qtree[vertex].xmax + qtree[vertex].xmin) >> 1;
	int ymid = (qtree[vertex].ymax + qtree[vertex].ymin) >> 1;

	if ( x <= xmid && y <= ymid ){
		if ( qtree[vertex].reg[0] == -1 ){  
			qtree[vertex].reg[0] = getNode( qtree[vertex].xmin , xmid , qtree[vertex].ymin , ymid );
		}
		update( qtree[vertex].reg[0] , x , y , val );
	}
	else if ( x > xmid && y <= ymid ){
		if ( qtree[vertex].reg[1] == -1){
			qtree[vertex].reg[1] = getNode( xmid + 1 , qtree[vertex].xmax , qtree[vertex].ymin , ymid );
		}
		update( qtree[vertex].reg[1] , x , y , val );
	}
	else if ( x <= xmid && y > ymid ){
		if ( qtree[vertex].reg[2] == -1){
			qtree[vertex].reg[2] = getNode( qtree[vertex].xmin , xmid , ymid + 1 , qtree[vertex].ymax );
		}		
		update( qtree[vertex].reg[2] , x , y , val );	
	}
	else if ( x > xmid && y > ymid ){
		if ( qtree[vertex].reg[3] == -1){
			qtree[vertex].reg[3] = getNode( xmid + 1 , qtree[vertex].xmax , ymid + 1 , qtree[vertex].ymax );
		}
		update( qtree[vertex].reg[3] , x , y , val );
	}

	int s = 0;
	for ( int i=0; i < 4; ++i ){
		s += qtree[ qtree[vertex].reg[i] ].sum;
	}
	qtree[vertex].sum = s;
}

int main(){
	
	char t[25];
	char s[5];
	int x1,x2,y1,y2;
	int v;
	int root;
	
	while ( scanf("%s",s) != EOF ){
		size = 0;
		root = getNode(1,MAX,1,MAX);
		while ( 1 ){
			if ( s[0] == 'E' ) break;
			else {
				while ( 1 ){
					scanf("%s",t);
					if ( !isdigit(t[0]) ) break;
					sscanf(t,"%d",&x1);
					if ( s[0] == 'I' ){ 
						scanf("%d %d",&y1,&v);
						//printf("Insert (%d,%d) - %d\n",x1,y1,v);
						update( root , x1 , y1 , v );
					}
					else {
						scanf("%d %d %d",&x2,&y1,&y2);
						//printf("Query (%d,%d) , (%d,%d)\n",x1,x2,y1,y2);
						printf("%d\n",query(root,x1,x2,y1,y2));
					}
				}
				strcpy( s , t );
			}
		}
	}
	return 0;
}

