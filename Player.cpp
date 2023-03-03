#include "Player.h"
#include "Procession.h"
#include <cassert>

void Player::Initialize()
{
	model_ = Model::Create();
	texture_ = TextureManager::Load("blue.png");

	worldTransform_.Initialize();
	viewProjection_.Initialize();
}

void Player::Update()
{
}

void Player::Draw()
{
	model_->Draw(worldTransform_, viewProjection_, texture_);
}
