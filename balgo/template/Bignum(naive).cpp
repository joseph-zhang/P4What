#include<iostream>
#include<vector>
#include<string.h>
#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<string>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<math.h>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<cctype>
#include<sstream>
#define INF 0x7777777f
#define sys std::ios::sync_with_stdio(false)
#define LL long long
#define Uint unsigned int
using namespace std;

/**
*    高精度适用于非常大的数的表示
*    下述代码简单地实现了高精的部分功能,并约定每个int区域放一个 <=4 位的表示
*    与另一个文件:正整数大数加法 不同,这里采用了非常紧凑的实现,牺牲了不少可读性.
*/
struct bigData{
	int s[1100];
	int len;
};

void input(bigData &a){
	char s[1100];
	scanf("%s",s);
	long long x=0;
	int i=0,j=0;
	int l=strlen(s);
	a.len=0;
	memset(a.s,0,sizeof(a.s));
	for (j=1;j<=l/4;j++){
		for (x=0,i=l-4*j;i<l-4*j+4;i++) x=x*10+s[i]-'0';
		a.s[j]=x;
	}
	for (x=0,i=0;i<l%4;i++) x=x*10+s[i]-'0';
	if (x) a.s[j++]=x;
	a.len=j-1;
}

int bigCmp(bigData a,bigData b){
	if (a.len>b.len) return 1;
	if (a.len<b.len) return -1;
	int i=a.len,j=b.len;
	for (;i>0&&j>0&&a.s[i]==b.s[j];i--,j--);
	if (i==0&&j==0) return 0; //a == b
	if (a.s[i]>b.s[j]) return 1; //a > b
	if (a.s[i]<b.s[j]) return -1; //a < b
	return -2;
}

bigData bigMul(bigData a,bigData b){
	int la=a.len;
	int lb=b.len;
	int l=la+lb-1;
	bigData c;  int x=0;  c.len=l;
	memset(c.s,0,sizeof(c.s));
	for (int i=1;i<=la;i++){
		for (int j=1;j<=lb;j++){
			c.s[i+j-1]+=x+a.s[i]*b.s[j];
			c.s[i+j]+=c.s[i+j-1]/10000;
			c.s[i+j-1]%=10000;
		}
	}
	if (c.s[l+1]) c.len++;
	while (c.len>1&&c.s[c.len]==0) c.len--;
	return c;
}

void output(bigData a){
	int l=a.len,i=0;
	printf("%d",a.s[l]);
	for (i=l-1;i>0;i--){
		if (a.s[i]<10) printf("000");
		else if (a.s[i]<100) printf("00");
		else if (a.s[i]<1000) printf("0");
		printf("%d",a.s[i]);
	}
	puts("");
}

bigData bigSqrt(bigData a){
	int lc=(a.len+1)/2,i;
	bigData c;
	c.len=lc;
	memset(c.s,0,sizeof(c.s));
	for (i=lc;i>0;i--){
		int f=0;
		do{
			c.s[i]+=1000;
			f=bigCmp(a,bigMul(c,c));
			if (f==0) break;
		}
		while (f==1);
		if (f==0) break;
		c.s[i]-=1000;
		do{
			c.s[i]+=100;
			f=bigCmp(a,bigMul(c,c));
			if (f==0) break;
		}
		while (f==1);
		if (f==0) break;
		c.s[i]-=100;
		do{
			c.s[i]+=10;
			f=bigCmp(a,bigMul(c,c));
			if (f==0) break;
		}
		while (f==1);
		if (f==0) break;
		c.s[i]-=10;
		do{
			c.s[i]++;
			f=bigCmp(a,bigMul(c,c));
			if (f==0) break;
		}
		while (f==1);
		if (f==0) break;
		c.s[i]--;
	}
	return c;
}
int main(){
	bigData a,b,c;
	int tt;
	printf("how many times? ");
	cin >> tt;
	while(tt--){
		printf("give me to big number:\n");
		input(a);
		input(b);
		printf("read in two big numer:\n");
		printf("a: ");output(a);
		printf("b: ");output(b);
		printf("cmp of a and b: ");cout << bigCmp(a,b) << endl;
		c = bigMul(a,b);
		cout << "the multiplacation of a and b: c = ";
		output(c);
		c = bigSqrt(c);
		cout << "sqrt of c: ";
		output(c);
		cout << endl;
	}
	return 0;

}