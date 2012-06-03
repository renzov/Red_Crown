#include <stdio.h>
#include <string.h>

#define MAX 1001

int Mildt[MAX],M,L,n;
int boxes[MAX+MAX],sum;

FILE *fi;

int verify ( void )
{
  int nr,i,prev,box,msum;

  if(fscanf(fi,"%d",&nr)!=1 || nr < 0 || nr > n) 
    return 0;

  msum = 0;
  prev=-1;
  for(i=0;i<nr;i++)
    {
      if(fscanf(fi,"%d",&box)!=1 || box <= prev || box > n) 
	return 0;
      msum += boxes[box-1];
      prev = box;
    }

  return (msum<=M && (sum-msum)<=L);
}


int main (void)
{
  int i,j;
  char e,p[100];

  freopen("shop.in","rt",stdin);
  if ( (fi = fopen("shop.out","rt")) == NULL)
    goto no;
  
  while(scanf("%d%d",&M,&L)==2 && (M||L))
    {
      scanf("%d",&n);
      memset(Mildt,0,sizeof(Mildt));
      Mildt[0] = -1;
      sum=0;
      for(i=0;i<n;i++)
	{
	  scanf("%d",boxes+i);
	  sum+=boxes[i];
	  for(j=M;j>=boxes[i];j--)
	    if (!Mildt[j] && Mildt[j-boxes[i]])
	      Mildt[j] = i+1;
	}
      for(i=0;i<=M;i++)
	if(Mildt[i] && sum-i <= L)
	  break;

      if(i>M)
	{
	  if(fscanf(fi," Impossible to distribut%c",&e)!=1 || e!='e') 
	    goto no;
	}
      else
	{
	  if (!verify())
	    goto no;
	}
    }

  if(fscanf(fi," %c",&e)==1)
    goto no;

  printf("\n\n\nYes - Correct Answer!!!!\n\n\n");
  return 0;


 no:
  printf("\n\n\nNo - Incorrect Output!!!!\n\n\n");
  return 0;
}
