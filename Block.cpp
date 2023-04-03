#include "Block.h"
#include "Procession.h"

void Block::Initialize()
{
	model_ = Model::Create();
	texture_ = TextureManager::Load("orange.png");

	for (size_t i = 0; i < _countof(worldTransform_); i++)
	{
		worldTransform_[i].Initialize();

		worldTransform_[0].translation_ = { -30,-17,0 };
		worldTransform_[1].translation_ = { -28,-17,0 };
		worldTransform_[2].translation_ = { -26,-17,0 };
		worldTransform_[3].translation_ = { -24,-17,0 };
		worldTransform_[4].translation_ = { -22,-17,0 };
		worldTransform_[5].translation_ = { -20,-17,0 };
		worldTransform_[6].translation_ = { -18,-17,0 };
		worldTransform_[7].translation_ = { -16,-17,0 };
		worldTransform_[8].translation_ = { -14,-17,0 };
		worldTransform_[9].translation_ = { -12,-17,0 };
		worldTransform_[10].translation_ = { -10,-17,0 };
		worldTransform_[11].translation_ = { -2,-17,0 };
		worldTransform_[12].translation_ = { 0,-17,0 };
		worldTransform_[13].translation_ = { 2,-17,0 };
		worldTransform_[14].translation_ = { 4,-17,0 };
		worldTransform_[15].translation_ = { 6,-17,0 };
		worldTransform_[16].translation_ = { 8,-17,0 };
		worldTransform_[17].translation_ = { 10,-17,0 };
		worldTransform_[18].translation_ = { 12,-17,0 };
		worldTransform_[19].translation_ = { 14,-17,0 };
		worldTransform_[20].translation_ = { 16,-17,0 };
		worldTransform_[21].translation_ = { 18,-17,0 };
		worldTransform_[22].translation_ = { 20,-17,0 };
		worldTransform_[23].translation_ = { 22,-17,0 };
		worldTransform_[24].translation_ = { 24,-17,0 };
		worldTransform_[25].translation_ = { 26,-17,0 };
		worldTransform_[26].translation_ = { 28,-17,0 };
		worldTransform_[27].translation_ = { 30,-17,0 };
		

		// 行列更新
		worldTransform_[i].matWorld_ = Mat_Identity();
		worldTransform_[i].matWorld_ = MatWorld(worldTransform_[i].scale_, worldTransform_[i].rotation_, worldTransform_[i].translation_);

		worldTransform_[i].TransferMatrix();
		worldTransform_[i].TransferColorMatrix();
	}

	viewProjection_.Initialize();
}

void Block::Draw()
{
	for (size_t i = 0; i < _countof(worldTransform_); i++)
	{
		model_->Draw(worldTransform_[i], viewProjection_, texture_);
	}
}

Vector3 Block::GetPosition()
{
	for (size_t i = 0; i < _countof(worldTransform_); i++)
	{
		// ワールド座標を入れる変数
		Vector3 worldPos;
		// ワールド行列の平行移動成分を取得(ワールド座標)
		worldPos.x = worldTransform_[i].translation_.x;
		worldPos.y = worldTransform_[i].translation_.y;
		worldPos.z = worldTransform_[i].translation_.z;

		return worldPos;
	}
}