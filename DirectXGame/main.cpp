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
	input.Initialize(windowsApp.GetHwnd(), windowsApp.GetW());//����������

	//DirectX���������� �����܂�



	//�`�揉����������������

	DirectX_.DrawInitialize();

	//�`�揉�������������܂�



	//�錾
	const int window_width = 1280;//����
	const int window_height = 720;//�c��

	Matrix4 MATRIX4;

	//���[���h�ϊ��s��
	Matrix4 matWorld;
	//�X�P�[�����O�s��
	Matrix4 matScale;
	//��]�s��
	Matrix4 matRot;
	//���s�ړ��s��
	Matrix4 matTrans;
	//���W
	XMFLOAT3 scale = { 1.0f,1.0f,1.0f };
	//��]�p
	XMFLOAT3 rotation = { 0.0f,0.0f,0.0f };
	//���W
	XMFLOAT3 position = { 0.0f,0.0f,0.0f };

	//�r���[�ϊ��s��	
	XMMATRIX matView;
	float angle = 0.0f;//�J�����̉�]�p
	//�J��������
	XMFLOAT3 eye = { 0, 0, -100 };	//���_���W
	XMFLOAT3 target = { 0, 0, 0 };	//�����_���W
	XMFLOAT3 up = { 0, 1, 0 };		//������x�N�g��

	//�ˉe�ϊ��s��(�������e)
	Matrix4 matProjection = XMMatrixPerspectiveFovLH(ChangeRadians(45.0f),
		(float)window_width / window_height,
		0.1f, 1000.0f
	);



	// �Q�[�����[�v
	while (true) {

		if (!windowsApp.MessageWindow()) {
			break;
		}

		input.Update();

		DirectX_.UpdateClear();

		//�X�V����

		if (input.KeepPush(DIK_W) || input.KeepPush(DIK_S) || input.KeepPush(DIK_D) || input.KeepPush(DIK_A)) {
			//���W���ړ����鏈��(Z���W)
			if (input.KeepPush(DIK_W)) { position.z += 1.0f; }
			else if (input.KeepPush(DIK_S)) { position.z -= 1.0f; }
			if (input.KeepPush(DIK_D)) { position.x += 1.0f; }
			else if (input.KeepPush(DIK_A)) { position.x -= 1.0f; }
		}
		if (input.KeepPush(DIK_UP) || input.KeepPush(DIK_DOWN) || input.KeepPush(DIK_RIGHT) || input.KeepPush(DIK_LEFT)) {
			//���W���ړ����鏈��(Z���W)
			if (input.KeepPush(DIK_UP)) { rotation.x += 1.0f; }
			else if (input.KeepPush(DIK_DOWN)) { rotation.x -= 1.0f; }
			if (input.KeepPush(DIK_RIGHT)) { rotation.y -= 1.0f; }
			else if (input.KeepPush(DIK_LEFT)) { rotation.y += 1.0f; }
		}
		if (input.KeepPush(DIK_U) || input.KeepPush(DIK_I) || input.KeepPush(DIK_J) || input.KeepPush(DIK_K) || input.KeepPush(DIK_N) || input.KeepPush(DIK_M)) {
			if (input.KeepPush(DIK_U)) { scale.x += 0.1f; }
			else if (input.KeepPush(DIK_I)) { scale.x -= 0.1f; }
			if (input.KeepPush(DIK_J)) { scale.y += 0.1f; }
			else if (input.KeepPush(DIK_K)) { scale.y -= 0.1f; }
			if (input.KeepPush(DIK_N)) { scale.z += 0.1f; }
			else if (input.KeepPush(DIK_M)) { scale.z -= 0.1f; }
			if (scale.x < 0.1) { scale.x = 0.1f; }
			if (scale.y < 0.1) { scale.y = 0.1f; }
			if (scale.z < 0.1) { scale.z = 0.1f; }
		}
		matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));

		MATRIX4.MakeScaling(scale.x, scale.y, scale.z);
		matScale = MATRIX4;

		matRot = MakeIdentity();
		MATRIX4 = MakeIdentity();
		MATRIX4.MakeRotation(ChangeRadians(rotation.x), ChangeRadians(rotation.y), ChangeRadians(rotation.z));
		matRot *= MATRIX4;

		MATRIX4 = MakeIdentity();
		MATRIX4.MakeTranslation(position.x, position.y, position.z);
		matTrans = MATRIX4;

		matWorld = MakeIdentity();//�ό`���Z�b�g
		matWorld *= matScale;//���[���h�s��ɃX�P�[�����O���f
		matWorld *= matRot;//���[���h�s��ɉ�]�𔽉f
		matWorld *= matTrans;//���[���h�s��ɕ��s�ړ��𔽉f

		MATRIX4 = MakeIdentity();

		//�`�揈��



		DirectX_.UpdateEnd(matWorld, matView, matProjection);

		DirectX_.DrawUpdate();
	}
	windowsApp.Break();

	return 0;
}