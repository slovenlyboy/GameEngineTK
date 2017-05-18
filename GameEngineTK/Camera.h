/// <summary>
/// �J�����𐧌䂷��N���X
/// </summary>

#pragma once
#include <d3d11_1.h>

#include<SimpleMath.h>

class Camera{
	public:
		Camera(int width ,int height);
	virtual	~Camera();

	virtual void Updates();

	//�т�[�s��̎擾
	const DirectX::SimpleMath::Matrix& GetView();
	//�ˉe�s��̎擾
	const DirectX::SimpleMath::Matrix& GetProj();

	//���_���W�̃Z�b�g
	void SetEyePos(const DirectX::SimpleMath::Vector3& EyePos);

	void SetRefPos(const DirectX::SimpleMath::Vector3& refPos);

	void SetUpVec(const DirectX::SimpleMath::Vector3& upvec);

	void setFovy(float fovy);

	void setAspect(float aspect);
	
	void setNiarCllip(float cllip);

	void setFarCllip(float cllip);

	void setView(DirectX::SimpleMath::Matrix View);

	void setProj(DirectX::SimpleMath::Matrix Proj);

	protected:

		//�J�����̈ʒu
		DirectX::SimpleMath::Vector3 m_eyepos;
		//�J�����̌��Ă���ʒu
		DirectX::SimpleMath::Vector3 m_refpos;
		//������x�N�g��
		DirectX::SimpleMath::Vector3 m_upvec;
		//����
		float m_fovY;
		//�A�X�y�N�g��
		float m_aspect;
		//�j�A�N���b�v
		float m_niarcllip = 0.01;
		//�t�@�[�N���b�v
		float m_farclip = 1000.0f;
		//�r���[�s��
		DirectX::SimpleMath::Matrix m_view;
		//�ˉe�s��
		DirectX::SimpleMath::Matrix m_proj;

};