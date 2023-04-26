#pragma once
#include "Audio.h"
#include "DebugCamera.h"
#include "DebugText.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "stage.h"
#include "Player.h"
#include <memory>
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Scene.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "Stage4.h"
#include "Stage5.h"
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

	void Parameter(const Vector3& playerPos1, const int& stageNum);

	bool CollisionStageFlag(Player* p, stage* s);

private: // メンバ変数
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	DebugText* debugText_ = nullptr;

	void CheckAllCollisions();

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// テクスチャハンドル
	uint32_t titleTexture_ = 0;
	uint32_t howToPlayTexture_ = 0;
	uint32_t stageClearTexture_ = 0;
	uint32_t gameOverTexture_ = 0;
	uint32_t gameClearTexture_ = 0;

	// 背景用
	uint32_t backGroundTexture1 = 0;
	uint32_t backGroundTexture2 = 0;
	uint32_t backGroundTexture3 = 0;
	uint32_t backGroundTexture4 = 0;
	uint32_t backGroundTexture5 = 0;
	uint32_t backGroundTexture6 = 0;
	// スプライト
	Sprite* title_ = nullptr;
	Sprite* howtoplay_ = nullptr;
	Sprite* stageClear_ = nullptr;
	Sprite* gameOver_ = nullptr;
	Sprite* gameClear_ = nullptr;

	// 背景
	Sprite* backGround1_ = nullptr;
	Sprite* backGround2_ = nullptr;
	Sprite* backGround3_ = nullptr;
	Sprite* backGround4_ = nullptr;
	Sprite* backGround5_ = nullptr;
	Sprite* backGround6_ = nullptr;

	// サウンドデータハンドル
	uint32_t titleBgm_ = 0;
	uint32_t doneSe_ = 0;
	// バネ
	uint32_t springSe_ = 0;

	// 3Dモデル
	Model* model_ = nullptr;

	// カメラ上方向の角度
	float viewAngle = 0.0f;

	// プレイヤー
	Player* player_ = nullptr;

	// モデル
	Model* modelSkydome_ = nullptr;
	// ステージ
	stage* stage_ = nullptr;

	// シーン用ファイルネーム
	const std::string filename_[7] = {
	  "0",
	  "1",
	  "2",
	  "3",
	  "4",
	  "5",
	  "6" }; // 0は使わない

	// デバッグカメラ有効化
	bool isDebugCameraActive_ = false;
	// クリアしたか
	bool isClear = false;
	Stage1* stage1_ = nullptr;
	Stage2* stage2_ = nullptr;
	Stage3* stage3_ = nullptr;
	Stage4* stage4_ = nullptr;
	Stage5* stage5_ = nullptr;

	Balloon* balloon_ = nullptr;

	SilverKey* silverKey_ = nullptr;

	WindPower* windPower_ = nullptr;

	MagmaBlock* magmaBlock_ = nullptr;

	Vector3 playerSpeed_;
	Vector3 balloonSpeed_;
	Vector3 silverKeySpeed_;
	Vector3 goldKeySpeed;

	Door* door_ = nullptr;

	size_t scene_ = TITLE;

	bool isGetGoldKey_ = false;
	bool isOpen_;
	bool isKeyOpen_;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
