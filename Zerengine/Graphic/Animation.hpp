#pragma once

#include "Sprite.hpp"

enum AnimType: bool {
    SCALED = false,
    UNSCALED = true
};

class Animation {
friend void animationSys(LateFixedSystem, World& world);
public:
    Animation(const AnimationAsset& newAnimations, const std::string& newAnim, AnimType newIsUnscaled = AnimType::SCALED) noexcept:
        animationAsset(newAnimations),
        curFrame(newAnimations.anims.at(newAnim).size() - 1),
        curTimer(newAnimations.anims.at(newAnim).at(curFrame).first),
        curAnimName(newAnim),
        isUnscaled(newIsUnscaled),
        oneShotAnimationStop(false),
        oneShotFirst(newAnimations.anims.at(newAnim).getAnimationType() == AnimationType::ONE_SHOT),
        reverseMode(false),
        speed(1) {
    }

    void update(float delta, Sprite& sprt) {
        if (!oneShotAnimationStop) {
            auto curAnimIt = animationAsset.anims.find(curAnimName);
            if (curAnimIt == animationAsset.anims.end()) {
                printf("Impossible de lancer l'animation: %s\n", curAnimName.c_str());
                return;
            }

            curTimer += delta * speed;

            const auto& animPair = curAnimIt->second.at(curFrame);

            if (curTimer >= animPair.first) {
                curTimer -= animPair.first;
                if (reverseMode) {
                    if (curFrame > 0) {
                        curFrame--;
                    } else {
                        curFrame = 0;
                        reverseMode = false;
                    }
                } else {
                    if (curAnimIt->second.size() > curFrame + 1) {
                        curFrame++;
                    } else {
                        if (curAnimIt->second.getAnimationType() == AnimationType::ONE_SHOT) {
                            if (oneShotFirst) {
                                oneShotFirst = false;
                                curFrame = 0;
                            } else {
                                oneShotAnimationStop = true;
                            }
                        } else if (curAnimIt->second.getAnimationType() == AnimationType::BOOMERANG) {
                            reverseMode = true;
                            if (curFrame > 0) {
                                curFrame--;
                            } else {
                                curFrame = 0;
                            }
                        } else {
                            curFrame = 0;
                        }
                    }
                }
                const auto& newImageData = curAnimIt->second.at(curFrame).second;
                sprt.setTextureRect(newImageData);
                // sprt.sprite.setOrigin(newImageData.spriteRect.z * newImageData.origin.x, newImageData.spriteRect.w * newImageData.origin.y);
            }
        }
    }

    void update(float delta, UI& ui) {
        if (!oneShotAnimationStop) {
            auto curAnimIt = animationAsset.anims.find(curAnimName);
            if (curAnimIt == animationAsset.anims.end()) {
                printf("Impossible de lancer l'animation: %s\n", curAnimName.c_str());
                return;
            }

            curTimer += delta * speed;

            const auto& animPair = curAnimIt->second.at(curFrame);

            if (curTimer >= animPair.first) {
                curTimer -= animPair.first;
                if (reverseMode) {
                    if (curFrame > 0) {
                        curFrame--;
                    } else {
                        curFrame = 0;
                        reverseMode = false;
                    }
                } else {
                    if (curAnimIt->second.size() > curFrame + 1) {
                        curFrame++;
                    } else {
                        if (curAnimIt->second.getAnimationType() == AnimationType::ONE_SHOT) {
                            if (oneShotFirst) {
                                oneShotFirst = false;
                                curFrame = 0;
                            } else {
                                oneShotAnimationStop = true;
                            }
                        } else if (curAnimIt->second.getAnimationType() == AnimationType::BOOMERANG) {
                            reverseMode = true;
                            if (curFrame > 0) {
                                curFrame--;
                            } else {
                                curFrame = 0;
                            }
                        } else {
                            curFrame = 0;
                        }
                    }
                }
                const auto& newImageData = curAnimIt->second.at(curFrame).second;
                ui.setTextureRect(newImageData);
                // sprt.sprite.setOrigin(newImageData.spriteRect.z * newImageData.origin.x, newImageData.spriteRect.w * newImageData.origin.y);
            }
        }
    }

    void play(const std::string& newAnim) {
        if (curAnimName != newAnim) {
            if (auto newAnimIt = animationAsset.anims.find(newAnim); newAnimIt != animationAsset.anims.end()) {
                curAnimName = newAnim;
                curFrame = newAnimIt->second.size() - 1;
                curTimer = newAnimIt->second.at(curFrame).first;
                oneShotAnimationStop = false;
                reverseMode = false;
                if (newAnimIt->second.getAnimationType() == AnimationType::ONE_SHOT) {
                    oneShotFirst = true;
                }
            } else {
                printf("L'animation %s n'existe pas\n", newAnim.c_str());
            }
        }
    }

    [[nodiscard]] constexpr const std::string& getCurrentAnimationName() const noexcept {
        return curAnimName;
    }

private:
    const AnimationAsset& animationAsset;
    std::size_t curFrame;
    float curTimer;
    std::string curAnimName;
    AnimType isUnscaled;
    bool oneShotAnimationStop;
    bool oneShotFirst;
    bool reverseMode;

public:
    float speed;
};

///////////////////////////////////////////////////////////////////////////////////

void animationSys(LateFixedSystem, World& world) {
#ifdef ZER_DEBUG_INTEGRITY
    try {
#endif
    auto [time] = world.resource<const Time>();

    for (auto [_, anim, sprt]: world.view<Animation, Sprite>()) {
        if (anim.isUnscaled)
            anim.update(time.unscaledFixedDelta(), sprt);
        else
            anim.update(time.fixedDelta(), sprt);
    }

    for (auto [_, anim, ui]: world.view<Animation, UI>()) {
        if (anim.isUnscaled)
            anim.update(time.unscaledFixedDelta(), ui);
        else
            anim.update(time.fixedDelta(), ui);
    }
#ifdef ZER_DEBUG_INTEGRITY
    } catch(const std::exception& except) {
        printf("%s: %s\n", __func__, except.what());
    }
#endif
}