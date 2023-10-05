#pragma once

#include <easyx.h>
#include "Game.h"

#define BLOCK_WIDTH 20	// 方块宽度

// 方块类
class Block
{
public:
	Block(Game& game, const int& x = (MAP_WIDTH - 4) / 2, const int& y = 0);	// 初始化函数
	bool move(const unsigned& direction = 0);									// 移动函数，0 表示下移一格，1 表示左移一格，2 表示右移一格，当下移检测到碰撞时返回 true
	void draw() const;															// 绘制函数
	void clear() const;															// 清除函数
	void addMap() const;														// 添加方块到地图
	void rotate();																// 旋转方块，false 向左，true 向右
	bool checkCollision() const;												// 碰撞检查
	static void generateBlockData();											// 初始化方块数据
	void setPos(const int& x = (MAP_WIDTH - 4) / 2, const int& y = 0);			// 设置方块坐标
	void randType();															// 随机方块类型
	void operator=(const Block& block);											// 为 Block 赋值

private:
	int x;							// 方块 X 坐标
	int y;							// 方块 Y 坐标
	unsigned char type;				// 方块类型
	bool direction;					// 旋转方向，false 代表顺时针，true 代表逆时针
	bool block[4][4];				// 方块数组，true 表示有方块，false 表示没方块
	COLORREF color;					// 方块填充颜色
	static bool blockData[7][4][4];	// 方块数据，对象共享的资源
	Game& game;						// Game 引用对象
};