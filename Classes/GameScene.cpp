#include "GameScene.h"
#include "Definitions.h"
#include "Bird.h"
#include "GameOverScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vect(0, 0));

    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());


    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create("ipadhd/Background.png");
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(backgroundSprite);

    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    edgeBody->setContactTestBitmask(true);



    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    edgeNode->setPhysicsBody(edgeBody);

    this->addChild(edgeNode);

    this->schedule(schedule_selector(GameScene::spawnPipe), PIPE_SPAWN_FREQUENCY *visibleSize.width);   

    bird = new Bird(this);

    

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);



   /* auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(GameScene::onMouseDown, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);*/

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    _score = 0;  

    __String* tempScore = __String::createWithFormat("%i",_score );

    _scoreLable = Label::createWithTTF(tempScore->getCString(), "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE);
    _scoreLable->setColor(Color3B::WHITE);
    _scoreLable->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.75 + origin.y));

    this->addChild(_scoreLable);


    this->scheduleUpdate();

    return true;
}
void GameScene::spawnPipe(float dt) {
    pipe.SpawnPipe(this);
}
bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact) {
     
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();
    if ((BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask()) ||
        (BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask())) 
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/Hit.mp3");

        auto scene = GameOverScene::createScene(_score);
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    }
    else if ((BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && POINT_COLLISION_BITMASK == b->getCollisionBitmask()) ||
        (BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && POINT_COLLISION_BITMASK == a->getCollisionBitmask()))
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/Point.mp3");

        _score++;
        __String* tempScore = __String::createWithFormat("%i", _score);
        _scoreLable->setString(tempScore->getCString());
    }
    return true;
}

//void GameScene::onMouseDown(cocos2d::Event* event) {
//
//    bird->Fly();
//    this->scheduleOnce(schedule_selector(GameScene::StopFlying),BIRD_FLY_DURATION);
//
//}
bool GameScene::onTouchBegan(cocos2d::Touch*, cocos2d::Event*) {
    bird->fly();

    this->scheduleOnce(schedule_selector(GameScene::stopFlying), BIRD_FLY_DURATION);

    return true;
}


void GameScene::stopFlying(float dt) {
    bird->stopFlying();
}

void GameScene::update(float dt) {
    bird->fall();
}