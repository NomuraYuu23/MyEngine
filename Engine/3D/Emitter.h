#pragma once
#include "TransformStructure.h"
#include "Particle.h"
#include <list>

class Emitter
{

public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const TransformStructure& transform, float lifeTime, uint32_t particleModelNum);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	std::list<Particle*> Emit();

	Particle* MakeParticle();

public: // アクセッサ

	bool GetToEmit() { return toEmit_; }

	void SetToEmit(bool toEmit) { toEmit_ = toEmit; }

	/// <summary>
	/// 死んでいるか
	/// </summary>
	/// <returns></returns>
	bool IsDead() { return isDead_; }

	uint32_t GetParticleModelNum() { return particleModelNum_; };

protected:

	// トランスフォーム
	TransformStructure transform_;
	// 発生させるインスタンス数
	uint32_t instanceCount_;
	// 発生頻度
	float frequency_;
	// 発生時間
	float frequencyTime_;
	// 生存時間
	float lifeTime_;
	// 発生してからの経過時間
	float currentTime_;
	// エミットする
	bool toEmit_;

	// 死んでいるか
	bool isDead_;

	// モデルネーム
	uint32_t particleModelNum_;

};
