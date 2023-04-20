#include "SilverKey.h"
#include "Procession.h"

void SilverKey::Initialize(float x, float y)
{
	model_ = Model::CreateFromOBJ("SilverKey");

	isGet_ = false;
	stopTimer = 6 * 5;

	worldTransform_.Initialize();

	worldTransform_.scale_ = { 0.75f,0.75f ,0.75f };

	worldTransform_.rotation_ = { 0,XMConvertToRadians(90),0 };

	worldTransform_.translation_.x = x;
	worldTransform_.translation_.y = y;

	worldTransform_.matWorld_ = Mat_Identity();
	worldTransform_.matWorld_ = MatWorld(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferColorMatrix();
	worldTransform_.TransferMatrix();
	viewProjection_.Initialize();
}

void SilverKey::Update()
{

	if (isMove_)
	{
		worldTransform_.translation_ += Speed;
		stopTimer--;
	}

	if (stopTimer <= 0)
	{
		isMove_ = false;
		stopTimer = 6 * 5;
	}

	worldTransform_.translation_ -= {0, 0.1f, 0};

	worldTransform_.matWorld_ = Mat_Identity();
	worldTransform_.matWorld_ = MatWorld(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void SilverKey::Draw()
{
	if (!isGet_)
	{
		model_->Draw(worldTransform_, viewProjection_);
	}
}

Vector3 SilverKey::GetWorldPosition()
{
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

void SilverKey::MoveCollision(Vector3 speed)
{
	isMove_ = true;
	Speed = speed;
}


void SilverKey::GetCollision()
{
	isGet_ = true;
}