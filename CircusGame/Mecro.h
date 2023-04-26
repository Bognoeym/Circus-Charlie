#pragma once

enum TITLE
{
	TITLE_START,
	MENU = 0,
	SELECT1,
	SELECT2,
	SELECT3,
	SELECT4,
	TITLE_BM,
	STAR1,
	STAR2,
	STAR3,
	TITLE_POINT,
	TITLE_END
};

enum BACKGROUND
{
	BG_START,
	TRACK = 0,
	DECO,
	CROWD1,
	CROWD2,
	FINISH,
	MITER,
	BG_END
};

enum PLAYER
{
	P_START,
	WALK1 = 0,
	WALK2,
	JUMP,
	END1,
	END2,
	DIE,
	P_END
};

enum OBSTACLE
{
	OB_START,
	FIRE1 = 0,
	FIRE2,
	MINIRING_LEFT,
	MINIRING_RIGHT,
	LEFTRING1,
	RIGHTRING1,
	LEFTRING2,
	RIGHTRING2,
	CASH,
	OB_END
};

enum INTERFACE
{
	INT_START,
	INFOMATION = 0,
	LIFE,
	INT_END
};