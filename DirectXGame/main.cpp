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

	DirectX_.DrawInitialize();

	//�`�揉�������������܂�



	//�錾
	//const int window_width = 1280;//����
	//const int window_height = 720;//�c��

	//Matrix4 MATRIX4;

	//

	////�r���[�ϊ��s��	
	//XMMATRIX matView;
	//float angle = 0.0f;//�J�����̉�]�p
	////�J��������
	//XMFLOAT3 eye = { 0, 30, -100 };	//���_���W
	//XMFLOAT3 target = { 0, 0, 0 };	//�����_���W
	//XMFLOAT3 up = { 0, 1, 0 };		//������x�N�g��

	////�ˉe�ϊ��s��(�������e)
	//XMMATRIX matProjection = XMMatrixPerspectiveFovLH(ChangeRadians(45.0f),
	//	(float)window_width / window_height,
	//	0.1f, 1000.0f
	//);



	// �Q�[�����[�v
	while (true) {

		if (!windowsApp.MessageWindow()) {
			break;
		}

		input.KeyboardUpdate();
		input.MouseUpdate();

		DirectX_.UpdateClear();

		//�X�V����

		//if (input.KeyboardKeepPush(DIK_W) || input.KeyboardKeepPush(DIK_S) || input.KeyboardKeepPush(DIK_D) || input.KeyboardKeepPush(DIK_A)) {
		//	//���W���ړ����鏈��(Z���W)
		//	if (input.KeyboardKeepPush(DIK_W)) { position.z += 1.0f; }
		//	else if (input.KeyboardKeepPush(DIK_S)) { position.z -= 1.0f; }
		//	if (input.KeyboardKeepPush(DIK_D)) { position.x += 1.0f; }
		//	else if (input.KeyboardKeepPush(DIK_A)) { position.x -= 1.0f; }
		//}
		//if (input.KeyboardKeepPush(DIK_UP) || input.KeyboardKeepPush(DIK_DOWN) || input.KeyboardKeepPush(DIK_RIGHT) || input.KeyboardKeepPush(DIK_LEFT)) {
		//	//���W���ړ����鏈��(Z���W)
		//	if (input.KeyboardKeepPush(DIK_UP)) { rotation.x += 1.0f; }
		//	else if (input.KeyboardKeepPush(DIK_DOWN)) { rotation.x -= 1.0f; }
		//	if (input.KeyboardKeepPush(DIK_RIGHT)) { rotation.y -= 1.0f; }
		//	else if (input.KeyboardKeepPush(DIK_LEFT)) { rotation.y += 1.0f; }
		//}
		//if (input.KeyboardKeepPush(DIK_U) || input.KeyboardKeepPush(DIK_I) || input.KeyboardKeepPush(DIK_J) || input.KeyboardKeepPush(DIK_K) || input.KeyboardKeepPush(DIK_N) || input.KeyboardKeepPush(DIK_M)) {
		//	if (input.KeyboardKeepPush(DIK_U)) { scale.x += 0.1f; }
		//	else if (input.KeyboardKeepPush(DIK_I)) { scale.x -= 0.1f; }
		//	if (input.KeyboardKeepPush(DIK_J)) { scale.y += 0.1f; }
		//	else if (input.KeyboardKeepPush(DIK_K)) { scale.y -= 0.1f; }
		//	if (input.KeyboardKeepPush(DIK_N)) { scale.z += 0.1f; }
		//	else if (input.KeyboardKeepPush(DIK_M)) { scale.z -= 0.1f; }
		//	if (scale.x < 0.1) { scale.x = 0.1f; }
		//	if (scale.y < 0.1) { scale.y = 0.1f; }
		//	if (scale.z < 0.1) { scale.z = 0.1f; }
		//}


		//�`�揈��



		DirectX_.UpdateEnd();

		DirectX_.DrawUpdate();
	}
	windowsApp.Break();

	return 0;
}