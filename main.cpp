/*
*	程序：有趣小游戏之俄罗斯方块
*	作者：Qt小徐
*	编译环境：Visual Studio 2022 + EasyX_20220901
*	最后修改：2023 年 4 月 5 日
*/


#include "Block.h"
#include "Game.h"
#include <ctime>
#include <iostream>

int main()
{
	SetWindowText(initgraph(350, 440), L"俄罗斯方块");

	// 设置绘图颜色
	setbkcolor(WHITE);
	cleardevice();
	setlinecolor(BLACK);

	// 生成游戏界面和数据
	srand(time(NULL));
	Block::generateBlockData();

	Game game;
	game.drawMap();
	game.drawPrompt();

	Block b(game);
	Block nextBlock(game, 11, 2);	// 下一方块
	clock_t start = 0;				// 时钟开始时间
	clock_t end;					// 时钟结束时间

	ExMessage msg;

	nextBlock.draw();

	// 游戏循环
	BeginBatchDraw();
	while (true)
	{
		b.clear();
		clearrectangle(20, 20, 220, 420);
		game.drawMap();

		// 按键按下
		while (peekmessage(&msg, EX_KEY) && msg.message == WM_KEYDOWN)
		{
			switch (msg.vkcode)
			{
				// 上键旋转
			case 'W':
			case VK_UP:
				b.rotate();
				break;

				// 下键加速下落
			case 'S':
			case VK_DOWN:
				if (b.move())
				{
					// 重新设置方块
					b.addMap();
					b = nextBlock;
					b.setPos();
					nextBlock.clear();
					nextBlock.setPos(11, 2);
					nextBlock.randType();
					nextBlock.draw();

					// 如果方块刚刚生成却发生了碰撞，说明游戏结束
					if (b.checkCollision())
					{
						MessageBox(GetHWnd(), L"游戏结束！", L"提示", MB_ICONWARNING);
						goto exit;
					}
				}
				break;

				// 左键移动
			case 'A':
			case VK_LEFT:
				b.move(1);
				break;

				// 右键移动
			case 'D':
			case VK_RIGHT:
				b.move(2);
				break;

				// Esc 键退出程序
			case VK_ESCAPE:
				goto exit;
				break;
			}
		}

		// 判断每过了 500 毫秒方块下移一格
		end = clock();
		if (end - start >= 500)
		{
			if (b.move())
			{
				// 重新设置方块
				b.addMap();
				b = nextBlock;
				b.setPos();
				nextBlock.clear();
				nextBlock.setPos(11, 2);
				nextBlock.randType();
				nextBlock.draw();

				// 如果方块刚刚生成却发生了碰撞，说明游戏结束
				if (b.checkCollision())
				{
					MessageBox(GetHWnd(), L"游戏结束！", L"提示", MB_ICONWARNING);
					goto exit;
				}
			}
			start = clock();
			game.addGameTime();
		}
		b.draw();
		game.clearLine();
		FlushBatchDraw();	// 刷新缓冲区
		Sleep(50);			// 每 50 毫秒接收一次按键
	}

exit:
	EndBatchDraw();

	closegraph();
	return 0;
}