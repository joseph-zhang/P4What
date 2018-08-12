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
char s[50];
char gue[50];
int bad = 0;
int n = 0;
bool guessed[26];
bool have[26];
bool failure[26];
int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	int t;
	while(cin >> t){
		if(t == -1) break;
		scanf("%s",s);
		scanf("%s",gue);
		int len1 = strlen(s);
		int len2 = strlen(gue);
		memset(have,false,sizeof(have));
		memset(guessed,false,sizeof(guessed));
		memset(failure,false,sizeof(failure));
		n = bad = 0;
		for(int i = 0;i < len1;i++){
			if(!have[s[i]-'a']){
				have[s[i]-'a'] = true;
				n++;
			}
		}
		bool ok = false;
		int shoot = 0;
		cout << "Round " << t << endl;
		for(int i = 0;i < len2;i++){
			int c = gue[i] - 'a';
			if(!have[c]){
				if(!failure[c])if(++bad > 6){ok = true;cout << "You lose." << endl;break;}
				failure[c] = true;
			}
			if(have[c] && !guessed[c]){
				if(++shoot >= n){ok = true;cout << "You win." << endl;break;}
				guessed[c] = true;
			}
		}
		if(!ok) cout << "You chickened out." << endl;
	}
	return 0;
}
