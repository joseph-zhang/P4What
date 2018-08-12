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
struct status{
	int cura,curb;
	string act;
	status(){}
	status(int a,int b,string s):cura(a),curb(b),act(s){}
};
string op[7] = {"-1","FILL(1)","FILL(2)","DROP(1)","DROP(2)","POUR(1,2)","POUR(2,1)"};
bool lookup[102][102];
int maxa,maxb,C;

inline void print_solution(status& res){
	int sz = res.act.size();
	printf("%d\n",sz);
	for(int i = 0;i < sz;i++)
		cout << op[res.act[i]-'0'] << endl;
}
bool solve(){
	queue<status> q;
	status beg = status(0,0,"");
	q.push(beg);
	lookup[0][0] = true;
	while(!q.empty()){
		status cur = q.front();q.pop();
		status newstatus;
		if(cur.cura == C || cur.curb == C){ //res
			print_solution(cur);
			return true;
		}
		if(cur.cura < maxa){ //FILL(1)
			newstatus = status(maxa,cur.curb,cur.act+"1");
			if(!lookup[maxa][cur.curb]){
				q.push(newstatus);
				lookup[maxa][cur.curb] = true;
			}
		}
		if(cur.curb < maxb){ //FILL(2)
			newstatus = status(cur.cura,maxb,cur.act+"2");
			if(!lookup[cur.cura][maxb]){
				q.push(newstatus);
				lookup[cur.cura][maxb] = true;	
			}					
		}
		if(cur.cura > 0){ //DROP(1)
			newstatus = status(0,cur.curb,cur.act+"3");
			if(!lookup[0][cur.curb]){
				q.push(newstatus);
				lookup[0][cur.curb] = true;
			}
		}
		if(cur.curb > 0){ //DROP(2)
			newstatus = status(cur.cura,0,cur.act+"4");
			if(!lookup[cur.cura][0]){
				q.push(newstatus);
				lookup[cur.cura][0] = true;
			}
		}
		if(cur.cura > 0 && cur.curb != maxb){ //POUR(1,2)
			int dif = min(cur.cura,maxb-cur.curb);
			newstatus = status(cur.cura-dif,cur.curb+dif,cur.act+"5");
			if(!lookup[cur.cura-dif][cur.curb+dif]){
				q.push(newstatus);
				lookup[cur.cura-dif][cur.curb+dif] = true;
			}
		}
		if(cur.cura != maxa && cur.curb > 0){ //POUR(2,1)
			int dif = min(maxa-cur.cura,cur.curb);
			newstatus = status(cur.cura+dif,cur.curb-dif,cur.act+"6");
			if(!lookup[cur.cura+dif][cur.curb-dif]){
				q.push(newstatus);
				lookup[cur.cura+dif][cur.curb-dif] = true;
			}
		}
	}
	return false;
}
int main(){
	while(cin >> maxa >> maxb >> C){
		memset(lookup,false,sizeof(lookup));
		if(!solve())printf("impossible\n");
	}
	return 0;
}
