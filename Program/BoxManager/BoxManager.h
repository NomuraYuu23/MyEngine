#pragma once
#include "../../Engine/3D/Model.h"
#include "../../Engine/3D/Material.h"
#include "../../Engine/3D/WorldTransform.h"
#include"../Box/Box.h"

#include<list>
#include "../../Engine/Collider/ColliderDebugDraw/ColliderDebugDraw.h"// コライダーデバッグ描画


class BoxManager{
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~BoxManager();

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
	void AddBox(TransformStructure box,bool isMoving, bool isVertical);

public: // アクセッサ

	/// <summary>
	/// 床リストゲッター
	/// </summary>
	/// <returns></returns>
	std::list<Box*> GetBoxes_() { return boxes_; }

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
	std::list<Box*> boxes_;

	// デバッグ描画
	ColliderDebugDraw* colliderDebugDraw_ = nullptr;
};

