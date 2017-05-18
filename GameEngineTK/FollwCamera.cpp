#include "pch.h"
#include "FollwCamera.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;



//�ÓI�����o�ϐ��̏�����
const float FollwCamera::camera_dis = 5.0f;

FollwCamera::FollwCamera(int width, int height)
	:Camera(width,height)
{
	m_taget_pos = Vector3::Zero;

	m_taget_angle = 0.0f;

	m_keynoard = nullptr;

	cameraFlag = false;
}

void FollwCamera::Updates()
{	
	
	//�L�[�{�[�h�̏�Ԃ��擾
	Keyboard::State keystate = m_keynoard->GetState();
	m_tracker.Update(keystate);


	if (m_tracker.IsKeyPressed(Keyboard::Keyboard::C))
	{
		//�J�����t���O�̐ؑ�
		cameraFlag  = !cameraFlag;

	}

	Vector3 eyepos, refpos;

	if (cameraFlag == false)
	{
		
		{//Fps�J����
			Vector3 position;

			position = (m_taget_pos + Vector3(0, 0.2f, 0));
			Vector3 cameraV(0.0f, 0.0f, -camera_dis);
			Matrix rotmat = Matrix::CreateRotationY(m_taget_angle);
			cameraV = Vector3::TransformNormal(cameraV, rotmat);
			eyepos = position + cameraV*0.1f;
			refpos = position + cameraV;
		}
	}
	else
	{
		{//Tps�J����
			refpos = (m_taget_pos + Vector3(0, 2.0f, 0));
			Vector3 cameraV(0.0f, 0.0f, camera_dis);
			Matrix rotmat = Matrix::CreateRotationY(m_taget_angle);
			cameraV = Vector3::TransformNormal(cameraV, rotmat);
			eyepos = refpos + cameraV;
		}

		////���_�����ݒn������
		eyepos = m_eyepos + (eyepos - m_eyepos)*0.05f;
		//
		////�Q�Ɠ_�����݈ʒu������
		refpos = m_refpos + (refpos - m_refpos)*0.05;

	}

	
	


	this->SetEyePos(eyepos);
	this->SetRefPos(refpos);
	//���N���X�X�V
	Camera::Updates();
}


void FollwCamera::setTargetPos(const DirectX::SimpleMath::Vector3& pos)
{
	m_taget_pos = pos;
}

void FollwCamera::setTargetAngele(float angle)
{
	m_taget_angle = angle;
}

void FollwCamera::setKeyboard(DirectX::Keyboard* keyboard)
{

	m_keynoard = keyboard;

}