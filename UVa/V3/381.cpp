#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

double avg[ 150 ];
int bonus[ 150 ];
int absence[ 150 ];
int letter[ 150 ];

int main(){

	int runs;
	int n,m;
	int least;
	int score;
	int sum;
	double media;
	double sd;
	double q1;
	double q2;
    int d;
	scanf("%d",&runs);
	puts("MAKING THE GRADE OUTPUT");
	while (runs--){
		scanf("%d %d",&n,&m);
		media = 0.0;
		
        d = m;
		if (d > 2) d = m-1;
		
        for (int i=0; i < n; ++i){
			least = 100;
			sum = 0;
			for (int j=0; j < m; ++j){
				scanf("%d",&score);
				if (score < least) least = score;
				sum += score;
			}
			if (m > 2) sum -= least;
			avg[i] = (double)sum / d;
			avg[i] = floor(avg[i]*10 + .5)/10;
			//printf("avg[%d] = %0.1lf\n",i,avg[i]);
			media += avg[i];
			scanf("%d %d",&bonus[i],&absence[i]);
		}
		media = media / n;
		media = floor(media*10 + .5)/10;
		
		//printf("media = %0.1lf\n",media);
        
        sd = 0.0;
		for (int i=0; i < n; ++i){
			sd += ((avg[i] - media)*(avg[i] - media));
		}
		sd /= n;
		sd = sqrt(sd);
		sd = floor(sd*10 + .5)/10;
		
		//printf("sd = %0.1lf\n",sd);
        
        if (sd < 1.0) sd = 1.0;
		q1 = media + sd;
		q1 = floor(q1*10 + .5)/10;
		q2 = media - sd;
		q2 = floor(q2*10 + .5)/10;
		
	    //printf("q1 = %0.1lf\n",q1);
		//printf("q2 = %0.1lf\n",q2);
		
		for (int i=0; i < n; ++i){
			avg[i] += ((bonus[i]/2)*3);
		}
		
		for (int i=0; i < n; ++i){
			if (avg[i] > q1 || fabs(avg[i] - q1) < 0.1) letter[i] = 0;
			else if (avg[i] > media || fabs(avg[i] - media) < 0.1) letter[i] = 1;
			else if (avg[i] > q2 || fabs(avg[i] - q2) < 0.1) letter[i] = 2;
			else letter[i] = 3;
		}
		
		for (int i=0; i < n; ++i){
			if (absence[i] == 0){ letter[i] = max( 0 , letter[i] - 1 ); }
			else { letter[i] = min( 4 , letter[i] + absence[i]/4 ); }
		}
		
		sum = 0;
		for (int i=0; i < n; ++i){
			switch(letter[i]){
				case 0: sum += 4; break;
				case 1: sum += 3; break;
				case 2: sum += 2; break;
				case 3: sum += 1; break;
			}
		}
		media = (double)sum /  n;
		media = floor(media*10 + .5)/10;
		printf("%0.1lf\n",media);
	}
	puts("END OF OUTPUT");
	return 0;
}
