#include<list>
#include<cstdio>
#include<algorithm>

using namespace std;

void read_num(char *cad,list<int> &N1){
	 for (int i=0; cad[i]; ++i){
		  switch(cad[i]){
			 case 'V' : N1.push_front(0); break;
			 case 'U' : N1.push_front(1); break;
			 case 'C' : N1.push_front(2); break;
			 case 'D' : N1.push_front(3); break;
		  }
	 }
}

list<int> add(list<int> &N1, list<int> &N2){
  int carry = 0;
  list<int> r;
  int a,b,res;

  int m = max( N1.size() , N2.size() );
  list<int>::iterator A = N1.begin();
  list<int>::iterator B = N2.begin();
  for (int i=0; i < m; ++i){
		  if (i < N1.size()) a = *A,A++;
		  else a = 0;
		  if (i < N2.size()) b = *B,B++;
		  else b = 0;
		  res = (a + b + carry);
		  r.push_back( res%4 );
		  carry = res / 4;
  }
  if (carry) r.push_back(carry);
  return r;
}

char to_char(int v){
  if (v == 0) return 'V';
  if (v == 1) return 'U';
  if (v == 2) return 'C';
  return 'D';
}

void output_list(list<int> &L){
  for (list<int>::iterator it = L.begin(); it != L.end(); ++it){
		printf("%d",*it);
  }
  putchar('\n');
}

int main(){

  int runs;
  char cad[100];
  char res[100];

  scanf("%d",&runs);
  puts("COWCULATIONS OUTPUT");
  while (runs--){
	 scanf("%s",cad);
	 list<int> N1;
	 read_num(cad,N1);
	 scanf("%s",cad);
	 list<int> N2;
	 read_num(cad,N2);
	 //output_list(N1);
	 //output_list(N2);
	 for (int i=0; i < 3; ++i){
		  scanf("%s",cad);
		  if (cad[0]=='A'){
				//puts("After add");
				N2 = add(N1,N2);
				//output_list(N2);
		  }
		  else if (cad[0]=='L'){
				//puts("After L");
				N2.push_front(0);
				//output_list(N2);
		  }
		  else if (cad[0]=='R'){
				//puts("After R");
				N2.pop_front();
				N2.push_back(0);
				//output_list(N2);
		  }
	 }
	 scanf("%s",res);
	 while (N2.size() < 8){
		  N2.push_back(0);
	 }
	 if (N2.size() > 8) puts("N0");
	 else {
		  bool ok = true;
		  list<int>::iterator it = N2.begin();
		  for (int i=7; i >= 0; i--){
				if (to_char(*it) != res[i]){
					 ok = false;
					 break;
				}
				it++;
		  }
		  if (ok) puts("YES");
		  else puts("NO");
	 }
  }
  puts("END OF OUTPUT");
  return 0;
}