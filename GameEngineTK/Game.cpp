﻿//
// Game.cpp
//

#include "pch.h"
#include "Game.h"
#include <time.h>



extern void ExitGame();

using namespace DirectX;

using namespace DirectX::SimpleMath;

using Microsoft::WRL::ComPtr;




Game::Game() :
    m_window(0),
    m_outputWidth(800),
    m_outputHeight(600),
    m_featureLevel(D3D_FEATURE_LEVEL_9_1)
{
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    m_window = window;
    m_outputWidth = std::max(width, 1);
    m_outputHeight = std::max(height, 1);

    CreateDevice();

    CreateResources();

	keyboard = std::make_unique<Keyboard>();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */


	//初期化はここに書く

	srand((unsigned int)time(NULL));

	m_batch = std::make_unique<PrimitiveBatch<VertexPositionNormal>>(m_d3dContext.Get());//.Getで中のポインタを参照

	m_effect = std::make_unique<BasicEffect>(m_d3dDevice.Get());//.Getで中のポインタを参照

	//セットプロジェクション行列の作成
	m_effect->SetProjection(XMMatrixOrthographicOffCenterRH(0,
	m_outputWidth, m_outputHeight, 0.0f, 0.0f, 1.0f));
	m_effect->SetVertexColorEnabled(true);

	void const* shaderByteCode;
	size_t byteCodeLength;

	m_effect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	m_d3dDevice->CreateInputLayout(VertexPositionColor::InputElements,
		VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		m_inputLayout.GetAddressOf());

	//汎用ステート

	m_states = std::make_unique<CommonStates>(m_d3dDevice.Get());


	//デバッグカメラ生成
	m_debugCamera = std::make_unique<DebugCamera>(m_outputWidth,m_outputHeight);



	//エフェクトファクトリー生成
	m_factory = std::make_unique<EffectFactory>(m_d3dDevice.Get());
	//テクスチャのパス指定
	m_factory->SetDirectory(L"Resources");
	//モデルの生成
	m_modelSkyDome = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources/SkyDome.cmo", *m_factory);

	m_modelGround = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources/ground200m.cmo", *m_factory);

	m_modelBall = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources/skyball.cmo", *m_factory);

	m_modelTeaPod = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources/TeaPod.cmo", *m_factory);

	m_modelHead = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources/head.cmo", *m_factory);




	for (int i = 0; i < 20; i++)
	{

		anngle[i] = rand() % 200-100;

		lenge[i] = rand() % 100;

	}

}

// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
	float elapsedTime = float(timer.GetElapsedSeconds());

	// TODO: Add your game logic here.
	elapsedTime;
	//毎フレーム処理を書く
	m_debugCamera->Update();



	//ワールド行列計算
	Matrix scalemat;

	m_angle++;

	

	

	if (m_pos > 0.0f)
	{
			m_pos -= 0.002f;
	}
	else
	{
			m_pos = 0.0f;
	}

		

	switch (m_sFlag)
	{
	case 0:
		m_scele+= 0.05f;
		break;

	case 1:
		m_scele-= 0.05f;
		break;

	}


	if (m_scele >= 5.0f)
	{
		m_sFlag = 1;
	}

	if (m_scele <= 1.0f)
	{
		m_sFlag = 0;
	}

	//ワールド行列合成(SRT)
	//for (int i = 0; i < 21; i++)
	//{
	//	Matrix transmat;

	//	Matrix rotmatZ;

	//	scalemat = Matrix::CreateScale(1.0f);//スケーリング

	//	if (i <= 9)
	//	{
	//		transmat = Matrix::CreateTranslation(20.0f, 0.0f, 0.0f);//平行移動
	//		rotmatZ = Matrix::CreateRotationZ(XMConvertToRadians(36.0f*i + m_angle));//ロール
	//	}
	//	else
	//	{
	//		transmat = Matrix::CreateTranslation(30.0f, 0.0f, 0.0f);//平行移動
	//		rotmatZ = Matrix::CreateRotationZ(XMConvertToRadians(36.0f*i - m_angle));//ロール
	//	}
	//	if (i == 20)
	//	{
	//		transmat = Matrix::CreateTranslation(0.0f, 0.0f, 0.0f);//平行移動
	//		scalemat = Matrix::CreateScale(2.5f);//スケーリング
	//		rotmatZ = Matrix::CreateRotationZ(-m_angle / 60);//ロール
	//	}

	//	//回転		
	//	Matrix rotmatX = Matrix::CreateRotationX(XMConvertToRadians(270.0f));//ピッチ（仰角）
	//	Matrix rotmatY = Matrix::CreateRotationY(XMConvertToRadians(0.0f));//ヨー（方位角）
	//	//回転行列の合成
	//	Matrix rotmat = rotmatZ*rotmatX*rotmatY;

	//	m_worldBall[i] = scalemat*transmat*rotmat;
	//}

	


	//for (int i = 0; i < 20; i++)
	//{



	//	Matrix transmat;

	//	Matrix rotmatZ;

	//	scalemat = Matrix::CreateScale(m_scele);//スケーリング

	//	transmat = Matrix::CreateTranslation((cosf(anngle[i])*lenge[i])*m_pos, 0.0f, (sinf(anngle[i])*lenge[i])*m_pos);//平行移動

	//	
	//	rotmatZ = Matrix::CreateRotationZ(XMConvertToRadians(0.0f));//ロール

	//	//(0~XM_2PI)(0~100)cosf(anngle[i])*lenge[i])sinf(anngle[i])*lenge[i])
	//	//回転		
	//	Matrix rotmatX = Matrix::CreateRotationX(XMConvertToRadians(0.0f));//ピッチ（仰角）
	//	Matrix rotmatY = Matrix::CreateRotationY(XMConvertToRadians(m_angle));//ヨー（方位角）
	//																	   //回転行列の合成
	//	Matrix rotmat = rotmatZ*rotmatX*rotmatY;

	//	m_worldTeaPod[i] = scalemat*rotmat*transmat;
	//}



	//for (int i = 0; i < 40000; i++)
	//{

	//	Matrix transmat = Matrix::CreateTranslation(i % 200-100,0.0f,i/200-100);

	//	Matrix rotmatZ;

	//	scalemat = Matrix::CreateScale(1.0f);//スケーリング

	//	Matrix rotmatX = Matrix::CreateRotationX(XMConvertToRadians(0.0f));//ピッチ（仰角）
	//	Matrix rotmatY = Matrix::CreateRotationY(XMConvertToRadians(0.0f));//ヨー（方位角）


	//	Matrix rotmat = rotmatZ*rotmatX*rotmatY;

	//	m_worldGround[i] = scalemat*rotmat*transmat;
	//}



	//時期のワールド行列を計算


	Matrix transmat = Matrix::CreateTranslation(head_Pos);//平行移動


	Matrix rotmat = Matrix::CreateRotationY(XMConvertToRadians(spin));//ヨー（方位角）



	m_worldHead = rotmat*transmat;

	   



	Keyboard::State key = keyboard->GetState();
	

		if (key.A)
		{

			float moveS = 0.5f;

			spin += moveS;

		}
		else if (key.D)
		{

			float moveS = -0.5f;

			spin += moveS;

		}


		if (key.W)
		{

			Vector3 moveV(0, 0, -0.1f);


			moveV = SimpleMath::Vector3::TransformNormal(moveV, rotmat);

			head_Pos += moveV;

		}
		else if (key.S)
		{

			Vector3 moveV(0, 0, +0.1f);


			moveV = SimpleMath::Vector3::TransformNormal(moveV, rotmat);

			head_Pos += moveV;

		}
		




		


		


		


		
		

}

// Draws the scene.
void Game::Render()
{
	uint16_t indices[] =
	{
		0,1,2,
		2,1,3
	};

	VertexPositionNormal vertices[] =
	{
		{Vector3(-1.0f,+1.0f,0.0f),Vector3(0.0f,0.0f,1.0f)},
		{Vector3(-1.0f,-1.0f,0.0f),Vector3(0.0f,0.0f,1.0f)},
		{Vector3(+1,+1,0),Vector3(0,0,1)},
		{Vector3(+1,-1,0),Vector3(0,0,1)},
	};

    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();//キャンバスの初期化

    // TODO: Add your rendering code here.
	//描画処理はここに書く

	m_d3dContext->OMSetBlendState(m_states->Opaque(), nullptr, 0xFFFFFFFF);//透明度
	m_d3dContext->OMSetDepthStencilState(m_states->DepthNone(), 0);//深度バッファの設定
	m_d3dContext->RSSetState(m_states->CullClockwise());//表裏関係なく描画
  /*  ビュー行列設定*/
	//m_view = Matrix::CreateLookAt(Vector3(0.0f, 200.0f,2.0f),//カメラ視点
	//	Vector3::Zero, //カメラが何処向いているか　
	//	Vector3::UnitY);//上方向ベクトル

	m_view = m_debugCamera->GetCameraMatrix();//デバッグカメラからビュー行列を取得

	//プロジェクション行列設定
	m_proj = Matrix::CreatePerspectiveFieldOfView(XM_PI /4.0f,//視野角（↕方向）
		float(m_outputWidth) / float(m_outputHeight), //アスペクト比
		0.1f,//ニアクリップ
		500.f);//ファークリップ

	m_effect->SetView(m_view);
	m_effect->SetProjection(m_proj);
	m_effect->Apply(m_d3dContext.Get());
	m_d3dContext->IASetInputLayout(m_inputLayout.Get());

	//モデルの描画
	m_modelSkyDome->Draw(m_d3dContext.Get(), *m_states, m_world, m_view, m_proj);
	//
	
	m_modelGround->Draw(m_d3dContext.Get(), *m_states, Matrix::Identity, m_view, m_proj);


	m_modelHead->Draw(m_d3dContext.Get(), *m_states, m_worldHead, m_view, m_proj);



	/*for (int i = 0; i < 21; i++)
	{
		m_modelBall->Draw(m_d3dContext.Get(), *m_states, m_worldBall[i], m_view, m_proj);
	}*/



	/*for (int i = 0; i < 20; i++)
	{
		m_modelTeaPod->Draw(m_d3dContext.Get(), *m_states, m_worldTeaPod[i], m_view, m_proj);
	}*/


	m_batch->Begin();//設定


	

	m_batch->End();//纏めて描画

    Present();//画面に反映させる
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    // Clear the views.
    m_d3dContext->ClearRenderTargetView(m_renderTargetView.Get(), Colors::CornflowerBlue);
    m_d3dContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    m_d3dContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());

    // Set the viewport.
    CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(m_outputWidth), static_cast<float>(m_outputHeight));
    m_d3dContext->RSSetViewports(1, &viewport);
}

// Presents the back buffer contents to the screen.
void Game::Present()
{
    // The first argument instructs DXGI to block until VSync, putting the application
    // to sleep until the next VSync. This ensures we don't waste any cycles rendering
    // frames that will never be displayed to the screen.
    HRESULT hr = m_swapChain->Present(1, 0);

    // If the device was reset we must completely reinitialize the renderer.
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
    {
        OnDeviceLost();
    }
    else
    {
        DX::ThrowIfFailed(hr);
    }
}

// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowSizeChanged(int width, int height)
{
    m_outputWidth = std::max(width, 1);
    m_outputHeight = std::max(height, 1);

    CreateResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 800;
    height = 600;
}

// These are the resources that depend on the device.
void Game::CreateDevice()
{
    UINT creationFlags = 0;

#ifdef _DEBUG
    creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    static const D3D_FEATURE_LEVEL featureLevels [] =
    {
        // TODO: Modify for supported Direct3D feature levels (see code below related to 11.1 fallback handling).
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1,
    };

    // Create the DX11 API device object, and get a corresponding context.
    HRESULT hr = D3D11CreateDevice(
        nullptr,                                // specify nullptr to use the default adapter
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        creationFlags,
        featureLevels,
        _countof(featureLevels),
        D3D11_SDK_VERSION,
        m_d3dDevice.ReleaseAndGetAddressOf(),   // returns the Direct3D device created
        &m_featureLevel,                        // returns feature level of device created
        m_d3dContext.ReleaseAndGetAddressOf()   // returns the device immediate context
        );

    if (hr == E_INVALIDARG)
    {
        // DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it.
        hr = D3D11CreateDevice(nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            creationFlags,
            &featureLevels[1],
            _countof(featureLevels) - 1,
            D3D11_SDK_VERSION,
            m_d3dDevice.ReleaseAndGetAddressOf(),
            &m_featureLevel,
            m_d3dContext.ReleaseAndGetAddressOf()
            );
    }

    DX::ThrowIfFailed(hr);

#ifndef NDEBUG
    ComPtr<ID3D11Debug> d3dDebug;
    if (SUCCEEDED(m_d3dDevice.As(&d3dDebug)))
    {
        ComPtr<ID3D11InfoQueue> d3dInfoQueue;
        if (SUCCEEDED(d3dDebug.As(&d3dInfoQueue)))
        {
#ifdef _DEBUG
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
#endif
            D3D11_MESSAGE_ID hide [] =
            {
                D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
                // TODO: Add more message IDs here as needed.
            };
            D3D11_INFO_QUEUE_FILTER filter = {};
            filter.DenyList.NumIDs = _countof(hide);
            filter.DenyList.pIDList = hide;
            d3dInfoQueue->AddStorageFilterEntries(&filter);
        }
    }
#endif

    // DirectX 11.1 if present
    if (SUCCEEDED(m_d3dDevice.As(&m_d3dDevice1)))
        (void)m_d3dContext.As(&m_d3dContext1);

    // TODO: Initialize device dependent objects here (independent of window size).
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateResources()
{
    // Clear the previous window size specific context.
    ID3D11RenderTargetView* nullViews [] = { nullptr };
    m_d3dContext->OMSetRenderTargets(_countof(nullViews), nullViews, nullptr);
    m_renderTargetView.Reset();
    m_depthStencilView.Reset();
    m_d3dContext->Flush();

    UINT backBufferWidth = static_cast<UINT>(m_outputWidth);
    UINT backBufferHeight = static_cast<UINT>(m_outputHeight);
    DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
    DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
    UINT backBufferCount = 2;

    // If the swap chain already exists, resize it, otherwise create one.
    if (m_swapChain)
    {
        HRESULT hr = m_swapChain->ResizeBuffers(backBufferCount, backBufferWidth, backBufferHeight, backBufferFormat, 0);

        if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
        {
            // If the device was removed for any reason, a new device and swap chain will need to be created.
            OnDeviceLost();

            // Everything is set up now. Do not continue execution of this method. OnDeviceLost will reenter this method 
            // and correctly set up the new device.
            return;
        }
        else
        {
            DX::ThrowIfFailed(hr);
        }
    }
    else
    {
        // First, retrieve the underlying DXGI Device from the D3D Device.
        ComPtr<IDXGIDevice1> dxgiDevice;
        DX::ThrowIfFailed(m_d3dDevice.As(&dxgiDevice));

        // Identify the physical adapter (GPU or card) this device is running on.
        ComPtr<IDXGIAdapter> dxgiAdapter;
        DX::ThrowIfFailed(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()));

        // And obtain the factory object that created it.
        ComPtr<IDXGIFactory1> dxgiFactory;
        DX::ThrowIfFailed(dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf())));

        ComPtr<IDXGIFactory2> dxgiFactory2;
        if (SUCCEEDED(dxgiFactory.As(&dxgiFactory2)))
        {
            // DirectX 11.1 or later

            // Create a descriptor for the swap chain.
            DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
            swapChainDesc.Width = backBufferWidth;
            swapChainDesc.Height = backBufferHeight;
            swapChainDesc.Format = backBufferFormat;
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.BufferCount = backBufferCount;

            DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = { 0 };
            fsSwapChainDesc.Windowed = TRUE;

            // Create a SwapChain from a Win32 window.
            DX::ThrowIfFailed(dxgiFactory2->CreateSwapChainForHwnd(
                m_d3dDevice.Get(),
                m_window,
                &swapChainDesc,
                &fsSwapChainDesc,
                nullptr,
                m_swapChain1.ReleaseAndGetAddressOf()
                ));

            DX::ThrowIfFailed(m_swapChain1.As(&m_swapChain));
        }
        else
        {
            DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
            swapChainDesc.BufferCount = backBufferCount;
            swapChainDesc.BufferDesc.Width = backBufferWidth;
            swapChainDesc.BufferDesc.Height = backBufferHeight;
            swapChainDesc.BufferDesc.Format = backBufferFormat;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.OutputWindow = m_window;
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;
            swapChainDesc.Windowed = TRUE;

            DX::ThrowIfFailed(dxgiFactory->CreateSwapChain(m_d3dDevice.Get(), &swapChainDesc, m_swapChain.ReleaseAndGetAddressOf()));
        }

        // This template does not support exclusive fullscreen mode and prevents DXGI from responding to the ALT+ENTER shortcut.
        DX::ThrowIfFailed(dxgiFactory->MakeWindowAssociation(m_window, DXGI_MWA_NO_ALT_ENTER));
    }

    // Obtain the backbuffer for this window which will be the final 3D rendertarget.
    ComPtr<ID3D11Texture2D> backBuffer;
    DX::ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));

    // Create a view interface on the rendertarget to use on bind.
    DX::ThrowIfFailed(m_d3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, m_renderTargetView.ReleaseAndGetAddressOf()));

    // Allocate a 2-D surface as the depth/stencil buffer and
    // create a DepthStencil view on this surface to use on bind.
    CD3D11_TEXTURE2D_DESC depthStencilDesc(depthBufferFormat, backBufferWidth, backBufferHeight, 1, 1, D3D11_BIND_DEPTH_STENCIL);

    ComPtr<ID3D11Texture2D> depthStencil;
    DX::ThrowIfFailed(m_d3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, depthStencil.GetAddressOf()));

    CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
    DX::ThrowIfFailed(m_d3dDevice->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, m_depthStencilView.ReleaseAndGetAddressOf()));

    // TODO: Initialize windows-size dependent objects here.
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.

    m_depthStencilView.Reset();
    m_renderTargetView.Reset();
    m_swapChain1.Reset();
    m_swapChain.Reset();
    m_d3dContext1.Reset();
    m_d3dContext.Reset();
    m_d3dDevice1.Reset();
    m_d3dDevice.Reset();

    CreateDevice();

    CreateResources();
}