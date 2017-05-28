#pragma once

#include <windows.h>

#include <wrl/client.h>

#include <d3d11_1.h>

#include "Camera.h"
#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Model.h>

class Obj3d
{
public:
	
	//�ÓI�����o�֐�

	static void InitializeStatic(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice
		, Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext,
		Camera * camera);

	
private:
	//�ÓI�����o�ϐ�
	//�f�o�C�X���e�L�X�g
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dContext;

	static Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice;

	static Camera * m_Camera;
	//�����X�e�[�g�ϐ�
	static std::unique_ptr<DirectX::CommonStates> m_states;

	//�G�t�F�N�g�t�@�N�g���[
	static std::unique_ptr<DirectX::EffectFactory> m_factory;


public:
	Obj3d();
	
	//CMO�ǂݍ���
	void LoadModel(const wchar_t* fileName);

	void Update();

	void Draw();


	
	//�Z�b�^�[
	//�X�P�[�����O(XYZ)
	void SetScale(const DirectX::SimpleMath::Vector3 scale) { m_scale = scale; };
	//��]�p(XYZ)
	void SetRotation(const DirectX::SimpleMath::Vector3 rotate) { m_rotate = rotate; };
	//���s�ړ�(XYZ)
	void SetTransration(const DirectX::SimpleMath::Vector3 translation) { m_translation = translation; };
	//�e��3D�I�u�W�F�N�g�ւ̃|�C���^
	void SetObjParent(Obj3d* ObjParent) { m_ObjParent = ObjParent; };
	//�Q�b�^�[
	//�X�P�[�����O(XYZ)
	const DirectX::SimpleMath::Vector3&  getScale() { return m_scale; };

	//��]�p(XYZ)
	const DirectX::SimpleMath::Vector3&  geRotation() { return m_rotate; };

	//���s�ړ�(XYZ()
	const DirectX::SimpleMath::Vector3&  getTransration() { return m_translation; };

	//���[���h�s��

	const DirectX::SimpleMath::Matrix& getWorld() { return m_world; }

private:
	//�����o�ϐ�

	//���f��
	std::unique_ptr<DirectX::Model>m_model;

	//�X�P�[�����O(XYZ)
	DirectX::SimpleMath::Vector3 m_scale;
	
	//��]�p(XYZ)

	DirectX::SimpleMath::Vector3 m_rotate;//���[�i���ʊp�j
				
	//���s�ړ�(XYZ()
	DirectX::SimpleMath::Vector3 m_translation;//���s�ړ�

	//���[���h�s��
	DirectX::SimpleMath::Matrix m_world;

	//�e��Obj3d�ւ̂��ۂ���
	Obj3d* m_ObjParent;

	
};

