#include "MyGame.h"

void MyGame::Initialize()
{


	//ゲームウィンドウの作成
	win = WinApp::GetInstance();
	win->CreateGameWindow();

	//DirectX初期化
	dxCommon = DirectXCommon::GetInstance();
	dxCommon->Initialize(win);

	//入力デバイス
	input = Input::GetInstance();
	input->Initialize(win->GetHInstance(), win->GetHwnd());

	GraphicsPipelineState::InitializeGraphicsPipeline(dxCommon->GetDevice());

	//テクスチャマネージャー
	TextureManager::GetInstance()->Initialize(dxCommon->GetDevice());

	// スプライト静的初期化
	Sprite::StaticInitialize(dxCommon->GetDevice(), GraphicsPipelineState::sRootSignature, GraphicsPipelineState::sPipelineState[GraphicsPipelineState::Sprite]);

	// モデル静的初期化
	Model::StaticInitialize(dxCommon->GetDevice(), GraphicsPipelineState::sRootSignature, GraphicsPipelineState::sPipelineState[GraphicsPipelineState::Model]);

	// マテリアル静的初期化
	Material::StaticInitialize(dxCommon->GetDevice());

	// 光源静的初期化
	DirectionalLight::StaticInitialize(dxCommon->GetDevice());

	//サウンド
	audio = Audio::GetInstance();
	audio->Initialize();

	// ImGuiマネージャー
	imGuiManager = ImGuiManager::GetInstance();
	imGuiManager->Initialize(win, dxCommon, TextureManager::GetInstance());

	//グローバル変数ファイル読み込み
	GlobalVariables::GetInstance()->LoadFiles();

	//ゲームシーン
	sceneManager = std::make_unique<SceneManager>();
	sceneManager->Initialize();

}

void MyGame::Finalize()
{

	// サウンド後始末
	audio->Finalize();

	//色々な解放処理の前に書く
	imGuiManager->Finalize();

	//ゲームウィンドウの破棄
	win->TerminateGameWindow();

}

void MyGame::Update()
{

	//Windowにメッセージが来てたら最優先で処理させる
	if (win->ProcessMessage() || input->TriggerKey(DIK_ESCAPE)) {
		endRequst_ = true;
	}

	//入力デバイス
	input->Update();
	if (input->PushKey(DIK_SPACE)) {
		input->JoystickConnected(win->GetHwnd());
	}

	//ゲームの処理 
	//ImGui
	imGuiManager->Begin();

	//開発用UIの処理。実際に開発用のUIを出す場合はここをゲーム固有の処理に置き換える
	//ImGui::ShowDemoWindow();
	// グローバル変数の更新
	GlobalVariables::GetInstance()->Update();

	// ゲームシーン更新
	sceneManager->Update();

}

void MyGame::Draw()
{

	//描画前処理
	dxCommon->PreDraw();

	//ゲームシーン描画処理
	sceneManager->Draw();

	imGuiManager->End();

	// シェーダーリソースビューをセット
	TextureManager::GetInstance()->SetGraphicsRootDescriptorTable(dxCommon->GetCommadList(), 2, 0);
	//実際のcommandListのImGuiの描画コマンドを積む
	imGuiManager->Draw();

	//描画後処理
	dxCommon->PostDraw();

}