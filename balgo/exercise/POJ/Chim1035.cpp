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
#define INF 0x7fffffff
#define LL long long 
#define sys std::ios::sync_with_stdio(false);
using namespace std;
char str[10005][20];
char s[20];
int cnt = 0;

bool check(char* s1,char* s2){
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	int p = 0;
	if(len1 == len2){
		while(s1[p] == s2[p])p++;
		while(++p < len1)
			if(s1[p]!= s2[p]) return false;
	}
	else if(len1 == len2+1){
		while(s1[p] == s2[p])p++;
		while(++p < len1)
			if(s1[p] != s2[p-1]) return false;
	}
	else if(len1 == len2-1){
		while(s1[p] == s2[p])p++;
		while(++p < len2)
			if(s1[p-1] != s2[p]) return false;
	}
	else return false;
	return true;
}
int main(){
	while(scanf("%s",str[cnt]) && str[cnt++][0]!='#');
	cnt--;
	while(scanf("%s",s) && s[0]!='#'){
		bool ok = false;
		for(int i = 0;i < cnt;i++)
			if(!strcmp(str[i],s)){ok =true;break;}
		if(ok) printf("%s is correct",s);
		else{
			printf("%s:",s);
			for(int i = 0;i < cnt;i++)
				if(check(str[i],s))
					printf(" %s",str[i]);
		}
		cout << endl;
	}
	return 0;
}

