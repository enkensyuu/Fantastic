#include "MagmaBlock.h"
#include "Procession.h"

void MagmaBlock::Initialize(float x, float y)
{
	model_ = Model::Create();
	texture_ = TextureManager::Load("Red.png");

	worldTransform_.Initialize();

	worldTransform_.translation_ = { x,y,0 };

	// 行列更新
	worldTransform_.matWorld_ = Mat_Identity();
	worldTransform_.matWorld_ = MatWorld(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferColorMatrix();
	worldTransform_.TransferMatrix();

	viewProjection_.Initialize();
}

void MagmaBlock::Update()
{
	// 行列更新
	worldTransform_.matWorld_ = Mat_Identity();
	worldTransform_.matWorld_ = MatWorld(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();
}

void MagmaBlock::Draw()
{
	model_->Draw(worldTransform_, viewProjection_, texture_);
}

Vector3 MagmaBlock::GetPosition()
{
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

void MagmaBlock::Collision()
{
	
}