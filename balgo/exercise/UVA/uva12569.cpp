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
#define sys std::ios::sync_with_stdio(false)
#define LL long long
#define Uint unsigned int
using namespace std;
const int maxn = 16;
struct state{
	int sta,x,cnt;
	string str;
	state(){}
	state(int _sta,int _x,int _cnt,string _str):sta(_sta),x(_x),cnt(_cnt),str(_str){}
};
state inis;
bool vis[1 << maxn][maxn];
int n,m,s,t;
vector<int> G[maxn];

void bfs(){
	queue<state> q;
	vis[inis.sta][inis.x] = true;
	q.push(inis);
	while(!q.empty()){
		state temps = q.front();q.pop();
		for(int i = 0;i < n;i++){
			if(temps.sta&(1 << i)){
				for(int j = 0;j < G[i].size();j++){
					int v = G[i][j];
					if(v == temps.x)continue;
					if(temps.sta&(1 << v))continue;
					int nc = temps.sta;
					nc ^= (1 << i);
					nc |= (1 << v);
					if(!vis[nc][temps.x]){
						string strc = temps.str;
						strc = strc + (char)(i+1+'0');
						strc = strc + (char)(v+1+'0');
						state news = state(nc,temps.x,
									temps.cnt+1,strc);
						vis[nc][temps.x] = true;
						q.push(news);
					}
				}
			}
		}
		for(int i = 0;i < G[temps.x].size();i++){
			int v = G[temps.x][i];
			if(temps.sta&(1 << v))continue;
			int nc = temps.sta;
			if(!vis[nc][v]){
				string strc = temps.str;
				strc = strc + (char)(temps.x+1+'0');
				strc = strc + (char)(v+1+'0');
				state news = state(nc,v,temps.cnt+1,strc);
				vis[nc][v] = true;
				q.push(news);
				if(v == t){
					cout << news.cnt <<endl;
					string res = news.str;
					for(int j = 0;j < res.size();j+=2)
						printf("%c %c\n",res[j],res[j+1]);
					return;
				}
			}
		}
	}
	printf("-1\n");
}
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout); 
	int time;cin >> time;
	int kase = 0;
	while(time--){
		memset(vis,false,sizeof(vis));
		for(int i = 0;i < maxn;i++)G[i].clear();
		scanf("%d%d%d%d",&n,&m,&s,&t);
		s--;t--;
		inis = state();
		inis.x = s;
		int pos;
		for(int i = 0;i < m;i++){
			cin >> pos;
			inis.sta |= (1 << (pos-1));
		}
		int a,b;
		for(int i = 0;i < n-1;i++){
			scanf("%d%d",&a,&b);
			G[a-1].push_back(b-1);G[b-1].push_back(a-1);
		}
		printf("Case %d: ",++kase);
		bfs();
		if(time)cout << endl;
	}
	return 0;
}

