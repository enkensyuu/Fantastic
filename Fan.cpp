#include "Fan.h"
#include <cassert>

void Fan::Initialize()
{
	/*assert(model);
	model_ = model;*/
	debugText_ = DebugText::GetInstance();
	input_ = Input::GetInstance();

	worldTransform_.Initialize();
}

void Fan::Update()
{
	if (input_->IsTriggerMouse(0))
	{
		if (input_->GetMousePosition() = )
		{

		}
		debugText_->SetPos(0, 0);
		debugText_->Printf("t");
	}
}

void Fan::Draw()
{
}
