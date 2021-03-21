#pragma once
#include <vector>


class KeyBoard final
{
public:
	std::vector<bool> pressed_button;
	void keyPressEvent(int key_event);
	void keyReleaseEvent(int key_event);
};
