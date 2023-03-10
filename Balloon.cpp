#include "Balloon.h"
#include <cassert>
#include "Procession.h"
#include <DirectXMath.h>

void Balloon::Initialize()
{
	model_ = Model::CreateFromOBJ("Balloon");

	worldTransform_.Initialize();

	worldTransform_.translation_ = { 5,10,0 };

	isMove_ = false;
	isUpDown_ = true;
	isUp_ = true;
	isDown_ = false;
	changeTime = 12 * 5;

	// 行列更新
	worldTransform_.matWorld_ = Mat_Identity();
	worldTransform_.matWorld_ = MatWorld(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();
	worldTransform_.TransferColorMatrix();

	viewProjection_.Initialize();
}

void Balloon::Update(Vector3 speed)
{
	balloonSpeed = speed;
	balloonSpeed /= 2;
	UpDownSpeed = { 0,0.01f,0 };

	if (isMove_)
	{
		worldTransform_.translation_ += balloonSpeed;
	}

	if (isUpDown_)
	{
		changeTime--;
		if (changeTime <= 0&&isUp_)
		{
			isUp_ = false;
			isDown_ = true;
			changeTime = 12 * 5;
		}

		else if (changeTime <= 0 && isDown_)
		{
			isUp_ = true;
			isDown_ = false;
			changeTime = 12 * 5;
		}

		if (isUp_)
		{
			worldTransform_.translation_ += UpDownSpeed;
		}

		if (isDown_)
		{
			worldTransform_.translation_ -= UpDownSpeed;
		}
	}

	// 行列更新
	worldTransform_.matWorld_ = Mat_Identity();
	worldTransform_.matWorld_ = MatWorld(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();
	worldTransform_.TransferColorMatrix();
}

void Balloon::Draw()
{
	model_->Draw(worldTransform_, viewProjection_);
}

void Balloon::Collision()
{
	isMove_ = true;
	isUpDown_ = false;
}

Vector3 Balloon::GetWorldPosition()
{
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}
