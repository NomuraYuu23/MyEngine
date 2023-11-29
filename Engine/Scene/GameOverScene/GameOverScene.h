#pragma once
#include "../IScene/IScene.h"
#include "../../../Program/UI/UIData.h"

class GameOverScene : public IScene
{

public: // メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize() override;

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() override;

private: // メンバ関数

	/// <summary>
	/// モデルクリエイト
	/// </summary>
	void ModelCreate() override;

	/// <summary>
	/// マテリアルクリエイト
	/// </summary>
	void MaterialCreate() override;

	/// <summary>
	/// テクスチャロード
	/// </summary>
	void TextureLoad() override;

private:

	void SelectChange();

	void Decision();

private: // メンバ変数

	UIData backGround_;

	UIData goToSelect_;

	UIData respawn_;

	bool isRespawn_ = true;
	
	// 選択クールタイム
	float selectCooltime_ = 0.3f;

	// 選択クールタイム
	float selectElapsedCooltime_ = 0.0f;

};
