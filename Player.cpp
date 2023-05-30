#include "Player.h"
#include <cassert>
#include "Procession.h"

void Player::Initialize(Vector3 pos)
{
	debugText_ = DebugText::GetInstance();

	model_ = Model::CreateFromOBJ("player");
	playerSpeed.x = 0.0f;

	worldTransform_.Initialize();

	worldTransform_.scale_ = { 2.0f,2.0f,2.0f };

	worldTransform_.translation_ = pos;
	isMove_ = false;
	isDead_ = false;

	// 行列更新
	worldTransform_.matWorld_ = Mat_Identity();
	worldTransform_.matWorld_ = MatWorld(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();

	viewProjection_.Initialize();
}

void Player::Update(bool collisionFlag) {

	worldTransform_.translation_ += playerSpeed;

	if (!stopG_)
	{
		playerSpeed.y -= 0.01f;
	}
	else if (stopG_ && playerSpeed.x >= 0.01)
	{
		playerSpeed.y = 0.0f;
	}

	if (isMove_)
	{
		if (playerSpeed.x >= 0.002f)
		{
			playerSpeed.x -= 0.002f;
		}
		else if (playerSpeed.x <= -0.002f)
		{
			playerSpeed.x += 0.002f;
		}

		if (playerSpeed.y >= 0.004f)
		{
			playerSpeed.y -= 0.004f;
		}

		if (playerSpeed.x <= 0.22f && playerSpeed.x >= 0.0f || playerSpeed.x >= -0.22f && playerSpeed.x <= 0.0f)
		{
			playerSpeed.x = 0.0f;
		}

		if (playerSpeed.x == 0.0f)
		{
			isMove_ = false;
		}

		
	}


	// 行列更新
	worldTransform_.matWorld_ = Mat_Identity();
	worldTransform_.matWorld_ = MatWorld(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();
	worldTransform_.TransferColorMatrix();
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

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}

void Player::IsDead()
{
	if (worldTransform_.translation_.x <= -5.0f || worldTransform_.translation_.x >= 154.0f
		|| worldTransform_.translation_.y <= -7.0f)
	{
		isDead_ = true;
	}
}

void Player::Collision(Vector3 speed)
{
	isMove_ = true;
	playerSpeed = speed;
}

void Player::OnCollisionStage(bool collisionFlag) {
	if (collisionFlag)
	{
		worldTransform_.translation_ = prePos_;
		worldTransform_.Update(worldTransform_);

		stopG_ = true;
	}
	else
	{
		stopG_ = false;
	}
	// 前フレーム座標
	prePos_ = worldTransform_.translation_;
}

void Player::DethCollision()
{
	isDead_ = true;
}

void Player::GetStop()
{
	playerSpeed.x = 0.0f;
}
