#include<cstdio>
#include<cstring>
#include<cctype>
int main(){
	char A[256];
	char B[256];

	scanf("%s %s", A, B);
	for ( int i=0; A[i] ; ++i ){
		A[i] = tolower(A[i]);
		B[i] = tolower(B[i]);
	}
	printf("%d\n", strcmp(A,B));
}
