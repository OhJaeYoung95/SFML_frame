#include "stdafx.h"
#include "Player.h"
#include "InputMgr.h"
#include "Framework.h"
#include "ResourceMgr.h"


void Player::Init()
{
	// 기존 애니메이션 방식
	{
		//std::string textureId = "graphics/RubySheet.png";

	//// RowIdle
	//{
	//	AnimationClip clip;
	//	clip.id = "RowIdle";
	//	clip.fps = 10;
	//	clip.loopType = AnimationLoopTypes::Loop;
	
	//	clip.frames.push_back({ textureId, sf::IntRect(0, 256*3, 256, 256) });
	//	clip.frames.push_back({ textureId, sf::IntRect(256, 256*5, 256, 256) });
	//	animation.AddClip(clip);
	//}	
	//// UpIdle
	//{
	//	AnimationClip clip;
	//	clip.id = "UpIdle";
	//	clip.fps = 10;
	//	clip.loopType = AnimationLoopTypes::Loop;
	
	//	clip.frames.push_back({ textureId, sf::IntRect(256 * 2, 256*3, 256, 256) });
	//	clip.frames.push_back({ textureId, sf::IntRect(256 * 3, 256*5, 256, 256) });
	//	animation.AddClip(clip);
	//}
	//// DownIdle
	//{
	//	AnimationClip clip;
	//	clip.id = "DownIdle";
	//	clip.fps = 10;
	//	clip.loopType = AnimationLoopTypes::Loop;
	
	//	clip.frames.push_back({ textureId, sf::IntRect(256, 256*3, 256, 256) });
	//	clip.frames.push_back({ textureId, sf::IntRect(256 * 2, 256*5, 256, 256) });
	//	animation.AddClip(clip);
	//}
	//// RowMove
	//{
	//	AnimationClip clip;
	//	clip.id = "RowMove";
	//	clip.fps = 10;
	//	clip.loopType = AnimationLoopTypes::Loop;
	
	//	sf::IntRect coord(0, 0, 256, 256);
	//	for (int i = 0; i < 4; ++i)
	//	{
	//		clip.frames.push_back({ textureId, coord });
	//		coord.left += coord.width;
	//	}
	//	animation.AddClip(clip);
	//}
	//// UpMove
	//{
	//	AnimationClip clip;
	//	clip.id = "UpMove";
	//	clip.fps = 10;
	//	clip.loopType = AnimationLoopTypes::Loop;
	
	//	sf::IntRect coord(0, 256, 256, 256);
	//	for (int i = 0; i < 4; ++i)
	//	{
	//		clip.frames.push_back({ textureId, coord });
	//		coord.left += coord.width;
	//	}
	//	animation.AddClip(clip);
	//}
	
	//// DownMove
	//{
	//	AnimationClip clip;
	//	clip.id = "DownMove";
	//	clip.fps = 10;
	//	clip.loopType = AnimationLoopTypes::Loop;
	
	//	sf::IntRect coord(0, 256*2, 256, 256);
	//	for (int i = 0; i < 4; ++i)
	//	{
	//		clip.frames.push_back({ textureId, coord });
	//		coord.left += coord.width;
	//	}
	
	//	//clip.frames[6].action = []() {
	//	//	std::cout << "On Complete Jump Clip" << std::endl;
	//	//};

	}

	// 애니메이션 파일 입출력
	//RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/RowIdle.csv");
	//RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/UpIdle.csv");
	//RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/DownIdle.csv");
	//RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/RowMove.csv");
	//RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/UpMove.csv");
	//RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/DownMove.csv");

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/RowIdle.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/UpIdle.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/DownIdle.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/RowMove.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/UpMove.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/DownMove.csv"));

	animation.SetTarget(&sprite);
	SetOrigin(Origins::BC);
}

void Player::Reset()
{
	animation.Play("DownIdle");
	SetOrigin(origin);
	SetPosition({ 0, 0 });
	SetFlipX(false);
}

void Player::Update(float dt)
{
	sf::Vector2f v = { INPUT_MGR.GetAxis(Axis::Horizontal), INPUT_MGR.GetAxis(Axis::Vertical) };

	// 플립
	if (v.x != 0.f)
	{
		bool flip = v.x < 0.f;
		if (GetFlipX() != flip)
		{
			SetFlipX(flip);
		}
	}

	// 점프
	//if (isGround && INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	//{
	//	velocity.y += JumpForce;
	//	//animation.Play("Jump");
	//	isGround = false;
	//}

	// 이동
	velocity.x = v.x * speed;
	velocity.y = v.y * speed;
	position += velocity * dt;

	//// 바닥 충돌 처리
	//if (position.y > 0.f)
	//{
	//	isGround = true;
	//	position.y = 0.f;
	//	velocity.y = 0.f;
	//}

	SetPosition(position);

	float absX = std::abs(v.x);
	float absY = std::abs(v.y);
	// 에니메이션
	if (animation.GetCurrentClipId() == "RowIdle")
	{
		if (v.x != 0.f && absX > absY)
		{
			animation.Play("RowMove");
		}
		if (v.y > 0.f && absX < absY)
		{
			animation.Play("DownMove");
		}
		 if (v.y < 0.f && absX < absY)
		{
			animation.Play("UpMove");
		}
	}
	else if (animation.GetCurrentClipId() == "RowMove")
	{
		if (v.x == 0.f)
		{
			animation.Play("RowIdle");
		}
		 if (v.y > 0.f && absX < absY)
		{
			animation.Play("DownMove");
		}
		 if (v.y < 0.f && absX < absY)
		{
			animation.Play("UpMove");
		}
	}
	else if (animation.GetCurrentClipId() == "UpMove")
	{
		if ( v.y == 0)
		{
			animation.Play("UpIdle");
		}
		 if (v.x != 0.f && absX > absY)
		{
			animation.Play("RowMove");
		}
		 if (v.y > 0.f && absX < absY)
		{
			animation.Play("DownMove");
		}
	}
	else if (animation.GetCurrentClipId() == "UpIdle")
	{

		if (v.x != 0.f && absX > absY)
		{
			animation.Play("RowMove");
		}
		 if (v.y < 0.f && absX < absY)
		{
			animation.Play("UpMove");
		}
		 if (v.y > 0.f && absX < absY)
		{
			animation.Play("DownMove");
		}
	}	
	else if (animation.GetCurrentClipId() == "DownMove")
	{
		if (v.y == 0)
		{
			animation.Play("DownIdle");
		}
		 if (v.x != 0.f && absX > absY)
		{
			animation.Play("RowMove");
		}

		 if (v.y < 0.f && absX < absY)
		{
			animation.Play("UpMove");
		}
	}
	else if (animation.GetCurrentClipId() == "DownIdle")
	{

		if (v.x != 0.f && absX > absY)
		{
			animation.Play("RowMove");
		}
		 if (v.y < 0.f && absX < absY)
		{
			animation.Play("UpMove");
		}
		 if (v.y > 0.f && absX < absY)
		{
			animation.Play("DownMove");
		}
	}

	// 
	// 
	//else if (animation.GetCurrentClipId() == "Jump")
	//{
	//	if (isGround)
	//	{
	//		animation.Play((h == 0.f) ? "Idle" : "Move");
	//	}
	//}
	animation.Update(dt);
}

bool Player::GetFlipX() const
{
	return filpX;
}

void Player::SetFlipX(bool filp)
{
	filpX = filp;

	sf::Vector2f scale = sprite.getScale();
	scale.x = !filpX ? -abs(scale.x) : abs(scale.x);
	sprite.setScale(scale);
}