#include<cstdio>
#include<cmath>

double angle[3];
double side[3];
int na,ns;

inline int prev(int p){
  return (2 + p)%3;
}

inline int next(int p){
  return (p+1)%3;
}

inline bool valid_angle(double p){
	return (p > 0.000000) && (p < M_PI);
}

void analyze0(void);
void analyze1(void);
void analyze2(void);
void analyze3(void);
bool isValidTriangle(void);

bool isValidTriangle(){
   if ( fabs( angle[0] + angle[1] + angle[2] - M_PI ) >= 0.000001 )
		return false;
	if ( side[0] + side[1] <= side[2] || side[1] + side[2] <= side[0] || side[2] + side[0] <= side[1] )
		return false;
	return true;
}

void analyze0(){
  if (ns < 3){
	 puts("Invalid input.");
	 return;
  }
  double cosA = (side[1]*side[1] + side[2]*side[2] - side[0]*side[0]) / (2*side[1]*side[2]);
  if (fabs(cosA) <= 1.0){
	 angle[0] = acos(cosA);
  }
  else {
	 puts("Invalid input.");
	 return;
  }
  int idx = 0;
  /* Hallamos los angulos */
  double val1 = (sin(angle[idx]) * side[ prev(idx) ]) / side[idx];
  double val2 = (sin(angle[idx]) * side[ next(idx) ]) / side[idx];
  
  if (fabs(val1 - 1.0) < 0.000001){
	 angle[ prev(idx) ] = M_PI / 2;
  }
  else if (val1 < 1.0){
	 if ( side[ idx ] < side[ prev(idx) ] ) {	/* two solutions */
		puts("More than one solution.");
		return;
	 }
	 angle[prev(idx)] = asin(val1);	
  }
  else {
	 puts("Invalid input.");
	 return;
  }
  
  if (fabs(val2 - 1.0) < 0.000001){
	 angle[ next(idx) ] = M_PI / 2;
  }
  else if (val2 < 1.0){
	 if ( side[ idx ] < side[ next(idx) ] ) {	/* two solutions */
		puts("More than one solution.");
		return;
	 }
	 angle[next(idx)] = asin(val2);
  }
  else {
	 puts("Invalid input.");
	 return;
  }
  analyze3();
  return;
}

void analyze1(){
	if (ns < 2){ puts("Invalid input."); return; }
	int v = 0;
	double s = 0.0;
	int idx;
	for (int i=0; i < 3; ++i) if (valid_angle(angle[i])){ v++; s += angle[i]; idx = i; }
	if (v == 1){
		if (ns == 3){
			/* Hallamos los angulos */
			double val1 = (sin(angle[idx]) * side[ prev(idx) ]) / side[idx];
			double val2 = (sin(angle[idx]) * side[ next(idx) ]) / side[idx];
			
			if (fabs(val1 - 1.0) < 0.000001){
				angle[ prev(idx) ] = M_PI / 2;
		   }
		   else if (val1 < 1.0){
				if ( side[ idx ] < side[ prev(idx) ] ) {	/* two solutions */
				  puts("More than one solution.");
				  return;
				}
				angle[prev(idx)] = asin(val1);	
		   }
		   else {
				puts("Invalid input.");
				return;
		   }
		   
		   if (fabs(val2 - 1.0) < 0.000001){
				angle[ next(idx) ] = M_PI / 2;
		   }
		   else if (val2 < 1.0){
				if ( side[ idx ] < side[ next(idx) ] ) {	/* two solutions */
				  puts("More than one solution.");
				  return;
				}
				angle[next(idx)] = asin(val2);
		   }
		   else {
				puts("Invalid input.");
				return;
		   }
		   analyze3();
			return;
		}
		else if (ns == 2){
			 if (fabs(side[idx]+1.0) > 0.000001){
				  if (fabs(side[prev(idx)]+1.0) > 0.000001){
					 double val1 = (sin(angle[idx]) * side[ prev(idx) ]) / side[idx];
					 if (fabs(val1 - 1.0) < 0.000001){
						  angle[ prev(idx) ] = M_PI / 2;
					 }
					 else if (val1 < 1.0){
						  if ( side[ idx ] < side[ prev(idx) ] ) {	/* two solutions */
							 puts("More than one solution.");
							 return;
						  }
						  angle[prev(idx)] = asin(val1);	
					 }
					 else {
						  puts("Invalid input.");
						  return;
					 }
				  }
				  else {
						double val2 = (sin(angle[idx]) * side[ next(idx) ]) / side[idx];
						if (fabs(val2 - 1.0) < 0.000001){
						  angle[ next(idx) ] = M_PI / 2;
						}
						else if (val2 < 1.0){
						  if ( side[ idx ] < side[ next(idx) ] ) {	/* two solutions */
							 puts("More than one solution.");
							 return;
						  }
						  angle[next(idx)] = asin(val2);
						}
						else {
						  puts("Invalid input.");
						  return;
						}
				  }
				  analyze2();
				  return;
			 }
			 else {
				double sqA = side[prev(idx)]*side[prev(idx)] + side[next(idx)]*side[next(idx)] - 2*side[prev(idx)]*side[next(idx)]*cos(angle[idx]);
				if (sqA > 0.0){
				  side[idx] = sqrt(sqA);
				  /* Hallamos los angulos */
				  double val1 = (sin(angle[idx]) * side[ prev(idx) ]) / side[idx];
				  double val2 = (sin(angle[idx]) * side[ next(idx) ]) / side[idx];
				  if (fabs(val1 - 1.0) < 0.000001){
						angle[ prev(idx) ] = M_PI / 2;
				  }
				  else if (val1 < 1.0){
						if ( side[ idx ] < side[ prev(idx) ] ) {	/* two solutions */
						  puts("More than one solution.");
						  return;
						}
						angle[prev(idx)] = asin(val1);	
				  }
				  else {
						puts("Invalid input.");
						return;
				  }
				  
				  if (fabs(val2 - 1.0) < 0.000001){
						angle[ next(idx) ] = M_PI / 2;
				  }
				  else if (val2 < 1.0){
						if ( side[ idx ] < side[ next(idx) ] ) {	/* two solutions */
						  puts("More than one solution.");
						  return;
						}
						angle[next(idx)] = asin(val2);
				  }
				  else {
						puts("Invalid input.");
						return;
				  }
				  analyze3();
				}
				else {
				  puts("Invalid input.");
				}
			 }
		}
	}
	else {
		puts("Invalid input.");
	}
}

void analyze3(){
	int v = 0;
	double s = 0.0;
	for (int i=0; i < 3; ++i) if (valid_angle(angle[i])){ v++; s += angle[i]; }
	if (v == 3 && fabs(s-M_PI) < 0.000001){
		if (ns == 0){ puts("Invalid input."); return; }
		if (ns == 1){ 
			int idx;
			for (int i=0; i<3; ++i){
				if (fabs(side[i]+1.0) > 0.0001){
					idx = i;
					break;
				}
			}
			side[prev(idx)] = (side[idx]/sin(angle[idx]))*sin(angle[prev(idx)]);
			side[next(idx)] = (side[idx]/sin(angle[idx]))*sin(angle[next(idx)]);
			if (isValidTriangle())
				printf("%.6f %.6f %.6f %.6f %.6f %.6f\n",side[0],angle[0],side[1],angle[1],side[2],angle[2]);
			else 
			  puts("Invalid input.");
			return;
		}
		else {
			double prop[3];
			for (int i=0; i < 3; ++i){
				if (fabs(side[i]+1.0) > 0.000001){
					prop[i] = side[i] / sin(angle[i]);
				}
				else {
					side[i] = (side[prev(i)]/sin(angle[prev(i)]))*sin(angle[i]);
					prop[i] = side[i]/ sin( angle[i] );
				}
			}
			if (fabs(prop[0] - prop[1]) < 0.000001 && fabs(prop[1] - prop[2]) < 0.000001 && isValidTriangle()){
				printf("%.6f %.6f %.6f %.6f %.6f %.6f\n",side[0],angle[0],side[1],angle[1],side[2],angle[2]);
			}
			else {
				puts("Invalid input.");
			}
		}
	}
	else {
		puts("Invalid input.");
	}
}

void analyze2(){
	int v = 0;
	double s = 0.0;
	for (int i=0; i < 3; ++i) if (valid_angle(angle[i])){ v++; s += angle[i]; }
	if (v == 2 && fabs(s-M_PI) > 0.000001 && s < M_PI){
		for (int i=0; i<3; ++i){
			if (fabs(angle[i]+1.0) < 0.000001){
					angle[i] = M_PI - s;
					break;
			}
		}
		analyze3();
	}
	else {
		puts("Invalid input.");
	}
}

int main(){
	int runs;
	scanf("%d",&runs);
	while (runs--){
		ns = na = 0;
		for (int i=0; i < 3; ++i){
			scanf("%lf %lf",side + i,angle + i);
			if (fabs(angle[i]+1.000000) > 0.000001 && angle[i] > 0.0) na++;
			if (fabs(side[i]+1.000000) > 0.000001 && side[i] > 0.0) ns++;
		}
		switch (na){
			case 0 : analyze0(); break;
			case 1 : analyze1(); break;
			case 2 : analyze2(); break;
			case 3 : analyze3(); break;
		}
	}
	return 0;
}
