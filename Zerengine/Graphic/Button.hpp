#pragma once

class OnClickButton final: public IComponent {
public:
    OnClickButton(const glm::vec4& newRect, void(*newCallback)(World&, Ent)):
        rect(newRect),
        callback(newCallback) {
    }

public:
    glm::vec4 rect;
    void(*callback)(World&, Ent);
};

class OnHoverButton final: public IComponent {
public:
    OnHoverButton(const glm::vec4& newRect, void(*newHoverCallback)(World&, Ent), void(*newUnhoverCallback)(World&, Ent)):
        rect(newRect),
        hoverCallback(newHoverCallback),
        unhoverCallback(newUnhoverCallback),
        isHover(false) {
    }

public:
    glm::vec4 rect;
    void(*hoverCallback)(World&, Ent);
    void(*unhoverCallback)(World&, Ent);
    bool isHover;
};