#include <iostream>
#include <cstdio>
#include <cstring>
#include <windows.h>
#define MAXN 22
using namespace std;
int N; //行
int M; //列
int cnt; //走过的瓷砖数
char map[MAXN][MAXN];
int fx[8] = { -1,0,0,1,1,0,0,-1 }; //两个作为一组，分别表示上右下左四个方向

void DFS(int x, int y)
{
	int nextx, nexty;
	int i;
	if (map[x][y] != '@')
		map[x][y] = '$'; //先把当前格设为已访问过
	for (i = 0;i < 8;i = i + 2) //按照上右下左的顺序，朝四个方向尝试
	{
		nextx = x + fx[i];
		nexty = y + fx[i + 1];
		if (nextx < 0 || nextx >= N || nexty < 0 || nexty >= M || map[nextx][nexty] != '#')
			continue; //满足以上任一个条件，则说明此路不通，换方向再试试吧

		cnt++; //如果到达这里，则说明此处也是黑瓷砖，计数加1，并启动新的搜索
		map[nextx][nexty] = '$';
		DFS(nextx, nexty);
	}
}

void show() {
	cout << "走过的黑色瓷砖数量为：" << cnt << endl << endl;
	cout << "运动路径为：" << endl;
	for (int i = 1;i <= N;i++)
	{
		for (int j = 1;j <= M;j++)
		{
			if (map[i][j] == '$' || map[i][j] == '@')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | BACKGROUND_BLUE);//设置表示路径的的字符颜色和背景色
				cout << map[i][j];//输出变化后地图的每一行
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);//恢复正常显示
			}
			else
				cout << map[i][j];//输出变化后地图的每一行
		}
		cout << endl;
	}
}

int main()
{
	int i, j;
	int startx = 0, starty = 0; //开始位置，即@所在位置
	while (1)
	{
		cout << "请输入列数、行数以及图形：" << endl;
		cin >> M >> N;//请注意，题目的输入是先列后行！
		if (M == 0 && N == 0)
			break;
		cnt = 1; //新开始，重新置1
		memset(map, 0, sizeof(map)); //清空地图
		for (i = 0;i < N;i++) //接收输入并找到起始位置
		{
			cin >> map[i];//输入一行
			for (j = 0;j < M;j++)
			{
				if (map[i][j] == '@')
				{
					startx = i;
					starty = j;
				}
			}
		}
		DFS(startx, starty); //启动深度搜索
		show();
	}
	return 0;
}
