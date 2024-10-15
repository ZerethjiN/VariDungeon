#pragma once
#include <unordered_map>
#include "IGraphicsPipeline.hpp"

class FrameBufferManager final: public IResource {
public:
    template <typename T>
    [[nodiscard]] T& get(VulkanEngine& newEngine) {
        auto pipelineIt = frameBuffers.find(typeid(T).hash_code());
        if (pipelineIt == frameBuffers.end()) {
            pipelineIt = frameBuffers.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(typeid(T).hash_code()),
                std::forward_as_tuple(std::make_unique<T>(newEngine))
            ).first;
            newEngine.frameBuffers.emplace_back(pipelineIt->second.get());
        }
        return *static_cast<T*>(pipelineIt->second.get());
    }

    void clear() {
        frameBuffers.clear();
    }

private:
    std::unordered_map<std::size_t, std::unique_ptr<IFrameBuffer>> frameBuffers;
};