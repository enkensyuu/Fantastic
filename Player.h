#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "MyMathUtility.h"
#include <memory>
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Player
{
public:
	void Initialize(Vector3 pos = { 0.0f, 0.0f, 0.0f });

	void Update(bool collisionFlag);

	void Draw(ViewProjection& viewProjection);

	void IsDead();

	Vector3 GetWorldPosition();

	bool GetStopMove() { return isMove_; }

	// 当たり判定
	void OnCollisionStage(bool collisionFlag);
	void Collision(Vector3 speed);

	void DethCollision();

	void GetStop();

	bool IsGetDead() { return isDead_; }

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	Input* input_ = nullptr;
	//デバッグテキスト
	DebugText* debugText_ = nullptr;

	//モデル
	Model* model_ = nullptr;

	// プレイヤーの直前のスピード
	float playerOldSpeedX;
	float playerOldSpeedY;

	// 前フレーム座標
	Vector3 prePos_{};
	// 半径
	float radius_ = 2.0f;
	//死亡フラグ
	bool isMove_ = false;
	bool isMove2_ = false;
	bool isDead_ = false;

	bool stopG_;

public: //アクセッサ、インライン関数
	float GetRadius() const { return radius_; }
	Vector3 playerSpeed;
	Vector3 returnSpeed;
	Vector3 acc;

	int stoptimer;
	int stoptimer2;
};


