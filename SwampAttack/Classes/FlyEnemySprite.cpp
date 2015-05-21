//
//  FlyEnemySprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/4/23.
//
//

#include "FlyEnemySprite.h"
#include "BaseUtil.h"


FlyEnemySprite::FlyEnemySprite(Enemy * model):EnemySprite(model)
{
    string name = m_model->getModelId();
    EnemyInfoData info = EnemyInfo::getInstance()->getInfoByName(name);
    float attackSpeed = m_model->getAttackSpeed();
    
    Action * walkAction = RepeatForever::create(BaseUtil::makeAnimateWithNameAndIndex(name + "_fly", info.walkFrames));
    walkAction->retain();
    
    Action * attackAction = Spawn::create(
                                          Sequence::create(DelayTime::create(attackSpeed * info.attackFrame),
                                                           CallFunc::create(CC_CALLBACK_0(FlyEnemySprite::attackCall, this)), NULL),
                                          BaseUtil::makeAnimateWithNameIndexDelay(name + "_attack", info.attackFrames,attackSpeed),
                                          NULL);
    attackAction->retain();
//    Action * dieAction = Sequence::create(BaseUtil::makeAnimateWithNameAndIndex(name + "_down", info.downFrames),
//                                          CallFunc::create(CC_CALLBACK_0(FlyEnemySprite::dieCall, this)),
//                                          NULL);
//    dieAction->retain();
    
    m_map["walkAction"] = walkAction;
    m_map["attackAction"] = attackAction;
//    m_map["dieAction"] = dieAction;
    
//    setArmorView();
    scheduleUpdate();
    
}
void FlyEnemySprite::update(float data)
{
    if (m_model->isDieing())
    {
        die();
    }else if (m_model->isAttack())
    {
        attack();
    }else if (m_model->isWalk())
    {
        move();
    }else if (m_model->isDied())
    {
        m_model->diedCall();
        unscheduleUpdate();
        removeFromParentAndCleanup(true);
        return;
    }
    if (m_model->isShowHurt()) {
        healthBar->setVisible(true);
        healthBar->updatePercent(m_model->getHealthPercent());
    }else
    {
        healthBar->setVisible(false);
    }
    setPosition(m_model->getPosition());
    
    if (isHaveArmor && m_model->isWeak() && armorSprite) {
        isHaveArmor = false;
        string armorName = m_model->getCapId();
        EnemyInfoData info = EnemyInfo::getInstance()->getInfoByName(armorName);
        
        Layer * gameLayer =(Layer *) this->getParent();
        Sprite * armor = Sprite::createWithTexture(armorSprite->getTexture(),
                                                   armorSprite->getTextureRect());
        gameLayer->addChild(armor);
        armor->setPosition(this->getPosition() + Vec2(info.width * 0.5,info.height));
        
        armorSprite->stopAllActions();
        armorSprite->removeFromParentAndCleanup(true);
        ActionInterval * a0 = RotateTo::create(0.6, 180);
        ActionInterval * a1 = MoveBy::create(0.6, Vec2(100, 0));
        ActionInterval * a2 = EaseSineIn::create(MoveBy::create(0.6, Vec2(0, -90)));
        ActionInterval * a3 = Sequence::create(Spawn::create(a0,a1,a2, NULL),
                                               FadeOut::create(0.2), NULL);
        armor->runAction(a3);
    }
}
void FlyEnemySprite::setArmorView()
{
    string armorName = m_model->getCapId();
    if ((armorName.size() > 0)) {
        isHaveArmor = true;
        EnemyInfoData info = EnemyInfo::getInstance()->getInfoByName(armorName);
        armorSprite = Sprite::create();
        addChild(armorSprite);
        armorSprite->setPosition(info.width * 0.5,info.height);
        
        float attackSpeed = m_model->getAttackSpeed();
        Action * walkAction = RepeatForever::create(BaseUtil::makeAnimateWithNameAndIndex(armorName + "_walk", info.walkFrames));
        walkAction->retain();
        m_map["armorWalkAction"] = walkAction;
        
        Action * attackAction = RepeatForever::create(
                                                      Spawn::create(
                                                                    Sequence::create(DelayTime::create(attackSpeed * info.attackFrame),
                                                                                     CallFunc::create(CC_CALLBACK_0(FlyEnemySprite::attackCall, this)), NULL),
                                                                    BaseUtil::makeAnimateWithNameIndexDelay(armorName + "_attack", info.attackFrames,attackSpeed),
                                                                    NULL)
                                                      );
        attackAction->retain();
        m_map["armorAttackAction"] = attackAction;
    }
}
void FlyEnemySprite::move()
{
    if (actionStatus == isMoving) {
        return;
    }
    actionStatus = isMoving;
    stopAllActions();
    runAction(m_map["walkAction"]);
    if (isHaveArmor) {
        armorSprite->stopAllActions();
        armorSprite->runAction(m_map["armorWalkAction"]);
    }
}
void FlyEnemySprite::attack()
{
    if (actionStatus == isAttacking) {
        return;
    }
    actionStatus = isAttacking;
    stopAllActions();
    runAction(m_map["attackAction"]);
    if (isHaveArmor) {
        armorSprite->stopAllActions();
        armorSprite->runAction(m_map["armorAttackAction"]);
    }
}
void FlyEnemySprite::die()
{
    
    if (actionStatus == isDieing) {
        return;
    }
    actionStatus = isDieing;
    dieCall();
//    stopAllActions();
//    runAction(m_map["dieAction"]);
}