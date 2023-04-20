#include "Player.h"
#include <cassert>
#include "Procession.h"

void Player::Initialize()
{
	input_ = Input::GetInstance();

	texture_ = TextureManager::Load("yellow.png");
	model_ = Model::Create();

	worldTransform_.Initialize();

	worldTransform_.translation_ = { -25.0f,-10.0f,0 };
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
	worldTransform_.translation_.y -= 0.1f;

	if (isMove_)
	{
		worldTransform_.translation_ +=playerSpeed;
		stoptimer--;
	}
	if (stoptimer <= 0)
	{
		isMove_ = false;
		isMove2_ = true;
		stoptimer = 6 * 5;
	}

	if (isMove2_)
	{
		worldTransform_.translation_ += returnSpeed;
		stoptimer2--;
	}

	if (stoptimer2 <= 0)
	{
		isMove2_ = false;
		stoptimer2 = 8 * 5;
	}

	if (input_->TriggerKey(DIK_R))
	{
		Initialize();
	}

	// 行列更新
	worldTransform_.matWorld_ = Mat_Identity();
	worldTransform_.matWorld_ = MatWorld(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();
	worldTransform_.TransferColorMatrix();
}

void Player::Draw()
{
	model_->Draw(worldTransform_, viewProjection_, texture_);
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

void Player::Collision(Vector3 speed)
{
	isMove_ = true;
	playerSpeed = speed;
	returnSpeed = speed;
	returnSpeed /= 2;
}

void Player::DethCollision()
{
	isDead_ = true;
}

void Player::GetStop()
{
	isMove_ = false;
	isMove2_ = false;
}
