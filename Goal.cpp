#include "Goal.h"
#include "Procession.h"

void Goal::Initialize(float x, float y)
{
	model_ = Model::CreateFromOBJ("gate");
	texture_ = TextureManager::Load("red.png");

	worldTransform_.Initialize();

	worldTransform_.scale_ = { 0.45f,0.45f,0.45f };

	worldTransform_.rotation_ = { 0,XMConvertToRadians(90),0 };

	worldTransform_.translation_ = { x,y,-20.0f };


	// 行列更新
	worldTransform_.matWorld_ = Mat_Identity();
	worldTransform_.matWorld_ = MatWorld(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();
	worldTransform_.TransferColorMatrix();

	viewProjection_.Initialize();
}

void Goal::Draw(ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}

Vector3 Goal::GetPosition()
{
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}