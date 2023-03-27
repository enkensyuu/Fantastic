#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene()
{
	delete Title_;
	delete Explanation_;
	delete StageChoice_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	//テクスチャを入れ込む
	textureHandle_[0] = TextureManager::Load("exchange.png"); //操作説明
	textureHandle_[1] = TextureManager::Load("Title.png"); //タイトル
	textureHandle_[2] = TextureManager::Load("space.png"); //Space文字
	textureHandle_[3] = TextureManager::Load("Stage.png"); //ステージ選択
	textureHandle_[4] = TextureManager::Load("waku.png"); //ステージ選択(枠)


	//スプライトを生成
	Explanation_ = Sprite::Create(textureHandle_[0], { 0,0 });
	Title_ = Sprite::Create(textureHandle_[1], { 0,0 });
	Space_ = Sprite::Create(textureHandle_[2], { 550,800 });
	StageChoice_= Sprite::Create(textureHandle_[3], { 0,0 });
	Waku_ = Sprite::Create(textureHandle_[4], {100,200});
	Waku2_ = Sprite::Create(textureHandle_[4], { 705,200 });
	Waku3_ = Sprite::Create(textureHandle_[4], { 1300,200 });
	Waku4_ = Sprite::Create(textureHandle_[4], { 100,600 });
	Waku5_ = Sprite::Create(textureHandle_[4], { 710,600 });

	stage1_ = new Stage1;
	stage1_->Initialize();

	stage2_ = new Stage2;
	stage2_->Initialize();

	stage3_ = new Stage3;
	stage3_->Initialize();

	stage4_ = new Stage4;
	stage4_->Initialize();

	stage5_ = new Stage5;
	stage5_->Initialize();

	scene_ = TITLE;
	RingFlag = 0;
}

void GameScene::Update() {
	switch (scene_)
	{
	case TITLE:
		Initialize();
		GameTimer_ += 1;
		if (input_->TriggerKey(DIK_SPACE))
		{
			scene_ = EXPLANATION;
		}
		break;
	case EXPLANATION:
		if (input_->TriggerKey(DIK_SPACE))
		{
			scene_ = STAGECHOICE;
		}
		break;
	case STAGECHOICE:

		//番号を押すと選択される
		if (input_->TriggerKey(DIK_1))
		{
			RingFlag = 1;
			if (input_->TriggerKey(DIK_RETURN) && RingFlag == 1)
			{
				scene_ = THREE;
			}
		}
		if (input_->TriggerKey(DIK_2))
		{
			RingFlag = 2;
			if (input_->TriggerKey(DIK_RETURN) && RingFlag == 2)
			{
				scene_ = FOUR;
			}
		}
		if (input_->TriggerKey(DIK_3))
		{
			RingFlag = 3;
			if (input_->TriggerKey(DIK_RETURN) && RingFlag == 3)
			{
				scene_ = FIVE;
			}
		}
		if (input_->TriggerKey(DIK_4))
		{
			RingFlag = 4;
			if (input_->TriggerKey(DIK_RETURN) && RingFlag == 4)
			{
				scene_ = SIX;
			}
		}
		if (input_->TriggerKey(DIK_5))
		{
			RingFlag = 5;
			if (input_->TriggerKey(DIK_RETURN) && RingFlag == 5)
			{
				scene_ = SEVEN;
			}
		}


		//Bボタンで選択キャンセル
		if (input_->TriggerKey(DIK_B) && RingFlag == 1)
		{
			RingFlag = 0;
		}

		if (input_->TriggerKey(DIK_B) && RingFlag == 2)
		{
			RingFlag = 0;
		}

		if (input_->TriggerKey(DIK_B) && RingFlag == 3)
		{
			RingFlag = 0;
		}

		if (input_->TriggerKey(DIK_B) && RingFlag == 4)
		{
			RingFlag = 0;
		}

		if (input_->TriggerKey(DIK_B) && RingFlag == 5)
		{
			RingFlag = 0;
		}
	case THREE:

		//ENTERキーを押したらステージ移動
		if (input_->TriggerKey(DIK_RETURN) && RingFlag == 1)
		{
			scene_ = THREE;
		}

		if (input_->TriggerKey(DIK_RETURN)&&RingFlag==2)
		{
			scene_ = FOUR;
		}

		if (input_->TriggerKey(DIK_RETURN) && RingFlag == 3)
		{
			scene_ = FIVE;
		}

		if (input_->TriggerKey(DIK_RETURN) && RingFlag == 4)
		{
			scene_ = SIX;
		}

		if (input_->TriggerKey(DIK_SPACE) && RingFlag == 5)
		{
			scene_ = SEVEN;
		}

		if (scene_ == THREE)
		{
			stage1_->Update();
		}
		break;

	case FOUR:
		if (scene_ == FOUR)
		{
            stage2_->Update();
		}
		break;

	case FIVE:
		if (scene_ == FIVE)
		{
			stage3_->Update();
		}
		break;

	case SIX:
		if (scene_ == SIX)
		{
			stage4_->Update();
		}
		break;

	case SEVEN:
		if (scene_ == SEVEN)
		{
			stage5_->Update();
		}
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	/// 
	switch (scene_)
	{
	case TITLE:
		Title_->Draw();
		if (GameTimer_ % 30 >= 20)
		{
			Space_->Draw();
		}
		break;
	case EXPLANATION:
		Explanation_->Draw();
		break;
	case STAGECHOICE:
		StageChoice_->Draw();
		if (RingFlag == 1)
		{
         Waku_->Draw();
		}
		if (RingFlag == 2)
		{
			Waku2_->Draw();
		}
		if (RingFlag == 3)
		{
			Waku3_->Draw();
		}
		if (RingFlag == 4)
		{
			Waku4_->Draw();
		}
		if (RingFlag == 5)
		{
			Waku5_->Draw();
		}
		break;
	}
	/*DebugText::GetInstance()->SetPos(200, 180);
	DebugText::GetInstance()->Printf("scene:%d", scene_);*/

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	switch (scene_)
	{
	case TITLE:
		break;
	case EXPLANATION:
		break;
	case STAGECHOICE:
		break;
	case THREE:
		stage1_->Draw();
		break;
	case FOUR:
		stage2_->Draw();
		break;
	case FIVE:
		stage3_->Draw();
		break;
	case SIX:
		stage4_->Draw();
		break;
	case SEVEN:
		stage5_->Draw();
		break;
	}
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
