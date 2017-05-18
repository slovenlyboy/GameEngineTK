/// <summary>
/// カメラを制御するクラス
/// </summary>

#pragma once
#include <d3d11_1.h>

#include<SimpleMath.h>

class Camera{
	public:
		Camera(int width ,int height);
	virtual	~Camera();

	virtual void Updates();

	//びゅー行列の取得
	const DirectX::SimpleMath::Matrix& GetView();
	//射影行列の取得
	const DirectX::SimpleMath::Matrix& GetProj();

	//視点座標のセット
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

		//カメラの位置
		DirectX::SimpleMath::Vector3 m_eyepos;
		//カメラの見ている位置
		DirectX::SimpleMath::Vector3 m_refpos;
		//上方向ベクトル
		DirectX::SimpleMath::Vector3 m_upvec;
		//垂直
		float m_fovY;
		//アスペクト比
		float m_aspect;
		//ニアクリップ
		float m_niarcllip = 0.01;
		//ファークリップ
		float m_farclip = 1000.0f;
		//ビュー行列
		DirectX::SimpleMath::Matrix m_view;
		//射影行列
		DirectX::SimpleMath::Matrix m_proj;

};