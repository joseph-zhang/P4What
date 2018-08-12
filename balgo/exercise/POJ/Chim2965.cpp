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
using namespace std;

int ref[4][4];
int minc = 36;
int flag[4][4];
int record[4][4];

void trans(int s){
	int x = s/4;
	int y = s%4;
	for(int i = 0;i < 4;i++){
		ref[i][y] = !ref[i][y];	
		ref[x][i] = !ref[x][i];
	}
	ref[x][y] = !ref[x][y];
}
bool complete(){
	for(int i = 0;i < 4;i++)
		for(int j = 0;j < 4;j++)
			if(ref[i][j] == 1)
				return false;
	return true;
}
void backtracking(int s,int cnt){
	if(complete()){
		minc = min(minc,cnt);
		memcpy(record,flag,sizeof(flag));
		return;
	}	
	if(s>=16) return;
	backtracking(s+1,cnt);
	trans(s);
	flag[s/4][s%4] = 1;
	backtracking(s+1,cnt+1);
	trans(s);
	flag[s/4][s%4] = 0;
}
int main(){
	memset(flag,0,sizeof(flag));
	memset(record,0,sizeof(record));
	for(int i =0;i < 4;i++){
		for(int j = 0;j < 4;j++){
			char c;
			cin >> c;
			if(c =='+') ref[i][j] = 1;
			if(c == '-') ref[i][j] = 0;
		}
	}
	backtracking(0,0);
	cout << minc << endl;
	for(int i = 0;i < 4;i++)
		for(int j = 0;j < 4;j++)
			if(record[i][j])
				cout << i+1 << " " << j+1 << endl;
	return 0;	
}
