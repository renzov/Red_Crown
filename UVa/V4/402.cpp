#include<cstdio>
#include<vector>
using namespace std;

int main(){
	int a[22];
	int N,X;
	int cases = 0;
	while ( scanf("%d %d",&N,&X) != EOF ){
		vector<int> v(N);
		cases++;
		for (int i=0; i < N; ++i) v[i] = i+1;
		for ( int i=0; i < 20; ++i ){ 
			scanf("%d",a+i);	
		}
		//Simulation
		int m = 0;
		int pos = 0;
		while ( X < N && m < 20 ){
			while ( (pos + a[m] - 1) < N && X < N ){
				//printf("Eliminamos %d\n",v[a[m]-1]);
				v.erase( v.begin() + pos + a[m] - 1 );
				pos += (a[m] - 1); 
				N--;
			}
			pos = 0;
			m++;
		}
		printf("Selection #%d\n",cases);
		for ( int i=0; i < N; ++i ){
			if ( i > 0 ) putchar(' ');
			printf("%d",v[i]);
		}
		puts("\n");
	}
	return 0;
}
