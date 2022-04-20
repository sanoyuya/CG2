#pragma once
#include<DirectXMath.h>
#include<Windows.h>
#include <dinput.h>
#include<array>

class Input
{
public:
	Input();
	~Input();
	void Initialize(WNDCLASSEX& w, HWND& hwnd);
	void Update();
	bool PushKey(uint8_t index);
	bool TriggerKey(uint8_t index);
	bool ReleaseKey(uint8_t index);
private:

	//�L�[�{�[�h�f�o�C�X
	IDirectInputDevice8* keyboard = nullptr;

	//�S�L�[���͏�ԋL��
	std::array<BYTE, 256> key = {};

	//1�t���[���O�̃L�[���͏�ԋL�^
	std::array<BYTE, 256> oldKey = {};

	std::array<BYTE, 256> frameKey = {};

};

