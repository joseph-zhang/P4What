#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<string>
using namespace std;

int h[1000010];

int main(){
	int i,j;
	for (i=5;i<1000;i+=4)
		if (h[i]==0)
			for (j=i;i*j<1000002;j+=4)
				h[i*j]=h[i]+h[j]+1;
				
	for (i=25;i<1000002;i++)
		h[i]=(h[i]==1)+h[i-1];
		
	while(scanf("%d",&i) && i)
		printf("%d %d\n",i,h[i]);
	return 0;
}
