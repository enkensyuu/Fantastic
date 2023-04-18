#pragma once
#include <sstream>
#include "Model.h"
#include "MyMathUtility.h"

class stage {
private: // 定数
	static const int STAGE_WIDTH = 32;
	static const int STAGE_HEIGHT = 18;

public:
	// 列挙
	enum STAGE {
		NONE,		// 穴
		BLOCK,		// 地面, 壁
		GOAL,		// ゴール
	};

	// 構造体
	struct StageData {
		WorldTransform worldTransform_;	// 座標
		int type_;	// ブロックの種類
		int line_;
		int row_;
	};

public:
	// デストラクタ
	~stage();

	// 初期化
	void Initialize(Model* model);

	// ステージ初期化
	void StageInitialize(const std::string stageNum);

	// 更新
	void Update();

	// 描画
	void Draw(ViewProjection viewProjection);

	// 足元のブロックを判別する
	void CheckBlock(int line, int row);

	// 床からはみ出しているか
	bool CheckFloorBlock(int line, int row);

	// 座標ゲッター
	Vector3 GetBlockPosition(int line, int row);

private:
	// ステージ床の読み込み
	void LoadFloorBlock();

	// ステージファイル読み込み
	void LoadStageData(const std::string stageNum);

	// ステージ読み込み
	void LoadStageCommands();

	// ブロック初期化
	void InitializeStageBlock(std::unique_ptr<StageData>& block, Vector3 pos, int line, int row);

	// リストにブロックを追加
	void PushStageBlockList(std::list<std::unique_ptr<StageData>>& blocks_, int type, int line, int row, float depth);

private:

	WorldTransform worldTransform;

	// モデル
	Model* model_ = nullptr;
	Model* modelFloor_ = nullptr;
	Model* modelGoal_ = nullptr;
	// テクスチャハンドル
	int32_t textureHandle_ = 0u;

	// ファイルコマンド
	std::stringstream stageCommands;
	// ワールド変換データ
	std::list<std::unique_ptr<StageData>> stageBlocks_;
	std::list<std::unique_ptr<StageData>> floorBlocks_;

	// ブロックの倍率(Scale)
	float magnification_ = 2.0f;
	// ブロックの半径半径
	float radius_ = 2.0f;
	// ゴールフラグ
	bool isGoal_ = false;
	bool isSwitchDrawR_ = false;
	bool isSwitchDrawB_ = false;

public: // アクセッサ
	float GetRadius() { return radius_; }
	bool GetIsGoal() { return isGoal_; }
};