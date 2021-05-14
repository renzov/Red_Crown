#include<cstdio>
#include<algorithm>
using namespace std;

char S[64];
int V[4];

int main(){
	scanf("%s", S);
	for ( int i=0; S[i]; ++i ){
		switch (S[i]){
			case 'T':	V[0]++;
						break;
			case 'G':	V[1]++;
						break;
			case 'C':	V[2]++;
						break;
		}
	}
	printf("%d\n", V[0]*V[0] + V[1]*V[1] + V[2]*V[2] + 7 * ( min(V[0], min( V[1], V[2] ) ) ) );
	return 0;
}
