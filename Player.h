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
#include "MyMathUtility.h"

class Player
{
public:
	void Initialize(Model* model, Vector3 pos = { 0.0f, 0.0f, 0.0f });

	void Update();

	void Draw(ViewProjection& viewProjection);

	Vector3 GetWorldPosition();

	void Collision();

	void OnCollisionStage(bool collisionFlag);

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	Input* input_ = nullptr;
	Model* model_ = nullptr;
	uint32_t texture_ = 0;

	bool isMove_ = false;
	bool isMove2_ = false;

	Vector3 playerSpeed;
	Vector3 returnSpeed;

	int stoptimer;
	int stoptimer2;

	// �O�t���[�����W
	Vector3 prePos_{};

	// ���a
	float radius_ = 1.5f;

	//���S�t���O
	bool isDead_;

public: //�A�N�Z�b�T�A�C�����C���֐�
	bool IsDead() const { return isDead_; }
	Vector3 GetPosition() const { return worldTransform_.translation_; }
	float GetRadius() const { return radius_; }
};