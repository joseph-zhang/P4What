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
const int acdex[7] = {0,2,6,11,15,20,22};
const int bcdex[7] = {1,3,8,12,17,21,23};
const int hrdex[7] = {4,5,6,7,8,9,10};
const int grdex[7] = {13,14,15,16,17,18,19};
const int edex[8] = {6,7,8,11,12,15,16,17};
char rot[30];
char input[30];
char res[100];
int maxd;
void rotate(char op){
	int temp = 0;
	if(op == 'A'){
		temp = rot[acdex[0]];
		for(int i = 1;i < 7;i++)
			rot[acdex[i-1]] = rot[acdex[i]];
		rot[acdex[6]] = temp;
	}
	else if(op == 'B'){
		temp = rot[bcdex[0]];
		for(int i = 1;i < 7;i++)
			rot[bcdex[i-1]] = rot[bcdex[i]];
		rot[bcdex[6]] = temp;	
	}
	else if(op == 'C'){
		temp = rot[hrdex[6]];
		for(int i = 5;i >= 0;i--)
			rot[hrdex[i+1]] = rot[hrdex[i]];
		rot[hrdex[0]] = temp;
	}
	else if(op == 'D'){
		temp = rot[grdex[6]];
		for(int i = 5;i >= 0;i--)
			rot[grdex[i+1]] = rot[grdex[i]];
		rot[grdex[0]] = temp;	
	}
	else if(op == 'E'){
		temp = rot[bcdex[6]];
		for(int i = 5;i >= 0;i--)
			rot[bcdex[i+1]] = rot[bcdex[i]];
		rot[bcdex[0]] = temp;
	}
	else if(op == 'F'){
		temp = rot[acdex[6]];		
		for(int i = 5;i >= 0;i--)
			rot[acdex[i+1]] = rot[acdex[i]];
		rot[acdex[0]] = temp;
	}
	else if(op == 'G'){
		temp = rot[grdex[0]];	
		for(int i = 1;i < 7;i++)
			rot[grdex[i-1]] = rot[grdex[i]];
		rot[grdex[6]] = temp;
	}
	else{
		temp = rot[hrdex[0]];
		for(int i = 1;i < 7;i++)
			rot[hrdex[i-1]] = rot[hrdex[i]];	
		rot[hrdex[6]] = temp;
	}
}
void rotateBack(char k){
	if(k == 'A') rotate('F');
	else if(k == 'B') rotate('E');
	else if(k == 'C')rotate('H');
	else if(k == 'D')rotate('G');
	else if(k == 'E')rotate('B');
	else if(k == 'F')rotate('A');
	else if(k == 'G')rotate('D');
	else rotate('C');
}
bool judge(){
	for(int i = 0;i < 8;i++)
		if(rot[edex[i]] != rot[edex[0]]) return false;
	return true;
}
int diff(char k){
	int cnt = 0;
	for(int i = 0;i < 8;i++)
		if(rot[edex[i]] != k) cnt++;
	return cnt;
}
inline int h(){
	return min(min(diff('1'),diff('2')),diff('3'));
}
bool IDAs(int d){
	if(judge()){
		res[d] = '\0';
		printf("%s\n",res);
		return true;
	}
	if(h() > maxd-d)return false;
	for(int i = 0;i < 8;i++){
		char k = i+'A';
		res[d] = k;
		rotate(k);
		if(IDAs(d+1))return true;
		rotateBack(k);
	}
	return false;
}
int solve(){
	memcpy(rot,input,sizeof(input));
	if(judge())return -1;	
	for(maxd = 1;maxd <= 1000;maxd++){
		memcpy(rot,input,sizeof(input));
		if(IDAs(0))return maxd;
	}
	return 1001;
}
int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	while(cin >> input[0]){
		if(input[0]=='0')break;
		for(int i = 1;i < 24;i++)
			cin >> input[i];
		int ans = INF;
		ans = solve();
		if(ans == -1) printf("No moves needed\n");
		cout << rot[6] << endl;
	}
	return 0;
}
