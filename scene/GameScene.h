#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Scene.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "Stage4.h"
#include "Stage5.h"
#include "Player.h"
#include "Balloon.h"
#include "SilverKey.h"
#include "WindPower.h"
#include "MagmaBlock.h"
#include "Door.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void CheckAllCollisions();

private: // メンバ変数
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	Stage1* stage1_ = nullptr;
	Stage2* stage2_ = nullptr;
	Stage3* stage3_ = nullptr;
	Stage4* stage4_ = nullptr;
	Stage5* stage5_ = nullptr;

	Player* player_ = nullptr;

	Balloon* balloon_ = nullptr;

	SilverKey* silverKey_ = nullptr;

	WindPower* windPower_ = nullptr;

	MagmaBlock* magmaBlock_ = nullptr;

	Door* door_ = nullptr;

	size_t scene_ = TITLE;

	bool isGetGoldKey_ = false;
	bool isOpen_;
	bool isKeyOpen_;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
