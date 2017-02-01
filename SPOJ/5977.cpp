#include<cstdio>

const int MOD = 1000000007;
const int MAX = 200005;
struct MaxHeap {
  int H[MAX];
  int size;
  MaxHeap(){ size = 0; }
  void insert(int data){
		int i;
		size++;
		for (i=size; i > 1; i>>=1){
			 if (data <= H[i>>1]){  break; }
			 H[i] = H[i>>1];
		}
		H[i] = data;
  }
  inline int top(){ return (size>0)? H[1]:0; }
  int remove(){
	 int res = H[1];
	 int i,j;
	 int last = H[size--];
	 for (i = 1,j=2; j <= size ; i=j,j<<=1){
		  if (j < size && H[j] < H[j+1]) j++;
		  if (last >= H[j]) { break; }
		  H[i] = H[j];
	 }
	 H[i] = last;
	 return res;
  }
};

struct MinHeap {
  int H[MAX];
  int size;
  MinHeap(){ size = 0; }
  void insert(int data){
		int i;
		size++;
		for (i=size; i > 1; i>>=1){
			 if (data >= H[i>>1]){  break; }
			 H[i] = H[i>>1];
		}
		H[i] = data;
  }
  inline int top(){ return (size>0)? H[1]:0; }
  int remove(){
	 int res = H[1];
	 int i,j;
	 int last = H[size--];
	 for (i = 1,j=2; j <= size ; i=j,j<<=1){
		  if (j < size && H[j] > H[j+1]) j++;
		  if (last <= H[j]) { break; }
		  H[i] = H[j];
	 }
	 H[i] = last;
	 return res;
  }
};

int main(){
  int n;
  int s;
  long long e;
  int i;
  int ant;
  int mid;
  int runs;
  int prevMed;
  long long a,b,c,res;
  int t;
  scanf("%d",&runs);
  while (runs--){
	 MaxHeap A;
	 MinHeap B;
	 scanf("%lld %lld %lld %d",&a,&b,&c,&n);
	 A.insert(1);
	 prevMed = 1;
	 s = 1;
	 ant = 1;
	 res = 1;
	 for (i=1; i < n; ++i){
		  e = ( (a * prevMed) + ( b * (i+1) ) + c ) % MOD;
		  t = (int)e;
		  s++;
		  if (s&1) mid = (s+1) >> 1;
		  else mid = s >> 1;
		  if (mid == ant){
			 if (t < A.top()){
				B.insert( A.remove() ); A.insert(t);
			 }
			 else {
				B.insert( t );
			 }
		  }
		  else {
				ant = mid;
				B.insert( t );
				A.insert( B.remove() );
		  }
		  res += e;
		  prevMed = A.top();
	 }
	 printf("%lld\n",res);
  }
  return 0;
}