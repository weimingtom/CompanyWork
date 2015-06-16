//
//  GameLoadingScene.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/16.
//
//

#include "GameLoadingScene.h"

#include "GameFightScene.h"

#include "GameLoading.h"
#include "GuanQiaManager.h"
#include "EnemyManager.h"


Scene * GameLoadingScene::scene(std::string guanqiaId)
{
    Scene * scene = Scene::create();
    
    GameLoadingScene * layer = new GameLoadingScene(guanqiaId);
    layer->autorelease();
    scene->addChild(layer);
    return scene;
}
GameLoadingScene::GameLoadingScene(std::string guanqiaId):
m_guanqiaId(guanqiaId)
{
    
    Sprite * bg = Sprite::create(ImagePath("gameLoadingBg.png"));
    bg->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                    m_visibleOrigin.y + m_visibleSize.height * 0.5);
    addChild(bg);
    
    scheduleOnce(CC_SCHEDULE_SELECTOR(GameLoadingScene::loadingData), 0.3);
    scheduleOnce(CC_SCHEDULE_SELECTOR(GameLoadingScene::gotoFightScene), 3);
}
GameLoadingScene::~GameLoadingScene()
{
    
}
void GameLoadingScene::loadingData(float data)
{
    log("loading data");
    GuanqiaModel * guanQia = GuanQiaManager::getInstance()->getGuanqiaById(m_guanqiaId);
    
    GameLoading::loadFrames();
    GuanQiaManager::getInstance()->setCurrentGuanqiaId(guanQia->getId());
    EnemyManager::getInstance()->setData(guanQia->getMonsters());
}
void GameLoadingScene::gotoFightScene(float data)
{
    log("go to fight scene");
    Director::getInstance()->replaceScene(GameFightScene::scene());
}