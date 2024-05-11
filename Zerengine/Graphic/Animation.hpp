#pragma once

#include "Sprite.hpp"

enum AnimType: bool {
    SCALED = false,
    UNSCALED = true
};

class Animation {
friend void animationSys(World& world);
public:
    Animation(const AnimationAsset& newAnimations, const std::string& newAnim, AnimType newIsUnscaled = AnimType::SCALED) noexcept:
        animationAsset(newAnimations),
        curFrame(newAnimations.anims.at(newAnim).size() - 1),
        curTimer(newAnimations.anims.at(newAnim).at(curFrame).first),
        curAnimName(newAnim),
        isUnscaled(newIsUnscaled),
        speed(1) {
    }

    void update(float delta, Sprite& sprt) {
        auto curAnimIt = animationAsset.anims.find(curAnimName);
        if (curAnimIt == animationAsset.anims.end()) {
            printf("Impossible de lancer l'animation: %s\n", curAnimName.c_str());
            return;
        }

        curTimer += delta * speed;

        auto& animPair = curAnimIt->second.at(curFrame);

        if (curTimer >= animPair.first) {
            curTimer -= animPair.first;
            if (curAnimIt->second.size() > curFrame + 1) {
                curFrame++;
            } else {
                curFrame = 0;
            }
            const auto& newImageData = curAnimIt->second.at(curFrame).second;
            sprt.setTextureRect(newImageData);
            // sprt.sprite.setOrigin(newImageData.spriteRect.z * newImageData.origin.x, newImageData.spriteRect.w * newImageData.origin.y);
        }
    }

    void update(float delta, UI& ui) {
        auto curAnimIt = animationAsset.anims.find(curAnimName);
        if (curAnimIt == animationAsset.anims.end()) {
            printf("Impossible de lancer l'animation: %s\n", curAnimName.c_str());
            return;
        }

        curTimer += delta * speed;

        auto& animPair = curAnimIt->second.at(curFrame);

        if (curTimer >= animPair.first) {
            curTimer -= animPair.first;
            if (curAnimIt->second.size() > curFrame + 1) {
                curFrame++;
            } else {
                curFrame = 0;
            }
            const auto& newImageData = curAnimIt->second.at(curFrame).second;
            ui.setTextureRect(newImageData);
            // sprt.sprite.setOrigin(newImageData.spriteRect.z * newImageData.origin.x, newImageData.spriteRect.w * newImageData.origin.y);
        }
    }

    void play(const std::string& newAnim) {
        if (curAnimName != newAnim) {
            if (auto newAnimIt = animationAsset.anims.find(newAnim); newAnimIt != animationAsset.anims.end()) {
                curAnimName = newAnim;
                curFrame = newAnimIt->second.size() - 1;
                curTimer = newAnimIt->second.at(curFrame).first;
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

public:
    float speed;
};

///////////////////////////////////////////////////////////////////////////////////

void animationSys(World& world) {
#ifdef ZER_DEBUG_INTEGRITY
    try {
#endif
    auto [time] = world.getRes<const Time>();

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