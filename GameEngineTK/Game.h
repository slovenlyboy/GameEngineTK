//
// Game.h
//

#pragma once

#include "StepTimer.h"
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Model.h>
#include "DebugCamera.h"
#include <Keyboard.h>


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
public:

    Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();
    void Present();

    void CreateDevice();
    void CreateResources();

    void OnDeviceLost();

    // Device resources.
    HWND                                            m_window;
    int                                             m_outputWidth;
    int                                             m_outputHeight;

    D3D_FEATURE_LEVEL                               m_featureLevel;
    Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice1;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext1;

    Microsoft::WRL::ComPtr<IDXGISwapChain>          m_swapChain;
    Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain1;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;

    // Rendering loop timer.
    DX::StepTimer                                   m_timer;

    //�ėp�X�e�[�g�ݒ�
	std::unique_ptr<DirectX::CommonStates> m_states;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormal>> m_batch;
	std::unique_ptr<DirectX::BasicEffect> m_effect;//�ׁ[�V�b�N�G�t�F�N�g�^���j�[�N�|�C���^�̐錾
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;//�C���v�b�g���C�A�E�g�ϐ��̐錾



	DirectX::SimpleMath::Matrix m_world;//���[���h�s��
	DirectX::SimpleMath::Matrix m_view;//�r���[�s��
	DirectX::SimpleMath::Matrix m_proj;//�v���W�F�N�V�����s��



	//�f�o�b�O�J����
	std::unique_ptr<DebugCamera> m_debugCamera;

	//�G�t�F�N�g�t�@�N�g���[
	std::unique_ptr<DirectX::EffectFactory> m_factory;
	

	//�V��
	std::unique_ptr<DirectX::Model>m_modelSkyDome;

	//�n��
	std::unique_ptr<DirectX::Model>m_modelGround;

	//�����f��
	std::unique_ptr<DirectX::Model>m_modelBall;

	//�����f��
	std::unique_ptr<DirectX::Model>m_modelTeaPod;

	std::unique_ptr<DirectX::Model>m_modelHead;


	//���̃��[���h�s��
	DirectX::SimpleMath::Matrix m_worldBall[21];

	DirectX::SimpleMath::Matrix m_worldTeaPod[20];

	DirectX::SimpleMath::Matrix m_worldGround;


	DirectX::SimpleMath::Matrix m_worldHead;


	std::unique_ptr<DirectX::Keyboard> keyboard;

	float m_angle = 0;

	float m_scele = 1.0f;

	int m_sFlag = 0;

	int m_time = 60;

	float m_pos = 1.0f;


	float anngle[20];

	float lenge[20];



	DirectX::SimpleMath::Vector3 head_Pos;


	float spin = 0.0f;
};