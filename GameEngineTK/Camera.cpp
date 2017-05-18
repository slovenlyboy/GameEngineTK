#include "Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;



Camera::Camera(int width, int height)
{
	//メンバ変数の初期化


	//カメラの位置
	m_eyepos = Vector3(0, 0, 5);
	//カメラの見ている位置
	m_refpos = Vector3(0, 1, 0);
	//上方向ベクトル
	m_upvec = Vector3(0, 1, 0);
	//垂直
	m_fovY = XMConvertToRadians(60.0f);
	//アスペクト比
	m_aspect = float(width) / float(height);
	//ニアクリップ
	m_niarcllip = 0.01;
	//ファークリップ
	m_farclip = 1000.0f;
	//ビュー行列
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);
	//射影行列
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY,//視野角（↕方向）
		m_aspect, //アスペクト比
		m_niarcllip,//ニアクリップ
		m_farclip);//ファークリップ
}
	

Camera::~Camera()
{
}

void Camera::Updates()
{
	//ビュー行列の生成
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);

	//射影行列の生成
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY,//視野角（↕方向）
		m_aspect, //アスペクト比
		m_niarcllip,//ニアクリップ
		m_farclip);//ファークリップ
}

const DirectX::SimpleMath::Matrix& Camera::GetView()
{
	//ビュー行列
	return m_view;
}

const DirectX::SimpleMath::Matrix& Camera::GetProj()
{
	//射影行列
	return m_proj;
}

void Camera::SetEyePos(const DirectX::SimpleMath::Vector3& EyePos)
{
	m_eyepos = EyePos;
}

void Camera::SetRefPos(const DirectX::SimpleMath::Vector3& refPos)
{
	m_refpos = refPos;
}

void Camera::SetUpVec(const DirectX::SimpleMath::Vector3& upvec)
{
	m_upvec = upvec;

}

void Camera::setFovy(float fovy) 
{
	m_fovY = fovy;
}


void Camera::setAspect(float aspect)
{
	m_aspect = aspect;
}

void Camera::setNiarCllip(float cllip)
{
	m_niarcllip = cllip;
}

void Camera::setFarCllip(float cllip)
{

	m_farclip = cllip;
}

void Camera::setView(Matrix View)
{

	m_view = View;
}

void Camera::setProj(Matrix Proj)
{
	m_proj = Proj;
}