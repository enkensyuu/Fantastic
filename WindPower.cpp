#include "WindPower.h"
#include "Procession.h"

void WindPower::Initialize(float x, float y)
{
	texture_ = TextureManager::Load("white.png");
	texture2_ = TextureManager::Load("Red.png");
	model_ = Model::CreateFromOBJ("WindPowerUp");
	model2_ = Model::CreateFromOBJ("WindPowerDown");
	isMove_ = false;
	stopTimer_ = 4 * 5;

	for (size_t i = 0; i < _countof(worldTransform_); i++)
	{

		worldTransform_[i].Initialize();

		worldTransform_[0].translation_ = { x,y+2.5f,0 };
		worldTransform_[1].translation_ = { x,y,3.5f };

		worldTransform_[i].matWorld_ = Mat_Identity();
		worldTransform_[i].matWorld_ = MatWorld(worldTransform_[i].scale_, worldTransform_[i].rotation_, worldTransform_[i].translation_);
		worldTransform_[i].TransferColorMatrix();
		worldTransform_[i].TransferMatrix();

	}

	viewProjection_.Initialize();
}

void WindPower::Update()
{
	Vector3 RotationSpeed = { 0,0,0.1f};

	if (isMove_)
	{
		worldTransform_[0].rotation_ -= RotationSpeed;
		stopTimer_--;
	}

	if (stopTimer_<=0)
	{
		isMove_ = false;
	}

	for (size_t i = 0; i < _countof(worldTransform_); i++)
	{

		worldTransform_[i].matWorld_ = Mat_Identity();
		worldTransform_[i].matWorld_ = MatWorld(worldTransform_[i].scale_, worldTransform_[i].rotation_, worldTransform_[i].translation_);
		worldTransform_[i].TransferMatrix();

	}
}

void WindPower::Draw(ViewProjection& viewProjection)
{
		model_->Draw(worldTransform_[0], viewProjection);
		model2_->Draw(worldTransform_[1], viewProjection);
}

void WindPower::Collision()
{
	isMove_ = true;
	stopTimer_ = 12 * 5;
}

Vector3 WindPower::GetPosition()
{
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_[0].translation_.x;
	worldPos.y = worldTransform_[0].translation_.y;
	worldPos.z = worldTransform_[0].translation_.z;

	return worldPos;
}
