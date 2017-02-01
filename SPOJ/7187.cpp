#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
double p[305][2];
double G[305][305];

inline double Dist(int i,int j){
  return sqrt( (p[i][0] - p[j][0])*(p[i][0] - p[j][0]) + (p[i][1] - p[j][1])*(p[i][1] - p[j][1]) );
}

int main(){

  int N;
  double W,H;

  while ( scanf("%d %lf %lf",&N,&W,&H) && N > 0 ){
	 p[0][0] = 0.0; p[0][1] = 0.0;
	 for (int i=1; i<= N; ++i){
		  scanf("%lf %lf",&p[i][0],&p[i][1]);
	 }
	 p[N+1][0] = W;
	 p[N+1][1] = H;
	 N++;
	 for (int i=0; i < N; ++i)
		for (int j=i+1;j <= N; ++j){
			G[j][i] = G[i][j] = Dist( i , j )/ 2.0;
		}
	 for (int k=0; k <= N; ++k)
		for (int i=0; i <= N; ++i)
		  for (int j=0; j <= N; ++j)
			 G[i][j] = min( G[i][j] , max(G[i][k] , G[k][j] ) );
	 printf("%0.3lf\n",G[0][N]);
  }
  
  return 0;
}