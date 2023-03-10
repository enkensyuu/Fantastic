#include "Balloon.h"
#include <cassert>
#include "Procession.h"

void Balloon::Initialize()
{
	model_ = Model::CreateFromOBJ("balloon");

	worldTransform_.Initialize();

	worldTransform_.translation_ = { 5,0,0 };

	// s—ñXV
	worldTransform_.matWorld_ = Mat_Identity();
	worldTransform_.matWorld_ = MatWorld(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();

	viewProjection_.Initialize();
}

void Balloon::Update(Vector3 speed)
{
	balloonSpeed = speed;

	if (isMove_)
	{
		worldTransform_.translation_ += balloonSpeed;
	}
}

void Balloon::Draw()
{
	model_->Draw(worldTransform_, viewProjection_);
}

void Balloon::Collision()
{
	isMove_ = true;
}
