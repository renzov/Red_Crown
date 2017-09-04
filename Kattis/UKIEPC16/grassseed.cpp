#include<cstdio>
using namespace std;

int main(){

	double C;
	int L;
	double area = 0;
	double l, w;

	scanf("%lf %d", &C, &L);
	for ( int i=0; i < L; ++i ){
		scanf("%lf %lf", &w, &l);
		area += w*l;	
	}
	printf("%f\n", area * C);
	return 0;
}
