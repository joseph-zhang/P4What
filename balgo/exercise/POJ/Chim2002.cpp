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
struct Point{
	int x,y;
	Point(){}
	Point(int num1,int num2):x(num1),y(num2){}
}points[2001];
int hash[2001<<5];
int next[2001];
int N;
bool cmp(Point p1,Point p2){
	if(p1.y < p2.y) return true;
	if(p1.y == p2.y && p1.x < p2.x) return true;
	return false;
}
bool find(int x,int y){
	int val = abs(x+y);
	for(int i = hash[val];i != -1;i = next[i])
		if(points[i].x == x && points[i].y == y)
			return true;
	return false;
}
int main(){
	while(cin >> N){
		if(!N) break;
		int res = 0;
		for(int i = 0;i <N;i++){
			int x,y;
			scanf("%d %d",&x,&y);
			points[i] = Point(x,y);
		}
		sort(points,points+N,cmp);
		memset(hash,-1,sizeof(hash));
		memset(next,-1,sizeof(next));
		for(int i = 0;i < N;i++){
			int val = abs(points[i].x+points[i].y);
			next[i] = hash[val];
			hash[val] = i;
		}
		for(int i = 0;i < N;i++){
			for(int j = i+1;j < N;j++){
				int ux,uy,vx,vy;
				ux = points[i].x+(points[i].y - points[j].y);
				uy = points[i].y-(points[i].x - points[j].x);
				vx = points[j].x+(points[i].y - points[j].y);
				vy = points[j].y-(points[i].x - points[j].x);
				if(find(ux,uy)&&find(vx,vy)) res++;
			}
		}
		printf("%d\n",res/2);
	}
	return 0;
}
