#pragma once
#include <unordered_map>
#include "IGraphicsPipeline.hpp"

class PipelineManager final {
public:
    ~PipelineManager() {
        for (auto& pair: pipelines) {
            delete pair.second;
        }
    }

public:
    template <typename T>
    [[nodiscard]] T& get(VulkanEngine& newEngine, const VkRenderPass& newRenderPass) {
        auto pipelineIt = pipelines.find(typeid(T).hash_code());
        if (pipelineIt == pipelines.end()) {
            pipelineIt = pipelines.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(typeid(T).hash_code()),
                std::forward_as_tuple(new T(newEngine, newRenderPass))
            ).first;
        }
        return *static_cast<T*>(pipelineIt->second);
    }

    void clear() {
        for (auto& pair: pipelines) {
            delete pair.second;
        }
        pipelines.clear();
    }

private:
    std::unordered_map<std::size_t, IGraphicsPipeline*> pipelines;
};