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

    //汎用ステート設定
	std::unique_ptr<DirectX::CommonStates> m_states;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormal>> m_batch;
	std::unique_ptr<DirectX::BasicEffect> m_effect;//べーシックエフェクト型ユニークポインタの宣言
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;//インプットレイアウト変数の宣言



	DirectX::SimpleMath::Matrix m_world;//ワールド行列
	DirectX::SimpleMath::Matrix m_view;//ビュー行列
	DirectX::SimpleMath::Matrix m_proj;//プロジェクション行列



	//デバッグカメラ
	std::unique_ptr<DebugCamera> m_debugCamera;

	//エフェクトファクトリー
	std::unique_ptr<DirectX::EffectFactory> m_factory;
	

	//天球
	std::unique_ptr<DirectX::Model>m_modelSkyDome;

	//地面
	std::unique_ptr<DirectX::Model>m_modelGround;

	//球モデル
	std::unique_ptr<DirectX::Model>m_modelBall;

	//球モデル
	std::unique_ptr<DirectX::Model>m_modelTeaPod;

	std::unique_ptr<DirectX::Model>m_modelHead;


	//球のワールド行列
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