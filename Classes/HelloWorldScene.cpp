#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "screens/main.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png");
	CustomSprite* sprite = CustomSprite::createWithFile("HelloWorld.png");
	

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}


void HelloWorld::menuCloseCallback(cocos2d::Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}

void HelloWorld::changeScreen(Ref*sender)
{
	auto director = Director::getInstance();
	auto scene = MainScene::createScene();
	director->runWithScene(scene);
}


CustomSprite::CustomSprite() :
hitted(false),
touchListener(nullptr),
touchBeganPosition(Vec2::ZERO),
touchMovePosition(Vec2::ZERO),
touchEndPosition(Vec2::ZERO)
{}

CustomSprite::~CustomSprite()
{
	_eventDispatcher->removeEventListener(touchListener);
	CC_SAFE_RELEASE_NULL(touchListener);
}

CustomSprite*CustomSprite::createWithFile(const std::string &filename)
{
	CustomSprite*sprite = new CustomSprite();

	if(sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		sprite->initInstance();
		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void CustomSprite::initInstance()
{
	touchListener = EventListenerTouchOneByOne::create();
	CC_SAFE_RETAIN(touchListener);
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(CustomSprite::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(CustomSprite::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(CustomSprite::onTouchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(CustomSprite::onTouchCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool CustomSprite::onTouchBegan(Touch*touch, Event*unusedEvent)
{
	hitted = false;
	touchBeganPosition = touch->getLocation();
	if(hitTest(touchBeganPosition))
		hitted = true;
	if(!hitted)
		return false;
	pushDownEvent();
	return true;
}

bool CustomSprite::hitTest(const Vec2 &point)
{
	Vec2 nodeSpace = convertToNodeSpace(point);
	Rect bb;
	bb.size = _contentSize;
	if(bb.containsPoint(nodeSpace))
		return true;
	return false;
}

void CustomSprite::onTouchMoved(Touch*touch, Event*unusedEvent)
{
	touchMovePosition = touch->getLocation();
	moveEvent();
}

void CustomSprite::onTouchEnded(Touch*touch, Event*unusedEvent)
{
	touchEndPosition = touch->getLocation();
	if(hitTest(touchEndPosition))
		releaseUpEvent();
	else
		cancelUpEvent();
}

void CustomSprite::onTouchCancelled(Touch*touch, Event*unusedEvent)
{
	cancelUpEvent();
}

void CustomSprite::pushDownEvent()
{
	this->retain();
	if(touchEventCallback)
		touchEventCallback(this, TouchEventType::BEGAN);
	this->release();
}

void CustomSprite::moveEvent()
{
	this->retain();
	if(touchEventCallback)
		touchEventCallback(this, TouchEventType::MOVED);
	this->release();
}

void CustomSprite::releaseUpEvent()
{
	this->retain();
	if(touchEventCallback)
		touchEventCallback(this, TouchEventType::ENDED);
	this->release();
}

void CustomSprite::cancelUpEvent()
{
	this->retain();
	if(touchEventCallback)
		touchEventCallback(this, TouchEventType::CANCELED);
	this->release();
}

