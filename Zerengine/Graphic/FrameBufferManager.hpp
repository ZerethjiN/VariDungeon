#pragma once
#include <unordered_map>
#include "IGraphicsPipeline.hpp"

class FrameBufferManager final: public IResource {
public:
    ~FrameBufferManager() {
        for (auto& pair: frameBuffers) {
            delete pair.second;
        }
    }

public:
    template <typename T>
    [[nodiscard]] T& get(VulkanEngine& newEngine) {
        auto pipelineIt = frameBuffers.find(typeid(T).hash_code());
        if (pipelineIt == frameBuffers.end()) {
            pipelineIt = frameBuffers.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(typeid(T).hash_code()),
                std::forward_as_tuple(new T(newEngine))
            ).first;
            newEngine.frameBuffers.emplace_back(pipelineIt->second);
        }
        return *static_cast<T*>(pipelineIt->second);
    }

    void clear() {
        for (auto& pair: frameBuffers) {
            delete pair.second;
        }
        frameBuffers.clear();
    }

private:
    std::unordered_map<std::size_t, IFrameBuffer*> frameBuffers;
};