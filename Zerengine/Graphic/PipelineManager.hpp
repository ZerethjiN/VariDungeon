#pragma once
#include <unordered_map>
#include "IGraphicsPipeline.hpp"

class PipelineManager final: public IResource {
public:
    template <typename T>
    [[nodiscard]] T& get(VulkanEngine& newEngine, const VkRenderPass& newRenderPass) {
        auto pipelineIt = pipelines.find(typeid(T).hash_code());
        if (pipelineIt == pipelines.end()) {
            pipelineIt = pipelines.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(typeid(T).hash_code()),
                std::forward_as_tuple(std::move(std::make_unique<T>(newEngine, newRenderPass)))
            ).first;
        }
        return *static_cast<T*>(pipelineIt->second.get());
    }

    void clear() {
        pipelines.clear();
    }

private:
    std::unordered_map<std::size_t, std::unique_ptr<IGraphicsPipeline>> pipelines;
};