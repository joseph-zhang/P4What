
/**
*    LIS(�����������)��LCS(�����������)������������ΪDP������չʾ.
*    LIS�ǻ���DP�ĺ�����,Ҳ������������,��Ҫ��������ת�Ʒ��̵���ʽ.
*    ������:���е��д�������ȡһЩ��Ԫ�����ɵ�������.(ע����Ӵ�����)
*    ������Ҫ����DP�Ľⷨ,ͬʱ����һЩ�����Ľ�.
*	 ��ʽ��Ҫ��д,��ҪΪ�����ֳ�˼��.
*/

/**
*    �ҳ�LIS�ĳ���:DP O(n^2)
*    length(n) =  max  { length(i) + 1 : if s[i] < s[n] }  0��i��n-1
*    length(n)����λ��nΪ��β��LIS����.
*/
int s[5];		// sequence
int length[5];	// �� x ���ֵ�� s[0...x] �� LIS �L��

void LIS(){
	// ��ʼ����ÿһ�����ֱ�������L�Ȟ�һ�� LIS��
	for (int i=0; i<5; i++) length[i] = 1;

	for (int i=0; i<5; i++)
		// �ҳ� s[i] �ܽ�����Щ�������棬
		// ���ǿ��Խӣ��L�Ⱦ����ӡ�
		for (int j=0; j<i; j++)
			if (s[j] < s[i])
				length[i] = max(length[i], length[j] + 1);

	// length[] ֮������ֵ���� LIS ���L�ȡ�
	int n = 0;
	for (int i=0; i<5; i++)
		n = max(n, length[i]);
	cout << "LIS���L����" << n;
}
/**
*    �ҳ�LIS�ĳ���:Robinson-Schensted-Knuth Algorithm,˼����̰��.O(nlogn)
*	 ����̰�ĵ�˼��,��ַ���������Ǳ��.
*    ע��ִ�����ֻ�ܵõ�LIS�ĳ���,v�е����в���LIS
*/
int LIS(vector<int>& s){
	// ���ò��Д������
	if (s.size() == 0) return 0;

	// �ȷ���һ�����֣�������� v.back() ���e��
	vector<int> v;
	v.push_back(s[0]);

	for (int i = 1; i < s.size(); ++i){
		int n = s[i];
		if (n > v.back())
			v.push_back(n);
		else
			*lower_bound(v.begin(), v.end(), n) = n;
	}
	return v.size();
}
/**
*    �ҳ�һ��LIS:ֻҪ����һ��pre�����¼�����Ǹ�λ�ý�����.
*    ������Ȼ��DP,������ǲ�����һ��ת�Ʒ���.
*/
int s[5];
int length[5];
int prev[5]; // prev[x] ӛ� s[x] �ǽ����Ă���������
void LIS(){
	for (int i=0; i<5; i++) length[i] = 1;
	memset(pre,-1,sizeof(pre));
	
	for (int i=0; i<5; i++){
		for (int j=i+1; j<5; j++)
			if (s[i] < s[j])
				if (length[i] + 1 > length[j]){
					length[j] = length[i] + 1;
					// s[j] ���� s[i] ����
					prev[j] = i;
				}
	}
	int n = 0, pos = 0;
	for (int i=0; i<5; i++){
		if (length[i] > n){
			n = length[i];
			pos = i;
		}
	}
	trace(pos);	// ӡ��һ��LIS
}
void trace(int i){
	if (prev[i] != -1) trace(prev[i]);
	cout << seq[i] << ' ';
}

/**
*    �ҳ�LIS�ĳ���:DP O(NL)
*    ��������ǰ�LIS���L���OӋ춠�B����,�����B������һ���S��,��B���탦��LIS�ĽYβ���֡�
*    ����˼��������Robinson-Schensted-Knuth Algorithm�ĸ���.
*    f(n, l) =  min( f(n-1, l), s[n] ) :if f(n-1, l-1) < s[n] 
*    f(n, l): ��0헵���n헣��L�Ȟ�l������������,������С�ĽYβ��ֵ.
*    ����ʵ����ʹ���˹������������Ч��,�����˶�ά����.
*/
const int N = 10;
int s[N+1];
int array[N+1];	// ����������

int LIS(){
	for (int i=1; i<=N; ++i) array[i] = INF;
	array[0] = -INF;

	int n = 0;	// ĿǰLIS���L��
	for (int i=1; i<=N; ++i){
		if (array[n] < s[i]) n++;	// LIS���L��
		for (int j=n; j>0; --j)	// ����Ŀǰ��LIS�L�ȼ���
			if (array[j-1] < s[i])
				array[j] = min(array[j], s[i]);
	}
	return n;
}

