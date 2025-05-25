#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
const int MAXN = 100005;

int A[MAXN];
int B[MAXN];
int C[MAXN];
char buffer[2*MAXN];

void readHex( int *L, int &size ){
	// Read the string into buffer
	fgets(buffer, MAXN, stdin);
	int n = strlen(buffer);

	buffer[n - 1] = '\0'; n--;
	size = n >> 1;
	for ( int i = 0; i < size; ++i )
		sscanf( buffer + 2*i, "%2x", L + i );
}

int main(){
	int N;
	int M;

	freopen( "decode.in", "r", stdin );
	freopen( "decode.out", "w", stdout );

	readHex( A, N );
	readHex( B, M );

	C[0] = B[0] ^ 0x20;
	for ( int i = 1; i < M; ++i )
		C[i] = A[i - 1] ^ C[i - 1] ^ B[i];
	for ( int i = 0; i < M; ++i )
		printf("%02X", C[i]);
	puts("");
	return 0;
}
