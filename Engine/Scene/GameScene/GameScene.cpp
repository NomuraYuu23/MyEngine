#include "GameScene.h"
#include "../../base/WinApp.h"
#include "../../base/TextureManager.h"
#include "../../2D/ImguiManager.h"
#include "../../base/D3DResourceLeakChecker.h"

/// <summary>
/// 初期化
/// </summary>
void GameScene::Initialize() {

	// デバッグ描画
	colliderDebugDraw_ = std::make_unique<ColliderDebugDraw>();
	colliderSphereModel_.reset(Model::Create("Resources/TD2_November/collider/sphere/", "sphere.obj", dxCommon_));
	colliderBoxModel_.reset(Model::Create("Resources/TD2_November/collider/box/", "box.obj", dxCommon_));
	std::vector<Model*> colliderModels = { colliderSphereModel_.get(),colliderBoxModel_.get(),colliderBoxModel_.get() };
	colliderMaterial_.reset(Material::Create());
	colliderDebugDraw_->Initialize(colliderModels, colliderMaterial_.get());

	// ビュープロジェクション
	viewProjection_.transform_.translate = { 0.0f,23.0f,-35.0f };
	viewProjection_.transform_.rotate = { 0.58f,0.0f,0.0f };

}

/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update(){
	ImguiDraw();
	//光源
	DirectionalLightData directionalLightData;
	directionalLightData.color = { 1.0f,1.0f,1.0f,1.0f };
	directionalLightData.direction = { 0.0f, -1.0f, 0.0f };
	directionalLightData.intencity = 1.0f;
	directionalLight_->Update(directionalLightData);

	viewProjection_.UpdateMatrix();

	// デバッグカメラ
	DebugCameraUpdate();
	
	// デバッグ描画
	colliderDebugDraw_->Update();

}

/// <summary>
/// 描画処理
/// </summary>
void GameScene::Draw() {

	//ゲームの処理 

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(dxCommon_->GetCommadList());

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();


#pragma endregion

	Model::PreDraw(dxCommon_->GetCommadList());

	//光源
	directionalLight_->Draw(dxCommon_->GetCommadList());
	//3Dオブジェクトはここ

#ifdef _DEBUG

	// デバッグ描画
	colliderDebugDraw_->Draw(viewProjection_);

#endif // _DEBUG

	Model::PostDraw();

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(dxCommon_->GetCommadList());
	

	//背景
	//前景スプライト描画

	// 前景スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion

}

void GameScene::ImguiDraw(){
#ifdef _DEBUG
#endif // _DEBUG
}

void GameScene::DebugCameraUpdate()
{

#ifdef _DEBUG
	if (input_->TriggerKey(DIK_RETURN)) {
		if (isDebugCameraActive_) {
			isDebugCameraActive_ = false;
		}
		else {
			isDebugCameraActive_ = true;
		}
	}

	// カメラの処理
	if (isDebugCameraActive_) {
		// デバッグカメラの更新
		debugCamera_->Update();
		// デバッグカメラのビュー行列をコピー
		viewProjection_ = debugCamera_->GetViewProjection();
		// ビュー行列の転送
		viewProjection_.UpdateMatrix();
	}
#endif

}