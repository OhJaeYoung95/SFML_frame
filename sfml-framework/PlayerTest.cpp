#include "stdafx.h"
#include "PlayerTest.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "Framework.h"

PlayerTest::PlayerTest(const std::string& textureId, const std::string& n)
	:SpriteGo(textureId, n)
{
}

void PlayerTest::Init()
{
	// 애니메이션 기존 방식
	{
		//std::string textureId = "graphics/sprite_sheet.png";
		//// idele
		//{
		//	AnimationClip clip;
		//	clip.id = "Idle";
		//	clip.fps = 10;
		//	clip.loopType = AnimationLoopTypes::Loop;

		//	sf::IntRect coord(0, 0, 120, 120);
		//	for (int i = 0; i < 8; ++i)
		//	{
		//		clip.frames.push_back({ textureId ,coord });
		//		coord.left += coord.width;
		//	}

		//	// x 120 y 120
		//	animation.AddClip(clip);
		//}
		//// move
		//{
		//	AnimationClip clip;
		//	clip.id = "Move";
		//	clip.fps = 10;
		//	clip.loopType = AnimationLoopTypes::Loop;

		//	sf::IntRect coord(0, 120, 120, 120);
		//	for (int i = 0; i < 8; ++i)
		//	{
		//		clip.frames.push_back({ textureId ,coord });
		//		coord.left += coord.width;
		//	}
		//	coord.left = 240;
		//	clip.frames.push_back({ textureId ,sf::IntRect(0, 240, 120, 120) });
		//	// x 120 y 120
		//	animation.AddClip(clip);
		//}
		//// move2
		//{
		//	AnimationClip clip;
		//	clip.id = "Jump";
		//	clip.fps = 15;
		//	clip.loopType = AnimationLoopTypes::Single;

		//	sf::IntRect coord(0, 360, 120, 120);
		//	for (int i = 0; i < 7; ++i)
		//	{
		//		clip.frames.push_back({ textureId ,coord });
		//		coord.left += coord.width;
		//	}
		//	clip.frames[6].action = []()
		//	{
		//		std::cout << "On Complete jump" << std::endl;
		//	};
		//	// x 120 y 120
		//	animation.AddClip(clip);
		//}
	}

	// 애니메이션 파일 입출력
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/Idle.csv");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/Move.csv");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/Jump.csv");

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Idle.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Move.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Jump.csv"));

	animation.SetTarget(&sprite);

	SetOrigin(Origins::BC);

}

void PlayerTest::Reset()
{
	animation.Play("Idle");
	SetOrigin(origin);
	SetPosition(0, 0);
	//SpriteGo::Reset();
}

void PlayerTest::Update(float dt)
{

	/*if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
	{
		animation.Play("Idle");
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num2))
	{
		animation.Play("Move");
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num3))
	{
		animation.Play("Jump");
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num5))
	{

		animation.Play("Move");
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num6))
	{

		animation.PlayQueue("Jump");
	}
	if (animation.GetQueue().empty())
	{
		animation.PlayQueue("Idle");
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Left))
	{
		animation.Play("Move");
		sprite.setScale(-1.f, 1.f);
	}*/
	bool LeftKey = INPUT_MGR.GetKey(sf::Keyboard::Left);
	bool RightKey = INPUT_MGR.GetKey(sf::Keyboard::Right);
	bool UpKeyDown = INPUT_MGR.GetKeyDown(sf::Keyboard::Up);
	bool LeftKeyUp = INPUT_MGR.GetKeyUp(sf::Keyboard::Left);
	bool RightKeyUp = INPUT_MGR.GetKeyUp(sf::Keyboard::Right);
	bool UpKeyUp = INPUT_MGR.GetKeyUp(sf::Keyboard::Up);

	if (LeftKey && !dontMoveLeftPlayer)
	{
		if (!movePlayer)
		{
			animation.Play("Move");
			sprite.setScale(-1.f, 1.f);
			direction = { -1.f,0.f };
			movePlayer = true;
		}
		dontMoveRigthPlayer = true;
	}
	if (RightKey && !dontMoveRigthPlayer)
	{
		if (!movePlayer)
		{
			animation.Play("Move");
			sprite.setScale(1.f, 1.f);
			direction = { 1.f,0.f };
			movePlayer = true;

		}
		dontMoveLeftPlayer = true;
	}
	if (UpKeyDown)
	{
		animation.Play("Jump");
		velocity = jumpFource;
	}
	if (LeftKeyUp || RightKeyUp)
	{
		animation.Play("Idle");
		direction = { 0.f,0.f };
		movePlayer = false;
		dontMoveRigthPlayer = false;
		dontMoveLeftPlayer = false;
	}
	if (UpKeyUp)
	{
		if (RightKey || LeftKey)
			animation.PlayQueue("Move");
		else
			animation.PlayQueue("Idle");
	}

	position += direction * 500.f * dt;
	velocity -= grivaty * dt;
	position.y -= velocity;
	
	position.y -= grivaty * dt;
	if (position.y >= 260.f)
		position.y = 260.f;
	sprite.setPosition(position);


	SpriteGo::Update(dt);
	animation.Update(dt);
}
/*a += dt;
	if (a >= ? )
	{
		abc = Utils::RandomRange(0, 5);일반패턴
		switch (abc)
		{
			s = dasd
				dsad
				sad

		}문자열
		animation, playQueq(s);
	}

	if (hp < 50 && !newPaten)
	{
		cuuern ->
			animation.Play("Idle");
	}*/
	// 느낌의 보스 슈팅 패턴 짜보기