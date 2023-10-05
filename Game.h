#pragma once

#include <easyx.h>

#define MAP_WIDTH 10	// 地图宽度
#define MAP_HEIGHT 20	// 地图高度

// 游戏类
class Game
{
public:
	void drawMap() const;						// 绘制地图
	void drawPrompt() const;					// 绘制提示界面
	bool checkLine(const unsigned& line) const;	// 判断满行
	void clearLine();							// 清除满行

// 内联函数
public:
	// 设置地图
	void setMap(const int& x, const int& y, const bool& value)
	{
		map[x][y] = value;
	}

	// 获取地图
	const bool& getMap(const int& x, const int& y) const
	{
		return map[x][y];
	}

	// 添加游戏时间
	void addGameTime()
	{
		gameTime += 500;
	}

private:
	bool map[MAP_WIDTH][MAP_HEIGHT] = { 0 };	// 地图数组
	unsigned score = 0;							// 游戏分数
	unsigned gameTime = 0;						// 游戏时间
};

