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

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	Stage1* stage1_ = nullptr;
	Stage2* stage2_ = nullptr;
	Stage3* stage3_ = nullptr;
	Stage4* stage4_ = nullptr;
	Stage5* stage5_ = nullptr;

	uint32_t textureHandle_[20];

	size_t scene_ = TITLE;

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



	int RingFlag = 0; //枠のフラグ
	int PauseFlag = 0; //Pause画面のフラグ
	int GameTimer_ = 0;
	int StageTimer = 0;
	int StageTimerUpDown = 0;
	int Select = 0;
	int SelectFlag = 0;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
