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

int main(){
	int s,d;
	while(cin >> s >> d){
		int val = -1;
		if(d > 4*s) val = 10*s-2*d;
		else if(2*d > 3*s) val = 8*s-4*d;
		else if(3*d > 2*s) val = 6*s-6*d;
		else if(4*d > s) val = 3*s-9*d;
		if(val > 0)
			cout << val << endl;
		else
			cout << "Deficit" << endl;
	}
	return 0;
}
