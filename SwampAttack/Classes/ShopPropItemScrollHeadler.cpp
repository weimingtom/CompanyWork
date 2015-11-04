//
//  ShopPropItemScrollHeadler.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/27.
//
//

#include "ShopPropItemScrollHeadler.h"
//#include "GunManager.h"
#include "PropManager.h"
//#include "DefenseBuildingManager.h"
#include "GameUser.h"
#include "GameSprite.h"
#include "GameShowDiscLayer.h"
#include "GameShowLevelupLayer.h"
#include "BaseUtil.h"

ShopPropItemScrollHeadler::ShopPropItemScrollHeadler(int index)
{
    setIndex(index);
    _G_U->attach(this);
    initDaojuView();
    
}
ShopPropItemScrollHeadler::~ShopPropItemScrollHeadler()
{
    _G_U->detach(this);
    //    log("shop item scroll headler remove");
}
void ShopPropItemScrollHeadler::setGameShopScene(GameShopScene *shopScene)
{
    m_shopScene = shopScene;
}
void ShopPropItemScrollHeadler::initDaojuView()
{
    removeAllChildrenWithCleanup(true);
    
    Prop * prop = PropManager::getInstance()->getPropByIndex(m_index);
    setSubject(prop);
    if (prop->isUnlock())
    {
        initUnlockView();
    }else
    {
        initLockView();
    }
    
    updateDaojuView();
}
void ShopPropItemScrollHeadler::initUnlockView()
{
    Prop * prop = PropManager::getInstance()->getPropByIndex(m_index);
    
    Sprite * itemBg = Sprite::create(ImagePath("shopItemBg1.png"));
    addChild(itemBg);
    
    Size itemBgSize = itemBg->getContentSize();
    
    m_iconBg = new GameSprite(ImagePath("shopItemIconBg.png"));
    m_iconBg->autorelease();
    m_iconBg->m_touchMeCall = CC_CALLBACK_2(ShopPropItemScrollHeadler::showDiscView, this);
    
    //        Sprite * iconBg = Sprite::create(ImagePath("shopItemIconBg.png"));
    m_iconBg->setPosition(- itemBgSize.width * 0.35,
                        0);
    addChild(m_iconBg);
    
    Size iconBgSize = m_iconBg->getContentSize();
    
    Sprite * biaoSign = Sprite::create(ImagePath("shop_icon_sign.png"));
    biaoSign->setPosition(iconBgSize.width * 0.25,
                          iconBgSize.height * 0.71);
    m_iconBg->addChild(biaoSign);
    
    string propModelId = prop->getModelId();
    string propIconStr = StringUtils::format("%s_icon.png",propModelId.c_str());
    string propNameStr = StringUtils::format("%s_name.png",propModelId.c_str());
    Sprite * icon = Sprite::create(ImagePath(propIconStr));
    icon->setPosition(iconBgSize.width * 0.5,
                      iconBgSize.height * 0.5);
    icon->setScale(0.85);
    m_iconBg->addChild(icon,1);
    
    Sprite * iconName = Sprite::create(ImagePath(propNameStr));
    iconName->setPosition(-itemBgSize.width * 0.25
                          + iconName->getContentSize().width * 1,
                          itemBgSize.height * 0.2);
    addChild(iconName);
    
    m_upGradeButton = new GameSprite(ImagePath("shopItemButtonNormal.png"));
    m_upGradeButton->m_touchMeCall = CC_CALLBACK_2(ShopPropItemScrollHeadler::upGrade, this);
    m_upGradeButton->setPosition(itemBgSize.width * 0.29,
                                 -itemBgSize.height * 0.15);
    m_upGradeButton->autorelease();
    addChild(m_upGradeButton);
    
    Size upGradeButtonSize = m_upGradeButton->getContentSize();
    
    m_buyButton = new GameSprite(ImagePath("shopItemButtonNormal.png"));
    m_buyButton->m_touchMeCall = CC_CALLBACK_2(ShopPropItemScrollHeadler::buy, this);
    m_buyButton->setPosition(-itemBgSize.width * 0.03,
                             -itemBgSize.height * 0.15);
    m_buyButton->autorelease();
    addChild(m_buyButton);
    
    Size buyButtonSize = m_buyButton->getContentSize();
    
    m_takeUpButton = MenuItemImage::create(ImagePath("shop_zhuanbei.png"),
                                           ImagePath("shop_zhuanbei.png"),
                                           CC_CALLBACK_1(ShopPropItemScrollHeadler::takeUp, this));
    
    m_takeUpButton->setPosition(itemBgSize.width * 0.5,
                                -itemBgSize.height * 0.1);
    Menu * takeUpMenu = Menu::create(m_takeUpButton, NULL);
    takeUpMenu->setPosition(Point::ZERO);
    addChild(takeUpMenu);
    if (prop->isTakeUp())
    {
        m_takeUpButton->setVisible(false);
    }
    
    m_bulletsLabel = Label::createWithTTF("", "fonts/Arial Black.ttf", 25);
    m_bulletsLabel->enableOutline(Color4B(0, 0, 0, 255),2);
    m_bulletsLabel->setPosition(iconBgSize.width * 0.62,
                                iconBgSize.height * 0.25);
    m_bulletsLabel->setAdditionalKerning(-3);
    m_iconBg->addChild(m_bulletsLabel,1);
    Sprite * bulletIcon = Sprite::create(ImagePath("shop_bullet_icon.png"));
    bulletIcon->setPosition(iconBgSize.width * 0.81  ,
                            iconBgSize.height * 0.25);
    m_iconBg->addChild(bulletIcon,1);
    
    Sprite * jinbi1 = Sprite::create(ImagePath("jinbi_icon.png"));
    jinbi1->setPosition(buyButtonSize.width * 0.85,
                        buyButtonSize.height * 0.35);
    jinbi1->setScale(0.75);
    m_buyButton->addChild(jinbi1,1);
    string price = StringUtils::format("%d",prop->getPropPrice());
    m_buyLabel = Label::createWithTTF(price, "fonts/Arial Black.ttf", 30);
    m_buyLabel->enableOutline(Color4B(0, 0, 0, 255),3);
    m_buyLabel->setPosition(buyButtonSize.width * 0.55,
                            buyButtonSize.height * 0.35);
    m_buyLabel->setAdditionalKerning(-3);
    m_buyButton->addChild(m_buyLabel,1);
    Label * buyLabel = Label::createWithTTF("AMMO", "fonts/Arial Black.ttf", 30);
    buyLabel->setPosition(buyButtonSize.width * 0.5,
                          buyButtonSize.height * 0.73);
    buyLabel->enableOutline(Color4B(0, 0, 0, 255),3);
    buyLabel->setAdditionalKerning(-3);
    m_buyButton->addChild(buyLabel,1);
//    Sprite * buyLabel = Sprite::create(ImagePath("shopItemLabel2.png"));
//    buyLabel->setPosition(-itemBgSize.width * 0.03,
//                          -itemBgSize.height * 0.04);
//    addChild(buyLabel,1);
    
    //--
    Label * upgradeLabel = Label::createWithTTF("LEVEL UP", "fonts/Arial Black.ttf", 30);
    upgradeLabel->setPosition(upGradeButtonSize.width * 0.5,
                              upGradeButtonSize.height * 0.73);
    upgradeLabel->enableOutline(Color4B(0, 0, 0, 255),3);
    upgradeLabel->setAdditionalKerning(-3);
    m_upGradeButton->addChild(upgradeLabel);
//    Sprite * upgradeLabel = Sprite::create(ImagePath("shopItemLabel1.png"));
//    upgradeLabel->setPosition(itemBgSize.width * 0.29,
//                              -itemBgSize.height * 0.04);
//    addChild(upgradeLabel);
    
    m_progressBar = new ProgressBar("shopItemTiao1.png","shopItemTiao2.png");
    m_progressBar->autorelease();
    m_progressBar->setBarRight();
    m_progressBar->setPosition(itemBgSize.width * 0.32,
                               itemBgSize.height * 0.18);
    addChild(m_progressBar);
    
    m_levelUpLabel = Label::createWithTTF("LV", "fonts/Arial Black.ttf", 24);
    m_levelUpLabel->enableOutline(Color4B(0, 0, 0, 255),3);
    m_levelUpLabel->setPosition(itemBgSize.width * 0.16,
                                itemBgSize.height * 0.18);
    m_levelUpLabel->setAdditionalKerning(-3);
    addChild(m_levelUpLabel,1);
    
    m_upgradeLabel = Label::createWithTTF("", "fonts/Arial Black.ttf", 30);
    m_upgradeLabel->enableOutline(Color4B(0, 0, 0, 255),3);
    m_upgradeLabel->setPosition(upGradeButtonSize.width * 0.55,
                                upGradeButtonSize.height * 0.35);
    m_upgradeLabel->setAdditionalKerning(-3);
    m_upGradeButton->addChild(m_upgradeLabel,1);
    
    Sprite * jinbi2 = Sprite::create(ImagePath("jinbi_icon.png"));
    jinbi2->setPosition(upGradeButtonSize.width * 0.85,
                        upGradeButtonSize.height * 0.35);
    jinbi2->setScale(0.75);
    m_upGradeButton->addChild(jinbi2);
}
void ShopPropItemScrollHeadler::initLockView()
{
    Prop * prop = PropManager::getInstance()->getPropByIndex(m_index);
    
    Sprite * itemBg = Sprite::create(ImagePath("shopItemBg2.png"));
    addChild(itemBg);
    Size itemBgSize = itemBg->getContentSize();
    //
    string propModelId = prop->getModelId();
    string propIconStr = StringUtils::format("%s_grayicon.png",propModelId.c_str());
    string propNameStr = StringUtils::format("%s_name.png",propModelId.c_str());
    Sprite * icon = Sprite::create(ImagePath(propIconStr));
    icon->setPosition(- itemBgSize.width * 0.35,
                      0);
    addChild(icon);
    Sprite * lockIcon = Sprite::create(ImagePath("shopItemLockIcon.png"));
    lockIcon->setPosition(- itemBgSize.width * 0.3,
                          - itemBgSize.height * 0.18);
    addChild(lockIcon);
    
    Sprite * iconName = Sprite::create(ImagePath(propNameStr));
    iconName->setPosition(-itemBgSize.width * 0.25
                          + iconName->getContentSize().width * 1,
                          itemBgSize.height * 0.2);
    addChild(iconName);
//    log("item name:%s",prop->getItemName().c_str());
//    Label * iconName = Label::createWithTTF(prop->getItemName(), "fonts/Arial Black.ttf", 30);
//    iconName->setPosition(-itemBgSize.width * 0.25
//                            + iconName->getContentSize().width * 0.5,
//                            itemBgSize.height * 0.2);
//    iconName->enableOutline(Color4B(0, 0, 0, 255),3);
//    iconName->setAdditionalKerning(-3);
//    addChild(iconName);
    Label * m_text = Label::createWithTTF(prop->getUnlockStr(), FontPath, 30);
    m_text->setLineHeight(35);
    m_text->setDimensions(itemBgSize.width * 0.3, itemBgSize.height * 0.2);
    m_text->setPosition(-itemBgSize.width * 0.028,
                        -itemBgSize.height * 0.18);
    addChild(m_text);
    
    m_unLockButton = new GameSprite(ImagePath("shopItemButonUnclock.png"));
    m_unLockButton->m_touchMeCall =CC_CALLBACK_2(ShopPropItemScrollHeadler::unLock, this);
    m_unLockButton->autorelease();
    m_unLockButton->setPosition(itemBgSize.width * 0.29,
                                -itemBgSize.height * 0.15);
    addChild(m_unLockButton);
    
    Size unlockButtonSize = m_unLockButton->getContentSize();
    
    Label * unlockName = Label::createWithTTF("UNLOCK", "fonts/Arial Black.ttf", 30);
    unlockName->setPosition(unlockButtonSize.width * 0.5,
                            unlockButtonSize.height * 0.68);
    unlockName->enableOutline(Color4B(0, 0, 0, 255),3);
    unlockName->setAdditionalKerning(-3);
    m_unLockButton->addChild(unlockName);
//    Sprite * unlockName = Sprite::create(ImagePath("shopItemUnlockName.png"));
//    unlockName->setPosition(itemBgSize.width * 0.29,
//                            -itemBgSize.height * 0.15);
//    addChild(unlockName);
    
    Label * unlockLabel = Label::createWithTTF(StringUtils::format("%d",prop->getUnlockGold()),
                                               "fonts/Arial Black.ttf",
                                               30);
    unlockLabel->setPosition(unlockButtonSize.width * 0.5,
                             unlockButtonSize.height * 0.35);
    unlockLabel->enableOutline(Color4B(0, 0, 0, 255),3);
    unlockLabel->setAdditionalKerning(-3);
    m_unLockButton->addChild(unlockLabel);
    Sprite * jinbi2 = Sprite::create(ImagePath("jinbi_icon.png"));
    jinbi2->setPosition(unlockButtonSize.width * 0.85,
                        unlockButtonSize.height * 0.35);
    jinbi2->setScale(0.75);
    m_unLockButton->addChild(jinbi2);
}
void ShopPropItemScrollHeadler::updateDaojuView()
{
    Prop * prop = PropManager::getInstance()->getPropByIndex(m_index);
    
    if (prop->isUnlock())
    {
        int propPrice = prop->getPropPrice();
        int propNum = prop->getNum();
        float level = prop->getStrengthenLevel();
        float limitLevel = prop->getLimitLevel();
        int upgradeGold = prop->getStrengthenGold();
        
        int userGold = GameUser::getInstance()->getUserGold();
        
        if (prop->isMaxLevel())
        {
            m_upgradeLabel->setString("MAX");
        }else
        {
            m_upgradeLabel->setString(StringUtils::format("%d",upgradeGold));
        }
        
        m_levelUpLabel->setString(StringUtils::format("LV.%d",(int)level));
        m_progressBar->updatePercent(level/limitLevel * 100);
        m_bulletsLabel->setString(StringUtils::format("%d",propNum));
        
        if ("daoju9" == prop->getModelId()) {
            m_upgradeLabel->setString("MAX");
            m_progressBar->updatePercent(100);
        }
        
        if (userGold >= propPrice)
        {
            m_buyButton->setEnabled(true,ImagePath("shopItemButtonNormal.png"));
        }else
        {
            m_buyButton->setEnabled(false,ImagePath("shopItemButtonDisable.png"));
        }
        if (userGold >= upgradeGold && !prop->isMaxLevel())
        {
            m_upGradeButton->setEnabled(true,ImagePath("shopItemButtonNormal.png"));
        }else
        {
            m_upGradeButton->setEnabled(false,ImagePath("shopItemButtonDisable.png"));
        }
        if ("daoju9" == prop->getModelId()) {
            m_upGradeButton->setEnabled(false,ImagePath("shopItemButtonDisable.png"));
        }
    }
}
void ShopPropItemScrollHeadler::setHealderSelect()
{
    auto spriteFrameCache = SpriteFrameCache::getInstance();
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("texiao2.plist"));
    
    Action * guangAc = RepeatForever::create(BaseUtil::makeAnimateWithNameAndIndex("item_flash", 4));
    Sprite * texiao = Sprite::create();
    Sprite * guang = Sprite::create();
    texiao->addChild(guang);
    guang->runAction(guangAc);
    m_iconBg->addChild(texiao);
    Size iconBgSize = m_iconBg->getContentSize();
    texiao->setPosition(iconBgSize.width * 0.5, iconBgSize.height * 0.5);
    texiao->setScale(1.5);
    texiao->runAction(Sequence::create(DelayTime::create(1),
                                       FadeOut::create(0.3),
                                       CallFuncN::create(CC_CALLBACK_1(ShopPropItemScrollHeadler::guangEnd, this)),
                                       NULL));
}
void ShopPropItemScrollHeadler::guangEnd(cocos2d::Node *pSender)
{
    pSender->stopAllActions();
    pSender->removeFromParentAndCleanup(true);
}
void ShopPropItemScrollHeadler::updateData()
{
    Prop * prop = PropManager::getInstance()->getPropByIndex(m_index);
    if (prop->isUnlock())
    {
        if (prop->isTakeUp())
        {
            m_takeUpButton->setVisible(false);
        }else
        {
            m_takeUpButton->setVisible(true);
        }
    }
    updateDaojuView();
}
void ShopPropItemScrollHeadler::upGrade(Touch * touch, Event * event)
{
    GameSprite * spr = (GameSprite *)event->getCurrentTarget();
    if (!spr->isEnable())
    {
        return;
    }
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
    Prop * prop = PropManager::getInstance()->getPropByIndex(m_index);
    bool sec = prop->addStrengthenLevel();
    if (sec)
    {
        SimpleAudioEngine::getInstance()->playEffect(MusicPath("propUpgrade.mp3").c_str());
//        m_shopScene->updateUserData();
//        updateDaojuView();
        GameShowLevelupLayer * showLayer = new GameShowLevelupLayer(prop->getModelId());
        showLayer->autorelease();
        m_shopScene->addChild(showLayer,10);
    }else
    {
        
    }
}
void ShopPropItemScrollHeadler::unLock(Touch * touch, Event * event)
{
    GameSprite * spr = (GameSprite *)event->getCurrentTarget();
    if (!spr->isEnable())
    {
        return;
    }
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
    Prop * prop = PropManager::getInstance()->getPropByIndex(m_index);
    bool sec = prop->unlockProp();
    if (sec)
    {
//        m_shopScene->updateUserData();
        initDaojuView();
    }else
    {
        log("no enough money for unlock");
    }
}
void ShopPropItemScrollHeadler::buy(Touch * touch, Event * event)
{
    GameSprite * spr = (GameSprite *)event->getCurrentTarget();
    if (!spr->isEnable())
    {
        return;
    }
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
    Prop * prop = PropManager::getInstance()->getPropByIndex(m_index);
    bool sec = prop->buyProp();
    if (sec)
    {
//        m_shopScene->updateUserData();
//        updateDaojuView();
    }else
    {
        
    }
}
void ShopPropItemScrollHeadler::takeUp(cocos2d::Ref *pSender)
{
    Prop * prop = PropManager::getInstance()->getPropByIndex(m_index);
    PropManager::getInstance()->takeUpProp(prop->getId());
    
}
void ShopPropItemScrollHeadler::showDiscView(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Sprite * icon = (Sprite *) event->getCurrentTarget();
    Vec2 iconPoint = convertToWorldSpace(icon->getPosition());
    
    Prop * prop = PropManager::getInstance()->getPropByIndex(m_index);
    std::string name = prop->getModelId();
    std::string disc = prop->getItemDestription();
    GameShowDiscLayer * showLayer = new GameShowDiscLayer(name,disc,iconPoint);
    showLayer->autorelease();
    m_shopScene->addChild(showLayer);
    
}
