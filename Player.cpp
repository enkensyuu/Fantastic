#include "Player.h"
#include <cassert>

bool Player::isDeads_ = false;

void Player::Initialize(Model* model, Vector3 pos) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	//�V���O���g���C���X�^���X���擾
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	// �����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
}

void Player::Update() {
	Vector3 move = MyMathUtility::MySetVector3Zero();
	float moveSpeed = 1.0f;

	// �L�[�{�[�h���͂ɂ��ړ�����
	Matrix4 matTrans = MyMathUtility::MySetMatrix4Identity();
	if (input_->PushKey(DIK_A)) {
		move.x = -moveSpeed;
	}
	if (input_->PushKey(DIK_D)) {
		move.x = moveSpeed;
	}
	if (input_->PushKey(DIK_W)) {
		move.y = moveSpeed;
	}
	if (input_->PushKey(DIK_S)) {
		move.y = -moveSpeed;
	}
	if (input_->PushKey(DIK_J)) {
		move.z = moveSpeed;
	}
	if (input_->PushKey(DIK_U)) {
		move.z = -moveSpeed;
	}

	worldTransform_.translation_ += move;
	worldTransform_.Update(worldTransform_);
}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}

void Player::OnCollisionStage(bool collisionFlag) {
	if (collisionFlag) {
		worldTransform_.translation_ = prePos_;
		worldTransform_.Update(worldTransform_);
	}
	// �O�t���[�����W
	prePos_ = worldTransform_.translation_;
}