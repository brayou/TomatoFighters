#pragma once
class EventHandler
{
public:
	EventHandler(void);
	~EventHandler(void);
	int mouseLeftX;
	int	mouseRightX;
	int	mouseleftY;
	int	mouseRightY;
	enum KEYS {space, what};
	bool keySwitch [1];
};

