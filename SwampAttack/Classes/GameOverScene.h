//
//  GameOverScene.h
//  SwampAttack
//
//  Created by 张洪星 on 15/6/1.
//
//

#ifndef __SwampAttack__GameOverScene__
#define __SwampAttack__GameOverScene__

#include "BaseCode.h"


class GameOverScene : public Layer {
private:
    GameOverStatus  m_overStatus;
    EventListenerTouchOneByOne * m_listener;
    
    std::vector<std::string> guideText;
    Label   * guideTextLabel;
    int     guideIndex;
public:
    static Scene * scene(GameOverStatus status, RenderTexture * rt);
    GameOverScene(GameOverStatus status,RenderTexture * rt);
    ~GameOverScene();
    
    bool init();
    bool    touchBegan(Touch * touch, Event * event);
    
//    void    nextGuanqia(Ref * pSender);
    void    restartGame(Ref * pSender);
    void    gotoMap(Ref * pSender);
    void    gotoShop(Ref * pSender);
    
    void    userGuide(float data);
};

#endif /* defined(__SwampAttack__GameOverScene__) */
