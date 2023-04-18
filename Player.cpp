#include "Player.h"
#include <cassert>
#include "Procession.h"

void Player::Initialize(Model* model, Vector3 pos)
{
	input_ = Input::GetInstance();
	texture_ = TextureManager::Load("yellow.png");
	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;

	isMove_ = false;
	isMove2_ = false;

	// 行列更新
	worldTransform_.matWorld_ = Mat_Identity();
	worldTransform_.matWorld_ = MatWorld(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();

	viewProjection_.Initialize();
}

void Player::Update()
{
	Vector3 move = MyMathUtility::MySetVector3Zero();
	float moveSpeed = 0.4f;

	// キーボード入力による移動処理
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

	worldTransform_.translation_ += move;
	worldTransform_.Update(worldTransform_);
}

void Player::Draw(ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection_, texture_);
}

void Player::OnCollisionStage(bool collisionFlag) {
	if (collisionFlag) {
		worldTransform_.translation_ = prePos_;
		worldTransform_.Update(worldTransform_);
	}
	// 前フレーム座標
	prePos_ = worldTransform_.translation_;
}

Vector3 Player::GetWorldPosition()
{
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

void Player::Collision()
{
	isMove_ = true;
}
