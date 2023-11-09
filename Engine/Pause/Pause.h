#pragma once
#include "../Input/Input.h"
#include "../2D/Sprite.h"
#include <array>

/// <summary>
/// ポーズ
/// </summary>
class Pause
{

public: // サブクラス

	// ポーズメニュー
	enum PauseMenu{
		kGoToTitle,       // タイトルへ
		kReturnToGame,    // ゲームに戻る
		kCountOfPauseMenu // 使用不可
	};

	// ポーズで使うテクスチャ番号
	enum PauseTextureNo{
		kPausing,              // ポーズ中
		kCountOfPauseTextureNo // 使用不可
	};

public: // メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const std::array<uint32_t, kCountOfPauseTextureNo>& textureHandles);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ関数

	/// <summary>
	/// ポーズ画面の切り替え
	/// </summary>
	void PoseSwitching();

	/// <summary>
	/// ポーズメニュー操作
	/// </summary>
	void PauseMenuOperation();

public: // アクセッサ

	bool IsPause() { return isPause_; }

private: // メンバ変数

	// 入力
	Input* input_ = nullptr;

	// ポーズしているか
	bool isPause_;
	// ポーズメニューでどこを選択しているか
	int pauseMenuSelect_;

	// テクスチャハンドル
	std::array<uint32_t, kCountOfPauseTextureNo> textureHandles_;

private: // メンバ変数(スプライト)

	// ポーズ中
	std::unique_ptr<Sprite> pausingSprite_;

};

