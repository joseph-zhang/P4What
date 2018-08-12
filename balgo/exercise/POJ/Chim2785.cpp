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
struct Node{
	int val,num,next;
	Node(){}
	Node(int v,int n,int nex):val(v),num(n),next(nex){}
};
const int HS = 37777773;
int A[4200],B[4200],C[4200],D[4200];
int head[HS];
Node nodes[16200000];
int np = 0;
int N;
int main(){
	memset(head,-1,sizeof(head));
	cin >> N;
	for(int i = 0;i < N;i++){
		int c;
		scanf("%d",&c);A[i] = c;
		scanf("%d",&c);B[i] = c;
		scanf("%d",&c);C[i] = c;
		scanf("%d",&c);D[i] = c;	
	}
	for(int i = 0;i < N;i++){
		for(int j = 0;j < N;j++){
			int med = abs(A[i]+B[j])%HS;
			int idx;
			for(idx = head[med];idx != -1;idx = nodes[idx].next){
				if(nodes[idx].val == A[i]+B[j]){
					nodes[idx].num++;
					break;
				}
			}
			if(idx == -1){
				nodes[np] = Node(A[i]+B[j],1,head[med]);
				head[med] = np++;
			}
		}
	}
	int res = 0;
	for(int i = 0;i < N;i++){
		for(int j = 0;j < N;j++){
			int med = abs(-C[i]-D[j])%HS;
			for(int idx = head[med];idx!=-1;idx = nodes[idx].next){
				if(nodes[idx].val == (-C[i]-D[j])){
					res+=nodes[idx].num;
					break;
				}
			}
		}
	}		
	cout << res << endl;
	return 0;
}
