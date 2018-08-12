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
using namespace std;

struct Point{
	int x,y;
	Point(){}
	Point(int i,int j):x(i),y(j){}
};
const int dx[8] = {-2,-2,-1,-1,1,1,2,2};
const int dy[8] = {-1,1,-2,2,-2,2,-1,1};
int p,q;
vector<Point> points,res;
bool ok;
bool visit[100][100];

bool valid(int x,int y){
	if(x < 0 || x >= p || y < 0 || y >= q) return false;
	return true;
}

void backtracking(int x,int y){
	visit[x][y] = true;
	points.push_back(Point(x,y));
	for(int i = 0;i < 8;i++){
		if(ok) return;
		int newx = x + dx[i];
		int newy = y + dy[i];
		if(visit[newx][newy] || (!valid(newx,newy))) continue;
		backtracking(newx,newy);
		visit[newx][newy] = false;
		points.pop_back();
	}
	if(!ok){
		for(int i = 0;i < p;i++)
			for(int j = 0;j < q;j++)
				if(!visit[i][j]) return;
		ok = true;
		for(int i = 0;i < points.size();i++){
			res.push_back(points[i]);
		}
	}
}

int main(){
	int n;
	int cnt = 1;
	cin >> n;
	while(n--){
		cin >> q >> p;
		ok = false;
		memset(visit,false,sizeof(visit));
		points.clear();
		res.clear();
		backtracking(0,0);
		cout << "Scenario "<<"#" << cnt++ << ":"<< endl;
		if(!ok)  cout <<"impossible"<< endl;
		else{
			for(int i = 0;i < res.size();i++){
				printf("%c%c",(res[i].x+'A'),(res[i].y+'1'));
			}
			cout << endl;
		}
		cout << endl;
	}
	return 0;
}

