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
	void Initialize();

	//�X�V
	void Update(bool collisionFlag);

	void Draw(ViewProjection& viewProjection);

	// ���S
	void IsDead() { isDead_ = true; }
	Vector3 GetWorldPosition();

	// �����蔻��
	void OnCollisionStage(bool collisionFlag);
	void Collision(Vector3 speed);

	void DethCollision();

	void GetStop();

	bool IsGetDead() { return isDead_; }


private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	Input* input_ = nullptr;
	//�f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;

	//���f��
	Model* model_ = nullptr;

	// �O�t���[�����W
	Vector3 prePos_{};
	// ���a
	float radius_ = 2.0f;
	//���S�t���O
	bool isMove_ = false;
	bool isMove2_ = false;
	bool isDead_ = false;

	bool stopG_;

public: //�A�N�Z�b�T�A�C�����C���֐�
	bool IsDead() const { return isDead_; }
	Vector3 GetPosition() const { return worldTransform_.translation_; }
	float GetRadius() const { return radius_; }
	Vector3 playerSpeed;
	Vector3 returnSpeed;
	Vector3 acc;

	int stoptimer;
	int stoptimer2;
};


