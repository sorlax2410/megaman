#include "main.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene*MainScene::createScene()
{
	return MainScene::create();
}

bool MainScene::init()
{
	if(!Scene::init()) return false;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto closeItem = MenuItemImage::create(
						"CloseNormal.png",
						"CloseSelected.png",
						CC_CALLBACK_1(MainScene::menuCloseCallback, this)
    );
	closeItem->setPosition(
				Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
					origin.y + visibleSize.height - closeItem->getContentSize().height / 2)
    );
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);

	//Making label and position it on the main menu screen
	auto startGameLabel = Label::createWithTTF("Start Game", "fonts/Marker Felt.ttf", 20);
	auto quitGameLabel = Label::createWithTTF("Quit Game", "fonts/Marker Felt.ttf", 20);
	auto megamanLabel = Label::createWithTTF("Megaman", "fonts/Marker Felt.ttf", 20);
	auto nameLabel = Label::createWithTTF("Time and Space", "fonts/Marker Felt.ttf", 20);

	startGameLabel->setPosition(Vec2(
			visibleSize.width/2 + origin.x,
			visibleSize.height + origin.y/2
	));
	quitGameLabel->setPosition(Vec2(
			visibleSize.width/2 + origin.x,
			visibleSize.height + origin.y
	));
	megamanLabel->setPosition(Vec2(
			visibleSize.width/2 + origin.x,
			origin.y + visibleSize.height/2
	));
	nameLabel->setPosition(Vec2(
			visibleSize.width/2 + origin.x/2 + megamanLabel->getContentSize().width/2,
			visibleSize.height/2 + origin.y - megamanLabel->getContentSize().height
	));

	//adding label as a child to this layer
	this->addChild(megamanLabel, 2);
	this->addChild(nameLabel, 2);
	this->addChild(startGameLabel, 2);
	this->addChild(quitGameLabel, 2);

	//adding sprites as a child
//	auto sprite = Sprite::create("sprites/megaman zero/title screen.png");

//	sprite->setPosition(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);
//	this->addChild(sprite);

	return true;
}

void MainScene::menuCloseCallback(cocos2d::Ref*sender)
{
	//close the game and quit the application
	Director::getInstance()->end();
	#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
	#endif
}
