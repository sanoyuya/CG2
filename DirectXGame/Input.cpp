#include "Input.h"
#include<Windows.h>
#include <dinput.h>


#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
Input::Input()
{
}

Input::~Input()
{
}

void Input::Initialize(WNDCLASSEX& w, HWND& hwnd)
{

	//DirectInput�̏�����
	IDirectInput8* directInput = nullptr;
	auto result = DirectInput8Create(w.hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	//�L�[�{�[�h�f�o�C�X�̐���
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));

	//���̓f�[�^�`���̃Z�b�g
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);//�W���`��
	assert(SUCCEEDED(result));

	//�r�����䃌�x���̃Z�b�g
	result = keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	//DISCL_FOREGROUND		��ʂ���O�ɂ���ꍇ�̂ݓ��͂��󂯕t����
	//DISCL_NONEXCLUSIVE	�f�o�C�X�����̃A�v�������Ő�L���Ȃ�
	//DISCL_NOWINKEY		Window�L�[�𖳌��ɂ���
	assert(SUCCEEDED(result));
}

void Input::Update()
{
	//�L�[�{�[�h���̎擾�J�n
	keyboard->Acquire();

	oldKey = key;

	//�S�L�[���͏�Ԃ��擾����
	keyboard->GetDeviceState(static_cast<DWORD>(key.size()), key.data());
}

bool Input::PushKey(uint8_t index)
{
	//1�������牟����Ă�
	if (key[index])
	{
		return true;
	}

	//������ĂȂ�
	return false;
}

bool Input::TriggerKey(uint8_t index)
{
	if (key[index] && !oldKey[index])
	{
		return true;
	}

	return false;

}

bool Input::ReleaseKey(uint8_t index)
{
	if (!key[index] && oldKey[index])
	{
		return true;
	}

	return false;
}