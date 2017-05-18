//自機追従カメラクラス

#pragma once
#include "Camera.h"
#include <d3d11_1.h>
#include <Keyboard.h>
#include<SimpleMath.h>

class FollwCamera :public Camera
{
public:
	//自機とカメラの距離
	static const float camera_dis;
	FollwCamera(int width, int height);
	void Updates() override;

	void setTargetPos(const DirectX::SimpleMath::Vector3& pos);
	void setTargetAngele(float angle);
	
	void setKeyboard(DirectX::Keyboard* keyboard);

	

protected:

	bool cameraFlag;

	DirectX::SimpleMath::Vector3 m_taget_pos;

	float m_taget_angle;

	DirectX::Keyboard* m_keynoard;

	DirectX::Keyboard::KeyboardStateTracker m_tracker;
};

