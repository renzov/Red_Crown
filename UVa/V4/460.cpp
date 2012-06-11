#include<cstdio>
#include<algorithm>
using namespace std;

int main(){
	int xl[2];
	int yl[2];
	int xu[2];
	int yu[2];
	int runs;
	int xleft,yleft;
	int xright,yright;
	scanf("%d",&runs);
	while ( runs-- ){
		for ( int i=0; i < 2; ++i ){
			scanf("%d %d %d %d",&xl[i],&yl[i],&xu[i],&yu[i]);
		}
		xleft = max(xl[0],xl[1]);
		xright = min( xu[0] , xu[1] );
		yleft = max( yl[0] , yl[1] );
		yright = min( yu[0] , yu[1] );
		if ( xleft < xright && yleft < yright ){
			printf("%d %d %d %d\n",xleft,yleft,xright,yright);
		}
		else {
			puts("No Overlap");
		}
		if (runs) puts("");
	}
	return 0;
}
