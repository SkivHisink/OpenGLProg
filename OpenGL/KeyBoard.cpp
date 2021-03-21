#include <KeyBoard.h>
#include <QKeyEvent>
void KeyBoard::keyPressEvent(int key_event)
{
	if (key_event == Qt::Key_Escape && pressed_button[0] == false)
		pressed_button[0] = true;
	/*for(size_t i=1;i<pressed_button.size();++i)
	{
		if (key_event == key_map[i] && pressed_button[i] == false)
			pressed_button[i] = true;
	}*/
	if (key_event == Qt::Key_F1 && pressed_button[1] == false)
		pressed_button[1] = true;
	if (key_event == Qt::Key_PageUp && pressed_button[2] == false)
		pressed_button[2] = true;
	if (key_event == Qt::Key_PageDown && pressed_button[3] == false)
		pressed_button[3] = true;
	if (key_event == Qt::Key_R && pressed_button[4] == false)
		pressed_button[4] = true;
	if (key_event == Qt::Key_F && pressed_button[5] == false)
		pressed_button[5] = true;
	if (key_event == Qt::Key_T && pressed_button[6] == false)
		pressed_button[6] = true;
	if (key_event == Qt::Key_G && pressed_button[7] == false)
		pressed_button[7] = true;
	if (key_event == Qt::Key_Y && pressed_button[8] == false)
		pressed_button[8] = true;
	if (key_event == Qt::Key_H && pressed_button[9] == false)
		pressed_button[9] = true;
	if (key_event == Qt::Key_U && pressed_button[10] == false)
		pressed_button[10] = true;
	if (key_event == Qt::Key_J && pressed_button[11] == false)
		pressed_button[11] = true;
	if (key_event == Qt::Key_Z && pressed_button[12] == false)
		pressed_button[12] = true;
	if (key_event == Qt::Key_X && pressed_button[13] == false)
		pressed_button[13] = true;
	if (key_event == Qt::Key_W && pressed_button[15] == false)
		pressed_button[15] = true;
	if (key_event == Qt::Key_A && pressed_button[16] == false)
		pressed_button[16] = true;
	if (key_event == Qt::Key_S && pressed_button[17] == false)
		pressed_button[17] = true;
	if (key_event == Qt::Key_D && pressed_button[18] == false)
		pressed_button[18] = true;
	if (key_event == Qt::Key_Q && pressed_button[19] == false)
		pressed_button[19] = true;
	if (key_event == Qt::Key_E && pressed_button[20] == false)
		pressed_button[20] = true;
	if (key_event == Qt::Key_C)
		pressed_button[21] = !pressed_button[21];
	if (key_event == Qt::Key_V)
		pressed_button[22] = !pressed_button[22];
	if (key_event == Qt::Key_B)
		pressed_button[23] = !pressed_button[23];
	if (key_event == Qt::Key_1 && pressed_button[24] == false)
		pressed_button[24] = true;
	if (key_event == Qt::Key_2 && pressed_button[25] == false)
		pressed_button[25] = true;
	if (key_event == Qt::Key_3 && pressed_button[26] == false)
		pressed_button[26] = true;
	if (key_event == Qt::Key_4 && pressed_button[27] == false)
		pressed_button[27] = true;
	if (key_event == Qt::Key_5 && pressed_button[28] == false)
		pressed_button[28] = true;
	if (key_event == Qt::Key_6 && pressed_button[29] == false)
		pressed_button[29] = true;
	if (key_event == Qt::Key_7 && pressed_button[30] == false)
		pressed_button[30] = true;
	if (key_event == Qt::Key_8 && pressed_button[31] == false)
		pressed_button[31] = true;
	if (key_event == Qt::Key_9 && pressed_button[32] == false)
		pressed_button[32] = true;
	if (key_event == Qt::Key_0 && pressed_button[33] == false)
		pressed_button[33] = true;
	if (key_event == Qt::Key_Up && pressed_button[34] == false)
		pressed_button[34] = true;
	if (key_event == Qt::Key_Left && pressed_button[35] == false)
		pressed_button[35] = true;
	if (key_event == Qt::Key_Down && pressed_button[36] == false)
		pressed_button[36] = true;
	if (key_event == Qt::Key_Right && pressed_button[37] == false)
		pressed_button[37] = true;
	if (key_event == Qt::Key_N && pressed_button[38] == false)
		pressed_button[38] = true;
	if (key_event == Qt::Key_M && pressed_button[39] == false)
		pressed_button[39] = true;
}
void KeyBoard::keyReleaseEvent(int key_event)
{
	if (key_event == Qt::Key_F1)
		pressed_button[1] = false;
	if (key_event == Qt::Key_PageUp)
		pressed_button[2] = false;
	if (key_event == Qt::Key_PageDown)
		pressed_button[3] = false;
	if (key_event == Qt::Key_R)
		pressed_button[4] = false;
	if (key_event == Qt::Key_F)
		pressed_button[5] = false;
	if (key_event == Qt::Key_T)
		pressed_button[6] = false;
	if (key_event == Qt::Key_G)
		pressed_button[7] = false;
	if (key_event == Qt::Key_Y)
		pressed_button[8] = false;
	if (key_event == Qt::Key_H)
		pressed_button[9] = false;
	if (key_event == Qt::Key_U)
		pressed_button[10] = false;
	if (key_event == Qt::Key_J)
		pressed_button[11] = false;
	if (key_event == Qt::Key_Z)
		pressed_button[12] = false;
	if (key_event == Qt::Key_X)
		pressed_button[13] = false;
	if (key_event == Qt::Key_W)
		pressed_button[15] = false;
	if (key_event == Qt::Key_A)
		pressed_button[16] = false;
	if (key_event == Qt::Key_S)
		pressed_button[17] = false;
	if (key_event == Qt::Key_D)
		pressed_button[18] = false;
	if (key_event == Qt::Key_Q)
		pressed_button[19] = false;
	if (key_event == Qt::Key_E)
		pressed_button[20] = false;
	if (key_event == Qt::Key_1)
		pressed_button[24] = false;
	if (key_event == Qt::Key_2)
		pressed_button[25] = false;
	if (key_event == Qt::Key_3)
		pressed_button[26] = false;
	if (key_event == Qt::Key_4)
		pressed_button[27] = false;
	if (key_event == Qt::Key_5)
		pressed_button[28] = false;
	if (key_event == Qt::Key_6)
		pressed_button[29] = false;
	if (key_event == Qt::Key_7)
		pressed_button[30] = false;
	if (key_event == Qt::Key_8)
		pressed_button[31] = false;
	if (key_event == Qt::Key_9)
		pressed_button[32] = false;
	if (key_event == Qt::Key_0)
		pressed_button[33] = false;
	if (key_event == Qt::Key_Up)
		pressed_button[34] = false;
	if (key_event == Qt::Key_Left)
		pressed_button[35] = false;
	if (key_event == Qt::Key_Down)
		pressed_button[36] = false;
	if (key_event == Qt::Key_Right)
		pressed_button[37] = false;
	if (key_event == Qt::Key_N)
		pressed_button[38] = false;
	if (key_event == Qt::Key_M)
		pressed_button[39] = false;
}