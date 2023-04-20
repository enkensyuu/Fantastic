#pragma once
#include "Audio.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "MyMathUtility.h"
#include <memory>

class Player {
public:
	//初期化
	void Initialize(Model* model, Vector3 pos = { 0.0f, 0.0f, 0.0f });

	//更新
	void Update();

	//描画
	void Draw(ViewProjection& viewProjection);

	// 死亡
	void IsDead() { isDead_ = true; }

	// 当たり判定
	void OnCollisionStage(bool collisionFlag);

private:
	//インプット
	Input* input_ = nullptr;
	//デバッグテキスト
	DebugText* debugText_ = nullptr;

	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// ワールド変換データ
	WorldTransform worldTransform_;
	// 前フレーム座標
	Vector3 prePos_{};
	// 半径
	float radius_ = 2.0f;
	//死亡フラグ
	bool isDead_;
	static bool isDeads_;

public: //アクセッサ、インライン関数
	bool IsDead() const { return isDead_; }
	Vector3 GetPosition() const { return worldTransform_.translation_; }
	float GetRadius() const { return radius_; }

};