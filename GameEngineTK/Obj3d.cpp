
#include "Obj3d.h"

using namespace DirectX;

using namespace DirectX::SimpleMath;

///静的メンバ変数の定義
//デバイス高テキスト
Microsoft::WRL::ComPtr<ID3D11DeviceContext> Obj3d::m_d3dContext;
Microsoft::WRL::ComPtr<ID3D11Device> Obj3d::m_d3dDevice;

 Camera * Obj3d::m_Camera;
//半湯ステート変数
std::unique_ptr<DirectX::CommonStates> Obj3d::m_states;

//エフェクトファクトリー
 std::unique_ptr<DirectX::EffectFactory>Obj3d::m_factory;

Obj3d::Obj3d()
{
	//メンバ変数を初期化
	m_scale = Vector3(1, 1, 1);
	m_ObjParent = nullptr;
}


Obj3d::~Obj3d()
{
}

void Obj3d::LoadModel(const wchar_t * fileName)
{
	//モデルを読み込む
	m_model = Model::CreateFromCMO(m_d3dDevice.Get(), fileName, *m_factory);
}

void Obj3d::Update()
{
	//ワールド行列の計算

	Matrix scalemat;
	scalemat = Matrix::CreateScale(m_scale);//スケーリング;
	Matrix transmat = Matrix::CreateTranslation(m_translation);//平行移動
	Matrix rotmatZ = Matrix::CreateRotationY(m_rotate.z);//ヨー（方位角）
	Matrix rotmatX = Matrix::CreateRotationY(m_rotate.x);//ヨー（方位角）
	Matrix rotmatY = Matrix::CreateRotationY(m_rotate.y);//ヨー（方位角）
	Matrix rotmat = rotmatZ*rotmatX*rotmatY;
	Matrix::CreateTranslation(m_scale);
	
	m_world = scalemat*rotmat*transmat;
	if (m_ObjParent)
	{
		m_world *= m_ObjParent->getWorld();
	}
}

void Obj3d::Draw()
{

	if (m_model)
	{
		m_model->Draw(m_d3dContext.Get(), *m_states, m_world, m_Camera->GetView(), m_Camera->GetProj());
	}
	//描画
}

void Obj3d::InitializeStatic(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext, Camera * camera)
{
	m_d3dDevice = d3dDevice;

	m_d3dContext = d3dContext;

	m_Camera = camera;

	m_states = std::make_unique<CommonStates>(m_d3dDevice.Get());

	//エフェクトファクトリー生成
	m_factory = std::make_unique<EffectFactory>(m_d3dDevice.Get());

	//テクスチャのパス指定
	m_factory->SetDirectory(L"Resources");

}
