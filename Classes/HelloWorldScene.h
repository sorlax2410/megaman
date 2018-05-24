#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "screens/main.h"

struct CustomSprite: public cocos2d::Sprite
{

	enum class TouchEventType
	{
		BEGAN,
		MOVED,
		ENDED,
		CANCELED
	};

	typedef std::function<void(cocos2d::Ref*, CustomSprite::TouchEventType)> ccTouchCallback;

	static CustomSprite*createWithFile(const std::string &filename);
	static CustomSprite*createWithFrame(const std::string &filename);

	CustomSprite();
	virtual ~CustomSprite();

	bool hitTest(const cocos2d::Vec2 &point);

	void initInstance();

	void addTouchEventListener(const ccTouchCallback&callback);

	bool onTouchBegan(cocos2d::Touch*touch, cocos2d::Event*unusedEvent);
	void onTouchMoved(cocos2d::Touch*touch, cocos2d::Event*unusedEvent);
	void onTouchEnded(cocos2d::Touch*touch, cocos2d::Event*unusedEvent);
	void onTouchCancelled(cocos2d::Touch*touch, cocos2d::Event*unusedEvent);

	void moveEvent();
	void pushDownEvent();

	virtual void releaseUpEvent();
	virtual void cancelUpEvent();

private:
	bool hitted;
	cocos2d::EventListenerTouchOneByOne*touchListener;
	cocos2d::Vec2 touchBeganPosition;
	cocos2d::Vec2 touchMovePosition;
	cocos2d::Vec2 touchEndPosition;

	ccTouchCallback touchEventCallback;
};

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void changeScreen(cocos2d::Ref*sender);
};

#endif // __HELLOWORLD_SCENE_H__
