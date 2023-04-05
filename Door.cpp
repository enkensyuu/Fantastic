#include "Door.h"
#include "Procession.h"
#include <DirectXMath.h>

using namespace DirectX;


void Door::Initialize(float x, float y)
{
	input_ = Input::GetInstance();

	texture_ = TextureManager::Load("Red.png");
	model_ = Model::Create();

	worldTransform_.Initialize();

	startY = y;

	worldTransform_.scale_ = { 1,3,1 };
	worldTransform_.translation_ = { x,y,0 };

	// 行列更新
	worldTransform_.matWorld_ = Mat_Identity();
	worldTransform_.matWorld_ = MatWorld(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
	worldTransform_.TransferColorMatrix();

	viewProjection_.Initialize();
}

void Door::Update(bool flag)
{
	if (flag)
	{
		worldTransform_.translation_.y += 0.05f;
	}

	else
	{
		worldTransform_.translation_.y -= 0.05f;
	}

	if (worldTransform_.translation_.y > startY + 5)
	{
		worldTransform_.translation_.y = startY + 5;
	}

	else if (worldTransform_.translation_.y <= startY)
	{
		worldTransform_.translation_.y = startY;
	}

	// 行列更新
	worldTransform_.matWorld_ = Mat_Identity();
	worldTransform_.matWorld_ = MatWorld(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void Door::Draw()
{
	model_->Draw(worldTransform_, viewProjection_, texture_);
}
