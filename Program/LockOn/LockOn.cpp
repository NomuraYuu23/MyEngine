#include "LockOn.h"
#include "../../Engine/Input/Input.h"
#include <cmath>
#include "../../Engine/2D/ImguiManager.h"

void LockOn::Initialize(uint32_t textureHandle)
{

	//スプライトの生成関数
	lockOnMark_ = std::make_unique<Sprite>();
	lockOnMark_.reset(
		Sprite::Create(textureHandle, { 0.0f,0.0f }, { 1.0f,1.0f,1.0f,1.0f }));

}

void LockOn::Update(const std::list<Enemy*>& enemies, Player* player, const ViewProjection& viewProjection)
{

	Input* input = Input::GetInstance();
	Vector3Calc* v3Calc = Vector3Calc::GetInstance();
	Matrix4x4Calc* m4Calc = Matrix4x4Calc::GetInstance();

	// ロックオンモード変更する
	if (input->TriggerJoystick(9)) {
		LockOnModeChange();
	}


	// ロックオン状態なら
	if (target_) {
		// ロックオン解除処理
		if (input->TriggerJoystick(4) && !isAutomatic_) {
			// ロックオンを外す
			target_ = nullptr;
		}
		// 範囲外判定
		else if (OutOfRangeJudgment(player,viewProjection)) {
			// ロックオンを外す
			target_ = nullptr;
		}
		else if (input->TriggerJoystick(5)) {
			// ロックオン対象の検索
			// ロックオン対象の絞り込み
			// 目標
			std::list<std::pair<float, Enemy*>> targets;

			// 全ての敵に対して順にロックオン判定
			for (Enemy* enemy : enemies) {
				// 敵ロックオン座標取得
				Vector3 enemyWorldPosition = {
					enemy->GetWorldTransform().worldMatrix_.m[3][0],
					enemy->GetWorldTransform().worldMatrix_.m[3][1],
					enemy->GetWorldTransform().worldMatrix_.m[3][2]
				};

				//プレイヤー
				Vector3 playerWorldPosition = {
					player->GetWorldTransform().worldMatrix_.m[3][0],
					player->GetWorldTransform().worldMatrix_.m[3][1],
					player->GetWorldTransform().worldMatrix_.m[3][2]
				};


				Vector3 dirEnemy = v3Calc->Normalize(v3Calc->Subtract(enemyWorldPosition, viewProjection.transform_.translate));
				Vector3 dirPlayer = v3Calc->Normalize(v3Calc->Subtract(playerWorldPosition, viewProjection.transform_.translate));
				float dot = v3Calc->Dot(dirEnemy, dirPlayer);

				float distance = v3Calc->Length(v3Calc->Subtract(enemyWorldPosition, playerWorldPosition));
				// 距離条件チェック
				if (minDistance_ <= distance && distance <= maxDistance_ && dot > 0.0f && enemy != target_) {

					targets.emplace_back(std::make_pair(distance, enemy));

				}

				// ロックオン対象をリセット
				target_ = nullptr;
				if (targets.size() > 0) {
					// 距離で昇順にソート
					targets.sort([](auto& pair1, auto& pair2) {return pair1.first < pair2.first; });
					// ソートの結果一番近い敵をロックオン対象とする
					target_ = targets.front().second;
				}
			}
		}

	}
	else {
		// ロックオン対象の検索
		if (input->TriggerJoystick(4) || isAutomatic_) {
			// ロックオン対象の検索
			// ロックオン対象の絞り込み
			// 目標
			std::list<std::pair<float, Enemy*>> targets;

			// 全ての敵に対して順にロックオン判定
			for (Enemy* enemy : enemies) {
				// 敵ロックオン座標取得
					Vector3 enemyWorldPosition = {
						enemy->GetWorldTransform().worldMatrix_.m[3][0],
						enemy->GetWorldTransform().worldMatrix_.m[3][1],
						enemy->GetWorldTransform().worldMatrix_.m[3][2]
				};

				//プレイヤー
				Vector3 playerWorldPosition = {
					player->GetWorldTransform().worldMatrix_.m[3][0],
					player->GetWorldTransform().worldMatrix_.m[3][1],
					player->GetWorldTransform().worldMatrix_.m[3][2]
				};

				Vector3 dirEnemy = v3Calc->Normalize(v3Calc->Subtract(enemyWorldPosition, viewProjection.transform_.translate));
				Vector3 dirPlayer = v3Calc->Normalize(v3Calc->Subtract(playerWorldPosition, viewProjection.transform_.translate));
				float dot = v3Calc->Dot(dirEnemy, dirPlayer);

				float distance = v3Calc->Length(v3Calc->Subtract(enemyWorldPosition, playerWorldPosition));
				// 距離条件チェック
				if (minDistance_ <= distance && distance <= maxDistance_ && dot > 0.0f) {

					targets.emplace_back(std::make_pair(distance, enemy));

				}


				// ロックオン対象をリセット
				target_ = nullptr;
				if (targets.size() > 0) {
					// 距離で昇順にソート
					targets.sort([](auto& pair1, auto& pair2) {return pair1.first < pair2.first; });
					// ソートの結果一番近い敵をロックオン対象とする
					target_ = targets.front().second;
				}

			}



		}
	}

	// ロックオン状態なら
	if (target_) {
		// ロックオンマークの座標計算
		// 敵のロックオン座標取得
		Vector3 positionWorld = {
			target_->GetWorldTransform().worldMatrix_.m[3][0],
			target_->GetWorldTransform().worldMatrix_.m[3][1],
			target_->GetWorldTransform().worldMatrix_.m[3][2]
		};
		// ワールド座標からスクリーン座標に変換
		Matrix4x4 viewPort = m4Calc->MakeViewportMatrix(0,0,WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);
		Matrix4x4 matViewProjectionViewPort = m4Calc->Multiply(viewProjection.viewProjectionMatrix_, viewPort);
		Vector3 positionScreen = m4Calc->Transform(positionWorld, matViewProjectionViewPort);
		// Vector2に格納
		Vector2 positionScreenV2(positionScreen.x, positionScreen.y);
		// スプライトの座標を設定
		lockOnMark_->SetPosition(positionScreenV2);
	}

}

void LockOn::Draw()
{

	if (target_) {
		lockOnMark_->Draw();
	}

#ifdef _DEBUG

	ImGuiDraw();

#endif // _DEBUG

}

Vector3 LockOn::GetTargetPosition() const
{
	
	if (target_) {
		Vector3 position = { 
			target_->GetWorldTransform().worldMatrix_.m[3][0],
			target_->GetWorldTransform().worldMatrix_.m[3][1],
			target_->GetWorldTransform().worldMatrix_.m[3][2] 
		};
		return position;
	}

	return Vector3();

}

void LockOn::Restart()
{

	// ロックオンを外す
	target_ = nullptr;
	isAutomatic_ = false;

}

bool LockOn::OutOfRangeJudgment(Player* player, const ViewProjection& viewProjection)
{

	Vector3Calc* v3Calc = Vector3Calc::GetInstance();
	Matrix4x4Calc* m4Calc = Matrix4x4Calc::GetInstance();

	// 敵ロックオン座標取得
	Vector3 enemyWorldPosition = {
		target_->GetWorldTransform().worldMatrix_.m[3][0],
		target_->GetWorldTransform().worldMatrix_.m[3][1],
		target_->GetWorldTransform().worldMatrix_.m[3][2]
	};

	//プレイヤー
	Vector3 playerWorldPosition = {
		player->GetWorldTransform().worldMatrix_.m[3][0],
		player->GetWorldTransform().worldMatrix_.m[3][1],
		player->GetWorldTransform().worldMatrix_.m[3][2]
	};

	Vector3 dirEnemy = v3Calc->Normalize(v3Calc->Subtract(enemyWorldPosition, viewProjection.transform_.translate));
	Vector3 dirPlayer = v3Calc->Normalize(v3Calc->Subtract(playerWorldPosition, viewProjection.transform_.translate));
	float dot = v3Calc->Dot(dirEnemy, dirPlayer);

	float distance = v3Calc->Length(v3Calc->Subtract(enemyWorldPosition, playerWorldPosition));
	// 距離条件チェック
	if (minDistance_ <= distance && distance <= maxDistance_ && dot > 0.0f) {

		return false;

	}

	return true;

}

void LockOn::LockOnModeChange()
{

	if (isAutomatic_) {
		isAutomatic_ = false;
	}
	else {
		isAutomatic_ = true;
	}

	target_ = nullptr;

}

void LockOn::ImGuiDraw()
{

	ImGui::Begin("LockOnMode");
	if (isAutomatic_) {
		ImGui::Text("Automatic");
	}
	else {
		ImGui::Text("Manual");
	}
	ImGui::End();

}