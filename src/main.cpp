#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/cocos/actions/CCActionInterval.h>
#include <Geode/binding/ButtonSprite.hpp>
#include <Geode/binding/CreatorLayer.hpp>
#include <Geode/binding/FLAlertLayer.hpp>
#include <Geode/cocos/menu_nodes/CCMenu.h>
#include <Geode/cocos/layers_scenes_transitions_nodes/CCLayer.h>
#include <Geode/cocos/platform/CCImage.h>

using namespace geode::prelude;

class MyLayer : public CCLayer
{
public:

    static CCScene* scene()
    {
        auto scene = CCScene::create();
        scene->addChild(MyLayer::create());
        return scene;
    }

    static CCScene* creatorScene()
    {
        auto scene = CCScene::create();
        scene->addChild(CreatorLayer::create());
        return scene;
    }
    
    static MyLayer* create()
    {
        MyLayer* ret = new MyLayer();
        if(ret && ret->init())
        {
            ret->autorelease();
            return ret;
        }
        delete ret;
        return nullptr;
    }
    
    size_t m_clicked = 0;

    bool init()
    {
        if (!CCLayer::init())
            return false;

        auto menu = CCMenu::create();

		auto corner1 = CCSprite::createWithSpriteFrameName("rewardCorner_001.png");

		corner1->setPosition(CCPoint::CCPoint(CCSize(-287.f,-112.f)));
        corner1->setAnchorPoint(CCPoint::CCPoint(CCSize(0,1)));
        menu->addChild(corner1);

		auto corner2 = CCSprite::createWithSpriteFrameName("rewardCorner_001.png");

		corner2->setPosition(CCPoint::CCPoint(CCSize(237.f,-112.f)));
        corner2->setAnchorPoint(CCPoint::CCPoint(CCSize(0,1)));
		corner2->setFlipX(true);
        menu->addChild(corner2);

        this->addChild(menu);

		auto corner3 = CCSprite::createWithSpriteFrameName("rewardCorner_001.png");

		corner3->setPosition(CCPoint::CCPoint(CCSize(-287.f,162.f)));
        corner3->setAnchorPoint(CCPoint::CCPoint(CCSize(0,1)));
		corner3->setFlipY(true);
        menu->addChild(corner3);

		auto corner4 = CCSprite::createWithSpriteFrameName("rewardCorner_001.png");

		corner4->setPosition(CCPoint::CCPoint(CCSize(237.f,162.f)));
        corner4->setAnchorPoint(CCPoint::CCPoint(CCSize(0,1)));
		corner4->setFlipX(true);
		corner4->setFlipY(true);
        menu->addChild(corner4);

        this->addChild(menu);

		auto btn = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
            this,
            menu_selector(MyLayer::onClick)
        );
        btn->setPosition(-260.500, 135.f);
        btn->setAnchorPoint(CCPoint::CCPoint(CCSize(0,1)));
        menu->addChild(btn);

        return true;
    }

    void onClick(CCObject* sender)
    {
        auto scenePrev = CCTransitionFade::create(0.5f, MyLayer::creatorScene());
        CCDirector::sharedDirector()->replaceScene(scenePrev);
    }
};

class $modify(MyMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		auto myButton = CCMenuItemSpriteExtra::create(
			CCSprite::createWithSpriteFrameName("GJ_plusBtn_001.png"),
			this,
			menu_selector(MyMenuLayer::onMyButton)
		);

		auto menu = this->getChildByID("bottom-menu");
		menu->addChild(myButton);

		myButton->setID("my-button"_spr);

		menu->updateLayout();

		return true;
	}

	void onMyButton(CCObject*) {
		auto scene = CCTransitionFade::create(0.5f, MyLayer::scene());
        CCDirector::sharedDirector()->replaceScene(scene);
	}
};
