#include<cstdio>
using namespace std;

int main (){
	int runs;
	int L, W, H;

	while ( scanf("%d", &runs) && runs ){
		int maxV = 0;
		int maxH = 0;
		while ( runs-- ){
			scanf("%d %d %d", &L, &W, &H);
			if ( H > maxH ){
				maxH = H;
				maxV = L * W * H;
			}
			else if ( maxH == H && L*H*W > maxV ){
				maxV = L * W * H;
			}
		}
		printf("%d\n", maxV);		
	}
	return 0;
}
