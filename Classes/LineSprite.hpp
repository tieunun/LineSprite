//
//  LineSprite.h
//  LineSample
//
//  Created by 阿部耕平 on 2014/10/26.
//
//

#ifndef __LineSample__LineSprite__
#define __LineSample__LineSprite__

#include <vector>
#include <cocos2d.h>

class LineSprite final : public cocos2d::Node
{
public:
    static LineSprite* create();
    
    void setSprite(cocos2d::Sprite* sprite);
    
    void setSpriteFrameName(const std::string& spriteFrameName);
    
    void setContentSize(const cocos2d::Size& size) override;
    
    void setColor(const cocos2d::Color3B& color) override;
    
    void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;

private:
    cocos2d::RefPtr<cocos2d::Sprite> sp;
    std::vector<cocos2d::RefPtr<cocos2d::Sprite>> draws;
    
    void adjust();
};

#endif /* defined(__LineSample__LineSprite__) */
