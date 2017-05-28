
#include "Obj3d.h"

using namespace DirectX;

using namespace DirectX::SimpleMath;

///�ÓI�����o�ϐ��̒�`
//�f�o�C�X���e�L�X�g
Microsoft::WRL::ComPtr<ID3D11DeviceContext> Obj3d::m_d3dContext;
Microsoft::WRL::ComPtr<ID3D11Device> Obj3d::m_d3dDevice;

 Camera * Obj3d::m_Camera;
//�����X�e�[�g�ϐ�
std::unique_ptr<DirectX::CommonStates> Obj3d::m_states;

//�G�t�F�N�g�t�@�N�g���[
 std::unique_ptr<DirectX::EffectFactory>Obj3d::m_factory;

Obj3d::Obj3d()
{
	//�����o�ϐ���������
	m_scale = Vector3(1, 1, 1);
	m_ObjParent = nullptr;
}


Obj3d::~Obj3d()
{
}

void Obj3d::LoadModel(const wchar_t * fileName)
{
	//���f����ǂݍ���
	m_model = Model::CreateFromCMO(m_d3dDevice.Get(), fileName, *m_factory);
}

void Obj3d::Update()
{
	//���[���h�s��̌v�Z

	Matrix scalemat;
	scalemat = Matrix::CreateScale(m_scale);//�X�P�[�����O;
	Matrix transmat = Matrix::CreateTranslation(m_translation);//���s�ړ�
	Matrix rotmatZ = Matrix::CreateRotationY(m_rotate.z);//���[�i���ʊp�j
	Matrix rotmatX = Matrix::CreateRotationY(m_rotate.x);//���[�i���ʊp�j
	Matrix rotmatY = Matrix::CreateRotationY(m_rotate.y);//���[�i���ʊp�j
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
	//�`��
}

void Obj3d::InitializeStatic(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext, Camera * camera)
{
	m_d3dDevice = d3dDevice;

	m_d3dContext = d3dContext;

	m_Camera = camera;

	m_states = std::make_unique<CommonStates>(m_d3dDevice.Get());

	//�G�t�F�N�g�t�@�N�g���[����
	m_factory = std::make_unique<EffectFactory>(m_d3dDevice.Get());

	//�e�N�X�`���̃p�X�w��
	m_factory->SetDirectory(L"Resources");

}
