#include<Windows.h>
#include "Input.h"
#include "DirectX_.h"
#include "WindowsApp.h"

#pragma comment(lib, "d3dcompiler.lib")

//Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	WindowsApp windowsApp;//WindowsApp�N���X�ǂݍ���
	windowsApp.CreatWindow();



	//DirectX���������� ��������

	DirectX_ DirectX_(windowsApp.GetHwnd(), windowsApp.GetW());//DirectX�N���X�ǂݍ���

	//DirectX���������� �����܂�



	//�`�揉����������������

	DirectX_.DrawInitiaize();

	//�`�揉�������������܂�



	// �Q�[�����[�v
	while (true) {

		if (!windowsApp.MessageWindow()) {
			break;
		}



		//DirectX���t���[�������@��������

		DirectX_.Update();
		DirectX_.DrawUpdate();

		//DirectX���t���[�������@�����܂�



	}
	windowsApp.Break();

	return 0;
}