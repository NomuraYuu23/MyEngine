#pragma once

#include "../IScene/IScene.h"
#include <memory>

class AbstractSceneFactory {

public: //メンバ関数

	// 仮想デストラクタ
	virtual ~AbstractSceneFactory() = default;
	// シーン生成
	virtual IScene* CreateScene(int sceneName) = 0;

};
