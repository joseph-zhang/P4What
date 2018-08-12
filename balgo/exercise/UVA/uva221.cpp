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
const int maxn = 105; 
struct House{
	double x,y,w,d,h;
	int index;
	House(){}
	House(int id,double xs,double ys,double ws,double ds,double hs){
		x = xs;y = ys;
		w = ws;d = ds;
		h = hs;index = id;
	}
	bool operator < (const House& rhs) const {
		return ((x < rhs.x)||(x == rhs.x && y < rhs.y));
	}
};
House houses[maxn];
int N;
vector<double> coord;
bool cover(House& hs,int mx){
	double xs = hs.x,ws = hs.w;
	if((xs <= mx) && (xs+ws >= mx))return true;
	return false;
}
bool visible(House& hs,int mx){
	if(!cover(hs,mx)) return false;
	for(int i = 0;i < N;i++){
		House& hm = houses[i];
		if(cover(hm,mx) && hm.y < hs.y && hm.h >= hs.h)
			return false;
	}
	return true;
}
int main(){
	int t = 0;
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	while(cin >> N){
		if(!N) break;
		if(t)cout<< endl;
		coord.clear();
		vector<int> res;
 		double xs,ys,ws,ds,hs;
		for(int i = 0;i < N;i++){
			scanf("%lf%lf%lf%lf%lf",&xs,&ys,&ws,&ds,&hs);
			houses[i] = House(i+1,xs,ys,ws,ds,hs);
			coord.push_back(xs);
			coord.push_back(xs+ws);
		}
		sort(houses,houses+N);
		sort(coord.begin(),coord.end());
		int M = unique(coord.begin(),coord.end()) - coord.begin();
		for(int i = 0;i < N;i++){
			bool isvis = false;
			for(int j = 0;j < M-1;j++){
				double mx = (coord[j]+coord[j+1])/2;
				if(visible(houses[i],mx)){isvis = true;break;}
			}
			if(isvis) res.push_back(houses[i].index);
		}
		printf("For map #%d, the visible buildings are numbered as follows:\n",++t);
		for(int i = 0;i < res.size()-1;i++)
			cout << res[i] << " ";
		cout << res[res.size()-1] << endl;
	}
	return 0;
}
