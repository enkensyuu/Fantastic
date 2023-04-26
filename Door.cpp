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

	worldTransform_.scale_ = { 2,6,2 };
	worldTransform_.translation_ = { x,y,-20 };

	// 行列更新
	worldTransform_.matWorld_ = Mat_Identity();
	worldTransform_.matWorld_ = MatWorld(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
	worldTransform_.TransferColorMatrix();

	viewProjection_.Initialize();
}

void Door::Update(bool flag, bool flag2)
{
	if (flag || flag2)
	{
		worldTransform_.translation_.y += 0.05f;
	}

	else if (!flag || !flag2)
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

void Door::Draw(ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, texture_);
}

Vector3 Door::GetPosition()
{
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}
