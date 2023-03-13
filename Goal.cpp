#include "Goal.h"

void Goal::Initialize()
{
	model_ = Model::Create();
	worldTransform_.scale_ = { 10.0f,Y_RAD ,10.0f };
	worldTransform_.Initialize();
	worldTransform_.Update();
	SetCollisionAttribute(CollisionAttribute::Goal);
	SetCollisionMask(CollisionMask::Wall);
}

void Goal::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}

void Goal::SetGoal(int stage)
{
	isGoal = false;

	switch (stage)
	{
	case 1: worldTransform_.translation_ = { 0,Y_POS,160.0f };			break;
	case 2: worldTransform_.translation_ = { 100.0f,Y_POS,-20.0f };		break;
	case 3: worldTransform_.translation_ = { 200.0f,Y_POS,200.0f };		break;
	case 4: worldTransform_.translation_ = { 0.0f,Y_POS,360.0f };		break;
	case 5: worldTransform_.translation_ = { 240.0f,Y_POS,-240.0f };	break;
	case 6: worldTransform_.translation_ = { -100.0f,Y_POS,120.0f };	break;
	case 7: worldTransform_.translation_ = { 400.0f,Y_POS,-300.0f };	break;
	case 8: worldTransform_.translation_ = { 280.0f,Y_POS,-280.0f };	break;
	}
	worldTransform_.Update();
}