#pragma once

#include "Sprite.hpp"

template <typename E>
concept IsAnimationEnumConcept = [] -> bool {
    static_assert(std::is_enum_v<E>, "IsAnimationEnumConcept: L'enum des frames d'animation n'est pas un \"enum\".");
    static_assert(std::is_scoped_enum_v<E>, "IsAnimationEnumConcept: L'enum des frames d'animation n'est pas un \"enum class\".");
    static_assert(std::is_same_v<std::underlying_type_t<E>, std::size_t>, "IsAnimationEnumConcept: L'enum des frames d'animation n'est pas de type \"std::size_t\".");
    return true;
}();

enum class AnimType: bool {
    SCALED = false,
    UNSCALED = true
};

class Animation final: public IComponent {
friend void animationSys(LateUnscaledFixedSystem, World& world);
public:
    template <typename E> requires (IsAnimationEnumConcept<E>)
    Animation(const AnimationAsset& newAnimations, const E& newAnimName, std::size_t newBegginingFrame, float animationSpeed = 1, AnimType newIsUnscaled = AnimType::SCALED) noexcept:
        animationAsset(newAnimations),
        curFrame(newBegginingFrame),
        curTimer(newAnimations.anims.at(static_cast<std::size_t>(newAnimName)).at(curFrame).first),
        curAnimName(static_cast<std::size_t>(newAnimName)),
        isUnscaled(newIsUnscaled),
        oneShotAnimationStop(false),
        oneShotFirst(newAnimations.anims.at(static_cast<std::size_t>(newAnimName)).getAnimationType() == AnimationType::ONE_SHOT),
        reverseMode(false),
        speed(animationSpeed) {
    }

    template <typename E> requires (IsAnimationEnumConcept<E>)
    Animation(const AnimationAsset& newAnimations, const E& newAnimName, float animationSpeed, AnimType newIsUnscaled = AnimType::SCALED) noexcept:
        animationAsset(newAnimations),
        curFrame(newAnimations.anims.at(static_cast<std::size_t>(newAnimName)).size() - 1),
        curTimer(newAnimations.anims.at(static_cast<std::size_t>(newAnimName)).at(curFrame).first),
        curAnimName(static_cast<std::size_t>(newAnimName)),
        isUnscaled(newIsUnscaled),
        oneShotAnimationStop(false),
        oneShotFirst(newAnimations.anims.at(static_cast<std::size_t>(newAnimName)).getAnimationType() == AnimationType::ONE_SHOT),
        reverseMode(false),
        speed(animationSpeed) {
    }

    template <typename E> requires (IsAnimationEnumConcept<E>)
    Animation(const AnimationAsset& newAnimations, const E& newAnimName, AnimType newIsUnscaled = AnimType::SCALED) noexcept:
        animationAsset(newAnimations),
        curFrame(newAnimations.anims.at(static_cast<std::size_t>(newAnimName)).size() - 1),
        curTimer(newAnimations.anims.at(static_cast<std::size_t>(newAnimName)).at(curFrame).first),
        curAnimName(static_cast<std::size_t>(newAnimName)),
        isUnscaled(newIsUnscaled),
        oneShotAnimationStop(false),
        oneShotFirst(newAnimations.anims.at(static_cast<std::size_t>(newAnimName)).getAnimationType() == AnimationType::ONE_SHOT),
        reverseMode(false),
        speed(1) {
    }

    void update(float delta, Sprite& sprt) {
        if (!oneShotAnimationStop) {
            auto curAnimIt = animationAsset.anims.find(curAnimName);
            if (curAnimIt == animationAsset.anims.end()) {
                printf("Impossible de lancer l'animation: %zu\n", curAnimName);
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
                printf("Impossible de lancer l'animation: %zu\n", curAnimName);
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

    template <typename E> requires (IsAnimationEnumConcept<E>)
    void play(const E& newAnim) {
        if (curAnimName != static_cast<std::size_t>(newAnim)) {
            if (auto newAnimIt = animationAsset.anims.find(static_cast<std::size_t>(newAnim)); newAnimIt != animationAsset.anims.end()) {
                curAnimName = static_cast<std::size_t>(newAnim);
                curFrame = newAnimIt->second.size() - 1;
                curTimer = newAnimIt->second.at(curFrame).first;
                oneShotAnimationStop = false;
                reverseMode = false;
                if (newAnimIt->second.getAnimationType() == AnimationType::ONE_SHOT) {
                    oneShotFirst = true;
                }
            } else {
                printf("L'animation %zu n'existe pas\n", static_cast<std::size_t>(newAnim));
            }
        }
    }

    [[nodiscard]] float getCurrentTimeOfTotalDuration() const noexcept {
        float newCurTime = 0;

        auto curAnimIt = animationAsset.anims.find(curAnimName);
        if (curAnimIt == animationAsset.anims.end()) {
            printf("Impossible de lancer l'animation: %zu\n", curAnimName);
            return 0;
        }

        if (curAnimIt->second.getAnimationType() != AnimationType::BOOMERANG || reverseMode != true) {
            for (std::size_t i = 0; i < curFrame; i++) {
                newCurTime += curAnimIt->second.at(i).first;
            }

            newCurTime += curTimer;
        } else {
            for (std::size_t i = 0; i < curAnimIt->second.size(); i++) {
                newCurTime += curAnimIt->second.at(i).first;
            }

            for (std::size_t i = curAnimIt->second.size() - 1; i > curFrame; i--) {
                newCurTime += curAnimIt->second.at(i).first;
            }

            newCurTime += curTimer;
        }

        return newCurTime;
    }

    [[nodiscard]] constexpr std::size_t getCurrentAnimationName() const noexcept {
        return curAnimName;
    }

private:
    const AnimationAsset& animationAsset;
    std::size_t curFrame;
    float curTimer;
    std::size_t curAnimName;
    AnimType isUnscaled;
    bool oneShotAnimationStop;
    bool oneShotFirst;
    bool reverseMode;

public:
    float speed;
};

///////////////////////////////////////////////////////////////////////////////////

void animationSys(LateUnscaledFixedSystem, World& world) {
    auto [time] = world.resource<const Time>();

    for (auto [_, anim, sprt]: world.view<Animation, Sprite>()) {
        if (anim.isUnscaled == AnimType::UNSCALED)
            anim.update(time.unscaledFixedDelta(), sprt);
        else
            anim.update(time.fixedDelta(), sprt);
    }

    for (auto [_, anim, ui]: world.view<Animation, UI>()) {
        if (anim.isUnscaled == AnimType::UNSCALED)
            anim.update(time.unscaledFixedDelta(), ui);
        else
            anim.update(time.fixedDelta(), ui);
    }
}