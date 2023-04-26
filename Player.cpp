#include "Player.h"
#include <cassert>
#include "Procession.h"

bool Player::isDeads_ = false;

	texture_ = TextureManager::Load("yellow.png");
	model_ = Model::CreateFromOBJ("Player");
void Player::Initialize(Model* model, Vector3 pos) {
	// NULLポインタチェック
	assert(model);

	worldTransform_.Initialize();

	worldTransform_.translation_ = { -25.0f,-10.0f,0 };
	isMove_ = false;
	isMove2_ = false;

	// 行列更新
	worldTransform_.matWorld_ = Mat_Identity();
	worldTransform_.matWorld_ = MatWorld(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();

	viewProjection_.Initialize();
	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
	worldTransform_.scale_ = { 2.0f,2.0f,2.0f };
}

void Player::Update() {
	Vector3 move = MyMathUtility::MySetVector3Zero();
	float moveSpeed = 1.0f;
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
}

Vector3 Player::GetWorldPosition()
{
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
void Player::Collision(Vector3 speed)
{
	isMove_ = true;
	playerSpeed = speed;
	returnSpeed = speed;
	returnSpeed /= 2;
}

void Player::OnCollisionStage(bool collisionFlag) {
	if (collisionFlag) {
		worldTransform_.translation_ = prePos_;
		worldTransform_.Update(worldTransform_);
void Player::DethCollision()
{
	isDead_ = true;
}
	// 前フレーム座標
	prePos_ = worldTransform_.translation_;

void Player::GetStop()
{
	isMove_ = false;
	isMove2_ = false;
}
