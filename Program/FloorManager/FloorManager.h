#pragma once
#include "../../Engine/3D/Model.h"
#include "../../Engine/3D/Material.h"
#include "../../Engine/3D/WorldTransform.h"
#include "../Floor/Floor.h"

#include <vector>
#include "../../Engine/Collider/ColliderDebugDraw/ColliderDebugDraw.h"// コライダーデバッグ描画

class FloorManager
{

public: // メンバ関数

	/// <summary>
	/// デストラクタ
	/// </summary>
	~FloorManager();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	void Initialize(Model* model, Material* material);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Draw(const ViewProjection& viewProjection);

	/// <summary>
	/// 床追加
	/// </summary>
	void AddFloor(Vector3 position, Vector3 rotate, bool isMoving, bool isVertical);

	/// <summary>
	/// imgui表示
	/// </summary>
	void DrawImgui();

public: // アクセッサ

	/// <summary>
	/// 床リストゲッター
	/// </summary>
	/// <returns></returns>
	std::vector<Floor*> GetFloors() { return floors_; }

	/// <summary>
	/// デバッグ描画セッター
	/// </summary>
	/// <param name="colliderDebugDraw"></param>
	void SetColliderDebugDraw(ColliderDebugDraw* colliderDebugDraw) { colliderDebugDraw_ = colliderDebugDraw; }

private:

	// モデル
	Model* model_ = nullptr;
	// マテリアル
	Material* material_ = nullptr;

	// 床リスト
	std::vector<Floor*> floors_;

	// デバッグ描画
	ColliderDebugDraw* colliderDebugDraw_ = nullptr;

};
