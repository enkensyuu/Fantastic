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
#include "Goal.h"

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
	bool CollisionKeyFlag(SilverKey* p, stage* s);

private: // メンバ変数
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	DebugText* debugText_ = nullptr;

	void CheckAllCollisions();

	bool GetClose() { return closeGame_; }

  private: // メンバ変数
    WorldTransform worldTransform_;
	ViewProjection viewProjection_;

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
	uint32_t backGroundStage1 = 0;
	uint32_t backGroundStage2 = 0;
	uint32_t backGroundStage3 = 0;
	uint32_t backGroundStage4 = 0;
	uint32_t backGroundStage5 = 0;

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

	Goal* goal_ = nullptr;

	uint32_t textureHandle_[20];

	size_t scene_ = TITLE;

	bool isGoal_ = false;
	bool isGetKey_ = false;
	bool isOpen_;
	bool isKeyOpen_;

	int stageFlag;

	Sprite* Explanation_ = nullptr; //説明 
	Sprite* Operation_ = nullptr;  //ゲーム説明
	Sprite* Title_ = nullptr;
	Sprite* Space_ = nullptr; //SPACE文字
	Sprite* StageChoice_ = nullptr; //ステージ選択
	Sprite* BackGroudStage1_ = nullptr; //ステージ1(背景)
	Sprite* BackGroudStage2_ = nullptr; //ステージ2(背景)
	Sprite* BackGroudStage3_ = nullptr; //ステージ3(背景)
	Sprite* BackGroudStage4_ = nullptr; //ステージ4(背景)
	Sprite* BackGroudStage5_ = nullptr; //ステージ5(背景)
	Sprite* Waku_ = nullptr; //ステージ選択の枠 
	Sprite* Waku2_ = nullptr; //ステージ選択の枠(2) 
	Sprite* Waku3_ = nullptr; //ステージ選択の枠(3) 
	Sprite* Waku4_ = nullptr; //ステージ選択の枠(4) 
	Sprite* Waku5_ = nullptr; //ステージ選択の枠(5) 
	Sprite* Pause_ = nullptr; //Pause
	Sprite* PauseScene_ = nullptr; //Pause画面
	Sprite* PauseSelect_ = nullptr; //PauseSelect画面
	Sprite* PauseSelect2_ = nullptr; //PauseSelect画面(2)
	Sprite* PauseSelect3_ = nullptr; //PauseSelect画面(3)
	Sprite* PauseSelect4_ = nullptr; //PauseSelect画面(4)
	Sprite* PauseSelect5_ = nullptr; //PauseSelect画面(5)
	Sprite* PauseSelect6_ = nullptr; //PauseSelect画面(6)
	Sprite* GameOver_ = nullptr; //ゲームオーバー文字



	int RingFlag = 0; //枠のフラグ
	int PauseFlag = 0; //Pause画面のフラグ
	int GameTimer_ = 0;
	int StageTimer = 0;
	int StageTimerUpDown = 0;
	int Select = 0;
	int SelectFlag = 0;
	int SceneStageFlag1 = 0; //ステージ1フラグ
	int SceneStageFlag2 = 0; //ステージ2フラグ
	int SceneStageFlag3 = 0; //ステージ3フラグ
	int SceneStageFlag4 = 0; //ステージ4フラグ
	int SceneStageFlag5 = 0; //ステージ5フラグ
	

	//SE
	uint32_t StageSelectSE_ = 0;
	uint32_t StageSEHandle_ = 0;
	uint32_t StageHandleFlag = false;


	//BGM
	uint32_t TitleBGM_ = 0;
	uint32_t TitleBGMHandle_ = 0;
	uint32_t TitleHandleFlag = false;

	uint32_t Stage1BGM_ = 0;
	uint32_t Stage1BGMHandle_ = 0;
	uint32_t Stage1HandleFlag = false;

	uint32_t Stage2BGM_ = 0;
	uint32_t Stage2BGMHandle_ = 0;
	uint32_t Stage2HandleFlag = false;

	uint32_t Stage3BGM_ = 0;
	uint32_t Stage3BGMHandle_ = 0;
	uint32_t Stage3HandleFlag = false;

	uint32_t Stage4BGM_ = 0;
	uint32_t Stage4BGMHandle_ = 0;
	uint32_t Stage4HandleFlag = false;

	uint32_t Stage5BGM_ = 0;
	uint32_t Stage5BGMHandle_ = 0;
	uint32_t Stage5HandleFlag = false;


	bool closeGame_;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
