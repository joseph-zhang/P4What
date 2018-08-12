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
struct Per{
	int B,J;
	Per(){}
	Per(int b,int j):B(b),J(j){}
	bool operator < (const Per& x) const{
		return J > x.J;
	} 
};
int N;

int main(){
	int t = 0;
	while(cin >> N){
		if(!N)break;t++;
		vector<Per> vec;
		for(int i = 0;i < N;i++){
			int b,j;
			scanf("%d %d",&b,&j);
			vec.push_back(Per(b,j));
		}	
		sort(vec.begin(),vec.end());
		int beg = 0,res = 0;
		for(int i = 0;i < N;i++){
			beg += vec[i].B;
			res = max(res,beg+vec[i].J);
		}
		printf("Case %d: %d\n",t,res);
	}
	return 0;
}
