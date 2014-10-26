//
//  LineSprite.cpp
//  LineSample
//
//  Created by 阿部耕平 on 2014/10/26.
//
//

#include <cmath>
#include "LineSprite.hpp"

LineSprite* LineSprite::create()
{
    auto ref = new LineSprite();
    if (ref && ref->init())
    {
        ref->autorelease();
    }
    else
    {
        CC_SAFE_RELEASE(ref);
    }
    return ref;
}

void LineSprite::setSprite(cocos2d::Sprite* sprite)
{
    this->sp = sprite;
    
    this->draws.clear();
    this->adjust();
}

void LineSprite::setSpriteFrameName(const std::string& spriteFrameName)
{
    auto spFrame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
    auto sprite = cocos2d::Sprite::createWithSpriteFrame(spFrame);
    this->sp = sprite;
    
    this->draws.clear();
    this->adjust();
}

void LineSprite::setContentSize(const cocos2d::Size& size)
{
    Node::setContentSize(size);
    this->adjust();
}

void LineSprite::setColor(const cocos2d::Color3B& color)
{
    Node::setColor(color);
    for (auto sprite : this->draws)
    {
        sprite->setColor(color);
    }
}

void LineSprite::adjust()
{
    if (!this->sp)
    {
        return;
    }
    
    float frameWidth = this->sp.get()->getSpriteFrame()->getRect().size.width;
    if (frameWidth == 0)
    {
        return;
    }
    
    float selfWidth = this->getContentSize().width;
    int repeat = static_cast<int>(std::ceil(selfWidth / frameWidth));
    if (repeat == 0)
    {
        return;
    }
    
    // adjust a number of sprites
    int existNum = static_cast<int>(draws.size());
    if (repeat < draws.size())
    {
        // erase unnecessary sprites
        int numErase = existNum - repeat;
        for (int i = 0; i < numErase; i++)
        {
            auto sprite = this->draws.back();
            
            this->draws.pop_back();
        }
    }
    else if (repeat > draws.size())
    {
        // add sprites
        int numAdd = repeat - existNum;
        for (int i = 0; i < numAdd; i++)
        {
            auto spFrame = this->sp->getSpriteFrame();
            auto sprite = cocos2d::Sprite::createWithSpriteFrame(spFrame);
            sprite->setColor(this->getColor());
            
            draws.emplace_back(sprite);
        }
    }
    
    // place sprites
    float fraction = selfWidth - frameWidth * std::floor(selfWidth / frameWidth);
    for (int i = 0; i < repeat; i++)
    {
        auto sprite = draws[i];
        
        bool isLastLoop = (i == repeat - 1);
        float spWidth = (isLastLoop && fraction != 0) ? fraction : frameWidth;

        auto spFrame = sprite->getSpriteFrame();
        auto rect = spFrame->getRect();
        if (spFrame->isRotated())
        {
            rect.size.height = spWidth;
        }
        else
        {
            rect.size.width = spWidth;
        }
        spFrame->setRect(rect);
        sprite->setSpriteFrame(spFrame);
        sprite->setPosition(frameWidth * i + spWidth / 2, 0);
    }
}

void LineSprite::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    for (auto sp : this->draws) {
        sp->visit(renderer, transform, flags);
    }
}
