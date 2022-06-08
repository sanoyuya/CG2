#pragma once
#include "Input.h"
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include<vector>
#include<string>
#include <d3dcompiler.h>
#include<DirectXTex.h>

class DirectX_
{
private:
	const int window_width = 1280;//����
	const int window_height = 720;//�c��

	HRESULT result;
	ID3D12Device* device = nullptr;
	IDXGIFactory7* dxgiFactory = nullptr;
	IDXGISwapChain4* swapChain = nullptr;
	ID3D12CommandAllocator* commandAllocator = nullptr;
	ID3D12GraphicsCommandList* commandList = nullptr;
	ID3D12CommandQueue* commandQueue = nullptr;
	ID3D12DescriptorHeap* rtvHeap = nullptr;
	//�X���b�v�`�F�[���̐ݒ�
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	//�f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	//�o�b�N�o�b�t�@
	std::vector<ID3D12Resource*>backBuffers;
	//�t�F���X�̐���
	ID3D12Fence* fence = nullptr;
	UINT64 fenceVal = 0;



	//�`�揉��������
	//�q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES cbHeapProp{};

	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC cbResourceDesc{};

	ID3D12Resource* constBuffMaterial = nullptr;

	// ���_�o�b�t�@�̐ݒ�
	D3D12_HEAP_PROPERTIES heapProp{}; // �q�[�v�ݒ�

	// ���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};

	// ���_�o�b�t�@�̐���
	ID3D12Resource* vertBuff = nullptr;

	// GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
	XMFLOAT3* vertMap = nullptr;

	// ���_�o�b�t�@�r���[�̍쐬
	D3D12_VERTEX_BUFFER_VIEW vbView{};

	ID3DBlob* vsBlob = nullptr; // ���_�V�F�[�_�I�u�W�F�N�g
	ID3DBlob* psBlob = nullptr; // �s�N�Z���V�F�[�_�I�u�W�F�N�g
	ID3DBlob* errorBlob = nullptr; // �G���[�I�u�W�F�N�g

	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};

	//�C���f�b�N�X�o�b�t�@�̐���
	ID3D12Resource* indexBuff = nullptr;

	//�C���f�b�N�X�o�b�t�@���}�b�s���O
	uint16_t* indexMap = nullptr;

	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	D3D12_INDEX_BUFFER_VIEW ibView{};

	// �u�����h�X�e�[�g
	D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = pipelineDesc.BlendState.RenderTarget[0];// RBGA�S�Ẵ`�����l����`��

	//�e�N�X�`���T���v���[�̐ݒ�
	D3D12_STATIC_SAMPLER_DESC samplerDesc{};

	// ���[�g�V�O�l�`��
	ID3D12RootSignature* rootSignature;

	// ���[�g�V�O�l�`���̐ݒ�
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};

	// ���[�g�V�O�l�`���̃V���A���C�Y
	ID3DBlob* rootSigBlob = nullptr;

	// �p�C�v�����X�e�[�g�̐���
	ID3D12PipelineState* pipelineState = nullptr;




	//�萔�o�b�t�@�p�f�[�^�\����(3D�ϊ��s��)
	struct ConstBufferDataTransform {
		XMMATRIX mat;//3D�ϊ��s��
	};

	//�萔�o�b�t�@�̐���
	ID3D12Resource* constBuffTransform = nullptr;
	ConstBufferDataTransform* constMapTransform = nullptr;

	//�q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES cbHeapProp_{};
	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC cbResourceDesc_{};




	//���[�g�p�����[�^�̐ݒ�
	D3D12_ROOT_PARAMETER rootParams[3] = {};


	//�萔�o�b�t�@�p�f�[�^�\����(�}�e���A��)
	struct ConstBufferDataMaterial {
		XMFLOAT4 color;//�F(RGBA)
	};
	
	// �r���[�|�[�g�ݒ�R�}���h
	D3D12_VIEWPORT viewport{};
	// �V�U�[��`
	D3D12_RECT scissorRect{};

	//���_�f�[�^�̍\����
	struct Vertex {
		XMFLOAT3 pos;
		XMFLOAT2 uv;
	};

	//���_�f�[�^
	Vertex vertices[4] = {
		//  x	  y   z		 u	  v
		{{-50.0f,-50.0f,0.0f},{0.0f,1.0f}},//����
		{{-50.0f,50.0f,0.0f},{0.0f,0.0f}},//����
		{{50.0f,-50.0f,0.0f},{1.0f,1.0f}},//�E��
		{{50.0f,50.0f,0.0f},{1.0f,0.0f}},//�E��
	};

	//�C���f�b�N�X�f�[�^
	unsigned short indices[6] = {
		0,1,2,//�O�p�`1��
		1,2,3,//�O�p�`2��
	};

	//���_�f�[�^�S�̃T�C�Y = ���_�f�[�^����̃T�C�Y * ���_�f�[�^�̗v�f��
	UINT sizeVB = static_cast<UINT>(sizeof(vertices[0]) * _countof(vertices));

	//�C���f�b�N�X�f�[�^�S�̂̃T�C�Y
	UINT sizeIB = static_cast<UINT>(sizeof(uint16_t) * _countof(indices));


	//1.���\�[�X�o���A�ŏ������݉\�ɕύX
	D3D12_RESOURCE_BARRIER barrierDesc{};



	//�e�N�X�`���}�b�s���O��������
	
	////�������s�N�Z����
	//const size_t textureWidth = 256;
	////�c�����s�N�Z����
	//const size_t textureHeight = 256;
	////�z��̗v�f��
	//const size_t imageDataCount = textureWidth * textureHeight;
	////�摜�C���[�W�f�[�^�z��
	//XMFLOAT4* imageData = new XMFLOAT4[imageDataCount];//�K����ŉ������

	TexMetadata metadata{};
	ScratchImage scratchImg{};
	ScratchImage mipChain{};

	//�q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES textureHeapProp{};
	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC textureResourceDesc{};
	//�e�N�X�`���o�b�t�@�̐���
	ID3D12Resource* texBuff = nullptr;

	//SRV�̍ő��
	const size_t kMaxSRVCount = 2056;

	//�f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};

	//�ݒ������SRV�p�f�X�N���v�^�q�[�v�𐶐�
	ID3D12DescriptorHeap* srvHeap = nullptr;

	//SRV�q�[�v�̐擪�n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle;

	//�V�F�[�_�[���\�[�X�r���[�ݒ�
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};//�ݒ�\����

	//�f�X�N���v�^�����W�̐ݒ�
	D3D12_DESCRIPTOR_RANGE descriptorRange{};

	//�e�N�X�`���}�b�s���O�����܂�

	//�r���[�ϊ��s��	
	XMMATRIX matView;
	float angle = 0.0f;//�J�����̉�]�p

	Input input;//Input�N���X�ǂݍ���
	
public:
	DirectX_(HWND hwnd, WNDCLASSEX w);
	void DrawInitialize();
	void Update();
	void DrawUpdate();
	void CameraInitialize();
	void CameraUpdate();
	void SetHwnd();
};

