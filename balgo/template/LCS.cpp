/**
*    LIS和LCS经常被用来作为DP的例子展示.
*    LCS(s1, s2) =
*         { max( LCS(sub1, s2), LCS(s1, sub2) ) , when e1 != e2
*         { LCS(sub1, sub2) + e1                , when e1 == e2
*    逐步削减尾端元素,将问题规模缩减以推得解.
*    一个经典的应用是最小回文代价,只需要求出原串和其逆串的LCS长度然后再用原串长度减去即可.
*/


/**
*    找出LCS的长度:DP 
*    二維数组array[i][j]是递推数组, 代表"s1前i個元素"和"s2前j個元素"的LCS長度。
*/
// 为了方便起见,從数组的第1格開始存入序列。
int s1[7+1] = {0, 2, 5, 7, 9, 3, 1, 2};
int s2[5+1] = {0, 3, 5, 3, 2, 8};
int array[7+1][5+1];	// DP表格

void LCS(){
	// 初始化：當s1或s2是空集合，則LCS是空集合。
	for (int i=0; i<=s1_length; i++) array[i][0] = 0; //S2为空
	for (int j=0; j<=s2_length; j++) array[0][j] = 0; //S1为空
	//DP的过程
	for (int i=1; i<=s1_length; i++){
		for (int j=1; j<=s2_length; j++)
			if (s1[i] == s2[j])
				array[i][j] = array[i-1][j-1] + 1;
			else
				array[i][j] = max(array[i-1][j],array[i][j-1]);
	}
	cout << "LCS的長度是" << array[s1_length][s2_length];
}
/**
*    找出一个LCS:记忆接续路,仍然用DP
*    使用一個二維数组，記錄每一格的結果是從哪一格而來.
*    往回追溯，每當發現某一格array[i][j]是由array[i-1][j-1] + 1而來，就印出s1[i](也是s2[j])
*    下述程式用汉字表示方向用以说明,实际可以赋值来代表,如： 左:1,右:2,左上:0; 
*/
int array[7+1][5+1];
int prev[7+1][5+1];	// 記錄每一格的的結果是從哪一格而來

void LCS(){
	for (int i=0; i<=s1_length; i++) array[i][0] = 0;
	for (int j=0; j<=s2_length; j++) array[0][i] = 0;

	for (int i=1; i<=s1_length; i++){
		for (int j=1; j<=s2_length; j++)
			if (s1[i] == s2[j]){
				array[i][j] = array[i-1][j-1] + 1;
				prev[i][j] = 左上方;
			}else{
				if (array[i-1][j] < array[i][j-1]){
					array[i][j] = array[i][j-1];
					prev[i][j] = 左方;
				}
				else{
					array[i][j] = array[i-1][j];
					prev[i][j] = 上方;
				}
			}
	}
	cout << "LCS的長度是" << array[s1_length][s2_length];
	cout << "LCS是";
	print_LCS(s1_length, s2_length);
}
void print_LCS(int i, int j){
	// 第一個或第二個序列為空集合就停止
	if (i==0 || j==0) return;
	if (prev[i][j] == 左上方){
		print_LCS(i-1, j-1);
		cout << s1[i];	// 印出LCS的元素
	}
	else if (prev[i][j] == 上方) print_LCS(i-1, j);
	else if (prev[i][j] == 左方) print_LCS(i, j-1);
}

/**
*    若只需要拿到LCS的长度,可以考虑使用滚动数组来加速.
*    二维阵列只需一维即可.不过需要每次记录一下左上方的格子的值.
*/
int array[5+1];
int mem[5+1];
void LCS(){
	for (int i=0; i<=s2_length; i++) array[i] = 0;
	for (int i=1; i<=s1_length; i++){
		memcpy(mem,array,sizeof(array));
		for (int j=1; j<=s2_length; j++)
			if (s1[i] == s2[j]) array[j] = mem[j-1] + 1;
			else array[j] = max(array[j],array[j-1]);
	}
	cout << "LCS的長度是" << array[s2_length] << endl;
}