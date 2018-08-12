#include<iostream>
#include<vector>
#include<string>
#include<cstdio>
#include<string.h>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<math.h>
#include<algorithm>
#include<cstdlib>
#include<stack>
#define INF 0x7fffffff
using namespace std;

int G[30][30];
int indeg[30];
int state = 0;
vector<int> res;
int n,m;  
int in[30];
void topoSort(){
	int indi[30];
	for(int i = 0;i < n;i++)
		indi[i] = indeg[i];	
	while(true){
		int dot = -1;
		for(int i = 0;i < n;i++){
			if(!indi[i]){
				dot = i;
				break;
			}
		}
		if(dot == -1) break;
		indi[dot] = -1;
		res.push_back(dot);
		for(int i = 0;i < n;i++)
			if(G[dot][i])
				indi[i]--;
	}
	if(res.size() == n) state = 1;
	for(int i = 0;i < n;i++)
		if(indi[i] > 0)
			state = 2;
}
bool detect(){
	int indi[30];
	int cnt = 0;
	for(int i = 0;i < n;i++)
		indi[i] = indeg[i];	
	for(int i = 0;i < res.size();i++){
		int u = res[i];
		cnt = 0;
		for(int i = 0;i < n;i++){
			if(!indi[i]) cnt++;
			if(cnt > 1)  return false;
		}
		indi[u] = -1;
		for(int i = 0;i < n;i++)
			if(G[u][i]) indi[i]--;
	}	
	return true;
}
int main(){
	while(cin >> n >> m){
		if(n == 1) {cout << "Sorted sequence determined after 0 relations: A." << endl;continue;}
		if(!(n||m)) break;
		string s;
		memset(G,0,sizeof(G));
		for(int i = 0;i < n;i++) indeg[i] = -1;
		state = 0;
		res.clear();
		int ok = 0;
		int index = 0;
		for(int i = 0;i < m;i++){
			cin >> s;
			if(!ok){
				int a = s[0] - 'A',b = s[2] - 'A';
				if(indeg[a] < 0) indeg[a] = 0;
				if(indeg[b] < 0) indeg[b] = 0;
				if(!G[a][b]) indeg[b]++;
				G[a][b] = 1;
				topoSort(); 
				if(state == 1)
					if(!detect()) state = 0;		
				if(state == 1){ok = 1;index = i;}
				if(state == 2){ok = 1;index = i;}
				if(!ok) res.clear();
			}
		}
		
		if(state == 1){
			cout << "Sorted sequence determined after "<<(index+1)<<" relations: ";
			for(int i = 0;i < res.size();i++)
				printf("%c",(res[i]+'A'));
			cout <<"."<< endl;	
		}
		else if(state == 2)
			cout << "Inconsistency found after "<<(index+1)<<" relations." << endl;
		else
			cout << "Sorted sequence cannot be determined." << endl;
	}
	return 0;
}
