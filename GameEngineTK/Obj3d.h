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
	
	//静的メンバ関数

	static void InitializeStatic(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice
		, Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext,
		Camera * camera);

	
private:
	//静的メンバ変数
	//デバイス高テキスト
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dContext;

	static Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice;

	static Camera * m_Camera;
	//半湯ステート変数
	static std::unique_ptr<DirectX::CommonStates> m_states;

	//エフェクトファクトリー
	static std::unique_ptr<DirectX::EffectFactory> m_factory;


public:
	Obj3d();
	
	//CMO読み込み
	void LoadModel(const wchar_t* fileName);

	void Update();

	void Draw();


	
	//セッター
	//スケーリング(XYZ)
	void SetScale(const DirectX::SimpleMath::Vector3 scale) { m_scale = scale; };
	//回転角(XYZ)
	void SetRotation(const DirectX::SimpleMath::Vector3 rotate) { m_rotate = rotate; };
	//平行移動(XYZ)
	void SetTransration(const DirectX::SimpleMath::Vector3 translation) { m_translation = translation; };
	//親の3Dオブジェクトへのポインタ
	void SetObjParent(Obj3d* ObjParent) { m_ObjParent = ObjParent; };
	//ゲッター
	//スケーリング(XYZ)
	const DirectX::SimpleMath::Vector3&  getScale() { return m_scale; };

	//回転角(XYZ)
	const DirectX::SimpleMath::Vector3&  geRotation() { return m_rotate; };

	//平行移動(XYZ()
	const DirectX::SimpleMath::Vector3&  getTransration() { return m_translation; };

	//ワールド行列

	const DirectX::SimpleMath::Matrix& getWorld() { return m_world; }

private:
	//メンバ変数

	//モデル
	std::unique_ptr<DirectX::Model>m_model;

	//スケーリング(XYZ)
	DirectX::SimpleMath::Vector3 m_scale;
	
	//回転角(XYZ)

	DirectX::SimpleMath::Vector3 m_rotate;//ヨー（方位角）
				
	//平行移動(XYZ()
	DirectX::SimpleMath::Vector3 m_translation;//平行移動

	//ワールド行列
	DirectX::SimpleMath::Matrix m_world;

	//親のObj3dへのっぽいんた
	Obj3d* m_ObjParent;

	
};

