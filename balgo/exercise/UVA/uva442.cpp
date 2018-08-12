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
#define LL long long
using namespace std;
struct Matrix{
	int m,n;
	Matrix(){}
	Matrix(int a,int b):m(a),n(b){}
};
Matrix mats[28];
int N;
unsigned int res = 0;
int main(){
	cin >> N;
	string ss;
	for(int i = 0;i < N;i++){
		char c;
		int a,b;
		cin >> c >> a >> b;
		mats[c -'A'] = Matrix(a,b);
	}
	while(cin >> ss){
		stack<Matrix> stk;
		res = 0;bool err = false;
		for(int i = 0;i < ss.size();i++){
			if(ss[i] == ')'){
				Matrix Ma = stk.top();stk.pop();
				Matrix Mb = stk.top();stk.pop();
				if(Mb.n != Ma.m){err = true;break;}
				res += Mb.m * Mb.n * Ma.n;
				stk.push(Matrix(Mb.m,Ma.n));
			}
			else if( 'A'<= ss[i] && ss[i] <= 'Z')stk.push(mats[ss[i]-'A']);
			else continue;
		}
		if(err) cout << "error" << endl;
		else cout << res << endl;
	}
	return 0;
}
