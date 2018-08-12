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

typedef struct island{
	int x,y;
	double fringel,fringer;
	
}island;
bool comp(island a,island b){
	return a.fringer < b.fringer; 
}

int main(){
	int n,d;
	int num = 0;
	while(cin >> n >> d){
		if(!(n||d)) break;
		num++;
		int flag = 0;
		island land[n];
		vector<double> point;
		for(int i = 0;i < n;i++){
			cin >> land[i].x;
			cin >> land[i].y;
			if(land[i].y > d || land[i].y < 0) flag = 1;
			double lens=  sqrt((double)(d*d - land[i].y*land[i].y));
			land[i].fringer = (double)land[i].x + lens;
			land[i].fringel = (double)land[i].x - lens;
		}
		if(flag){
			cout << "Case" << " " << num << ": " << "-1"<< endl;
			continue;
		}
		sort(land,land+n,comp);
		for(int i = 0;i < n;i++){
			if(point.empty()){
				point.push_back(land[i].fringer);
				continue;
			}
			double pre = point.back();
			if(pre < land[i].fringel)
				point.push_back(land[i].fringer);
		}
		cout << "Case" << " " << num << ": " << point.size() << endl;
	}
	return 0;
}


