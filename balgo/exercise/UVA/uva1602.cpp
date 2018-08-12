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
#define Uint unsigned int
using namespace std;
struct Cell{
	int x,y;
	Cell(){}
	Cell(int a,int b):x(a),y(b){}
	bool operator < (const Cell& rhs)const {
		return x < rhs.x || (x == rhs.x && y < rhs.y);
	}
};
const int maxn = 10;
const int dx[4] = {0,1,0,-1};
const int dy[4] = {1,0,-1,0};
typedef set<Cell> polyomino;
#define ForCell(c,p) for(set<Cell>::const_iterator c = (p).begin();c!= (p).end();c++)
set<polyomino> polys[maxn+2];
inline polyomino Norm(polyomino& p){
	polyomino np;
	int Minx = p.begin()->x,Miny = p.begin()->y;
	ForCell(c,p){
		Minx = min(Minx,c->x);
		Miny = min(Miny,c->y);
	}
	ForCell(c,p)
		np.insert(Cell(c->x-Minx,c->y-Miny));
	return np;	
}
inline polyomino Rotate(polyomino& p){
	polyomino rp;
	ForCell(c,p)
		rp.insert(Cell(c->y,-c->x));
	return Norm(rp);
}
inline polyomino Flip(polyomino& p){
	polyomino fp;
	ForCell(c,p)
		fp.insert(Cell(c->x,-c->y));
	return Norm(fp);
}
void insertPoly(const polyomino& pp,const Cell& cc){
	polyomino p = pp;
	Cell c = cc;
	p.insert(c);
	p = Norm(p);
	int sz = p.size();
	//detect if it is an included poly; 
	for(int i = 0;i < 4;i++){
		if(polys[sz].count(p)!= 0) return;
		p = Rotate(p);
	}
	p = Flip(p);
	for(int i = 0;i < 4;i++){
		if(polys[sz].count(p)!=0)return;
		p = Rotate(p);
	}
	//It's a new poly,insert it;
	polys[sz].insert(p);
}
int ans[maxn+2][maxn+2][maxn+2];
void preProcessing(){
	polyomino sp;
	sp.insert(Cell(0,0));
	polys[1].insert(sp);
	//generation
	for(int i = 2;i <= maxn;i++){
		for(set<polyomino>::iterator it = polys[i-1].begin();it!=polys[i-1].end();it++){
			ForCell(c,*it)
				for(int k = 0;k < 4;k++){
					Cell newc = Cell(c->x+dx[k],c->y+dy[k]);
					if(it->count(newc) == 0)insertPoly(*it,newc);
				}
		}
	}
	//fill table
	for(int i = 1;i <= maxn;i++){
		for(int j = 1;j <= maxn;j++){
			for(int k = 1;k <= maxn;k++){
				int cnt = 0;
				for(set<polyomino>::iterator it = polys[i].begin();it != polys[i].end();it++){
					int Maxx = 0,Maxy = 0;
					ForCell(c,*it){
						Maxx = max(Maxx,c->x);
						Maxy = max(Maxy,c->y);
					}
					if(min(Maxx,Maxy) < min(i,j) && max(Maxx,Maxy) < max(i,j))
						cnt++;
				}
				ans[i][j][k] = cnt;
				printf("%d,",cnt);
			}
		}
	}
}
int main(){
	freopen("output","w",stdout);
	int n,h,w;
	preProcessing();
//	while(scanf("%d %d %d",&n,&w,&h) == 3){
//		printf("%d\n",ans[n][w][h]);
//		polyomino sp;
//		sp.insert(Cell(0,0));
//		polys[1].insert(sp);
//		//generation
//		for(int i = 2;i <= n;i++){
//			for(set<polyomino>::iterator it = polys[i-1].begin();it!=polys[i-1].end();it++){
//				ForCell(c,*it)
//					for(int k = 0;k < 4;k++){
//						Cell newc = Cell(c->x+dx[k],c->y+dy[k]);
//						if(it->count(newc) == 0)insertPoly(*it,newc);
//					}
//			}
//		}
//		int cnt=  0;
//		for(set<polyomino>::iterator it = polys[n].begin();it!=polys[n].end();it++){
//			int Maxx = 0,Maxy = 0;
//			ForCell(c,*it){
//				Maxx = max(Maxx,c->x);
//				Maxy = max(Maxy,c->y);	
//			}		
//			if(min(Maxx,Maxy) < min(w,h) && max(Maxx,Maxy) < max(w,h))
//				cnt++;
//		}
//		printf("%d\n",cnt);

//	}
	return 0;
}
