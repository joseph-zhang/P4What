#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;
#define MAXHASHSIZE 31250010

short head[MAXHASHSIZE*2];
int main(){
	int a,b,c,d,e,x1,x2,x3,x4,x5;
	long long res = 0;
	scanf("%d%d%d%d%d",&a,&b,&c,&d,&e);
	for(x4=-50;x4<=50;x4++){
		for(x5=-50;x5<=50;x5++){
			if(x4!=0&&x5!=0){
				int tmp = d*x4*x4*x4+e*x5*x5*x5;
				head[tmp] ++;
			}
		}
	}
	for(x1=-50;x1<=50;x1++){
		for(x2=-50;x2<=50;x2++){
			for(x3=-50;x3<=50;x3++){
				if(x1!=0&&x2!=0&&x3!=0){
					int tmp = -(a*x1*x1*x1+b*x2*x2*x2+c*x3*x3*x3);
						res += head[tmp];
				}
			}
		}
	}
	cout<<res<<endl;
	return 0;
}

