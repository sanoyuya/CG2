#include<Windows.h>
#include "Input.h"
#include "DirectX_.h"
#include "WindowsApp.h"
#include"myMath.h"

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

//Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	WindowsApp windowsApp;//WindowsApp�N���X�ǂݍ���
	windowsApp.CreatWindow();



	//DirectX���������� ��������

	DirectX_ DirectX_(windowsApp.GetHwnd(), windowsApp.GetW());//DirectX�N���X�ǂݍ���
	//�L�[�擾�J�n
	Input input;
	input.KeyboardInitialize(windowsApp.GetHwnd(), windowsApp.GetW());//����������
	input.MouseInitialize(windowsApp.GetHwnd(), windowsApp.GetW());

	//DirectX���������� �����܂�



	//�`�揉����������������

	DirectX_.DrawInitialize(windowsApp.GetHwnd(), windowsApp.GetW());

	//�`�揉�������������܂�



	//�錾


	// �Q�[�����[�v
	while (true) {

		if (!windowsApp.MessageWindow()) {
			break;
		}

		input.KeyboardUpdate();
		input.MouseUpdate();

		DirectX_.UpdateClear();

		//�X�V����
		
	


		//�`�揈��



		DirectX_.UpdateEnd();

		DirectX_.DrawUpdate();
	}
	windowsApp.Break();

	return 0;
}