#include "Input.h"
//#define DIRECTINPUT_VERSION 0x0800	//DirectInput�̃o�[�W�����w��
#include<dinput.h>
#include<DirectXMath.h>
using namespace DirectX;

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

void Input::Initialize(HWND hwnd, WNDCLASSEX w){//������
	//DirectInput�̏�����
	result = DirectInput8Create(w.hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	//�L�[�{�[�h�f�o�C�X�̐���
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));

	
	//���̓f�[�^�`���̃Z�b�g
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);//�W���`��
	assert(SUCCEEDED(result));

	//�r�����䃌�x���̃Z�b�g
	result = keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
}

void Input::Update() {//�X�V����
	for (int i = 0; i < _countof(oldkey); i++) {
		oldkey[i] = key[i];
	}
	//�L�[�{�[�h���̎擾�J�n
	keyboard->Acquire();
	keyboard->GetDeviceState(sizeof(key), key);
}

bool Input::TriggerPush(int keyName) {//�������u��
	return key[keyName] && !oldkey[keyName];
}

bool Input::KeepPush(int keyName) {//������Ă����
	return key[keyName];
}

bool Input::TriggerRelease(int keyName) {//�����ꂽ�u��
	return !key[keyName] && oldkey[keyName];
}

bool Input::KeepRelease(int keyName) {//�����Ă����
	return !key[keyName]&&!oldkey[keyName];
}