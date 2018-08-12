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
#define sys std::ios::sync_with_stdio(false);
#define LL long long
using namespace std;
struct state{
	int x,y,direct;
	state(){}
	state(int x1,int y1,int dir):x(x1),y(y1),direct(dir){}
};
const char directions[6] = "NESW";
const char turns[6] = "FLR";
const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};
bool visit[10][10][5];
bool canTurn[10][10][5][4];
state pa[10][10][5];
state start;
int xbegin,ybegin;
int xend,yend;
inline int getDir(char temp){return (strchr(directions,temp) - directions);}
inline int getTurn(char temp){return (strchr(turns,temp) - turns);}
bool valid(int x,int y){
	if(x > 9 || x <= 0 || y > 9 || y <= 0)return false;
	else return true;
}
state Turn(state st,int tw){
	state v;
	int xs = st.x,ys = st.y;
	int dirs = st.direct;	
	int newdir = 0;
	if(tw == 1)newdir = (dirs+3)%4;
	else if(tw == 2)newdir = (dirs+1)%4; 
	else newdir = dirs;
	v.x = xs+dx[newdir];
	v.y = ys+dy[newdir];
	v.direct = newdir;
	return v;
}
void pulls(state u){
	vector<state> vec;
	for(;;){
		vec.push_back(u);
		if(u.x == xbegin && u.y == ybegin && 
			u.direct == start.direct){
			break;
		}
		u = pa[u.x][u.y][u.direct];
	}
	int cnt = 0;
	for(int i = vec.size()-1;i >= 0;i--){
		if(++cnt > 10){cout << endl;cnt = 1;}
		printf(" (%d,%d)",vec[i].x,vec[i].y);
	}
	cout << endl;
}
void solve(){
	queue<state> q;
	visit[start.x][start.y][start.direct] = true;
	state ms = Turn(start,start.direct);
	pa[ms.x][ms.y][ms.direct] = start;
	q.push(ms);
	visit[ms.x][ms.y][ms.direct] = true;
	while(!q.empty()){
		state u = q.front();q.pop();
		if(u.x == xend && u.y == yend){pulls(u);return;}
		for(int i = 0;i < 3;i++){
			state v = Turn(u,i);
			if(canTurn[u.x][u.y][u.direct][i] &&
				(!visit[v.x][v.y][v.direct]) && valid(v.x,v.y)){
				q.push(v);
				visit[v.x][v.y][v.direct] = true;
				pa[v.x][v.y][v.direct] = u;
			}
		}
	}
	cout << "No Solution Possible" << endl;
}

int main(){
	while(cin >> xbegin){
		memset(visit,false,sizeof(visit));
		memset(canTurn,false,sizeof(canTurn));
		int a,b;
		string s;
		cin >> ybegin >> s;
		start = state(xbegin,ybegin,getDir(s[0]));
		cin >> xend >> yend;
		for(;;){
			cin >> a;
			if(!a)break;
			cin >> b;
			for(;;){
				cin >> s;
				if(s[0] == '*')break;
				int dirs = getDir(s[0]);
				for(int i = 1;i < s.size();i++){
					int turs = getTurn(s[i]);
					canTurn[a][b][dirs][turs] = true;
				}
			}
		}
		solve();
	}
	return 0;
}
