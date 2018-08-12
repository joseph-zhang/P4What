#include<iostream>
#include<vector>
#include<string.h>
#include<cstdio>
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
#define INF 0x7fffffff
#define sys std::ios::sync_with_stdio(false);
#define LL long long
using namespace std;
bool image[34][34];
char s[5000];
int res,T;
void analog(char *s,int& p,int r,int c,int w){
	char cha = s[p++];
	if(cha == 'p'){
		analog(s,p,r,c+w/2,w/2);
		analog(s,p,r,c,w/2);
		analog(s,p,r+w/2,c,w/2);
		analog(s,p,r+w/2,c+w/2,w/2);
		//cout << "orz" << endl;
	}
	else if(cha == 'f'){
		for(int i = r;i < r+w;i++)
			for(int j = c;j < c+w;j++)
				if(!image[i][j]){image[i][j] = true;res++;}
		//cout << "orz" << endl;
	}
}
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin >> T;
	while(T--){
		memset(image,false,sizeof(image));
		res = 0;
		for(int i = 0;i < 2;i++){
			scanf("%s",s);
			int p = 0;
			analog(s,p,0,0,32);
			//cout << "orz" << endl;
		}
		printf("There are %d black pixels.\n",res);
	}
	return 0;
}

