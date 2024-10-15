#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <limits>

///////////////////////////////////////////////////////////////////////////////////

[[maybe_unused]] [[nodiscard]] static glm::vec2 collisionResolution(const glm::vec2 posA, const glm::vec4& colA, const glm::vec2& scaleA, const glm::vec2 posB, const glm::vec4& colB, const glm::vec2& scaleB) noexcept {
    glm::vec2 posMinA = posA + (glm::vec2(colA.x, colA.y) * scaleA);
    glm::vec2 posMaxA = posA + ((glm::vec2(colA.x, colA.y) + glm::vec2(colA.z, colA.w)) * scaleA);
    glm::vec2 posMinB = posB + (glm::vec2(colB.x, colB.y) * scaleB);
    glm::vec2 posMaxB = posB + ((glm::vec2(colB.x, colB.y) + glm::vec2(colB.z, colB.w)) * scaleB);

    glm::vec4 dist(
        posMaxA.x - posMinB.x,
        posMaxA.y - posMinB.y,
        posMinA.x - posMaxB.x,
        posMinA.y - posMaxB.y
    );

    dist = glm::abs(dist);

    unsigned int distId = 0;

    if (dist.y < dist.x) {
        dist.x = dist.y;
        distId = 1;
    }

    if (dist.z < dist.x) {
        dist.x = dist.z;
        distId = 2;
    }

    if (dist.w < dist.x) {
        dist.x = dist.w;
        distId = 3;
    }

    switch (distId) {
        case 1: return glm::vec2(0.0f, -(posMaxA.y - posMinB.y));
        case 2: return glm::vec2(-(posMinA.x - posMaxB.x), 0.0f);
        case 3: return glm::vec2(0.0f, -(posMinA.y - posMaxB.y));
    }

    return glm::vec2(-(posMaxA.x - posMinB.x), 0.0f);
}

///////////////////////////////////////////////////////////////////////////////////

[[nodiscard]] static bool intersect(const glm::vec2& posA, const glm::vec4& colA, const glm::vec2& scaleA, const glm::vec2& posB, const glm::vec4& colB, const glm::vec2& scaleB) noexcept {
    return (posB.x + (colB.x * scaleB.x) < posA.x + ((colA.x + colA.z) * scaleA.x))
        && (posB.y + (colB.y * scaleB.y) < posA.y + ((colA.y + colA.w) * scaleA.y))
        && (posA.x + (colA.x * scaleA.x) < posB.x + ((colB.x + colB.z) * scaleB.x))
        && (posA.y + (colA.y * scaleA.y) < posB.y + ((colB.y + colB.w) * scaleB.y));
}

///////////////////////////////////////////////////////////////////////////////////

[[maybe_unused]] [[nodiscard]] static bool intersect(const glm::vec2& rectOrigin, const glm::vec4& rect, const glm::vec2& scaleRect, const glm::vec2& point) noexcept {
    return ((point.x) < (rectOrigin.x + rect.x + rect.z) * scaleRect.x)
        && ((point.y) < (rectOrigin.y + rect.y + rect.w) * scaleRect.y)
        && ((rectOrigin.x + rect.x) * scaleRect.x < (point.x))
        && ((rectOrigin.y + rect.y) * scaleRect.y < (point.y));
}

///////////////////////////////////////////////////////////////////////////////////

[[nodiscard]] std::array<glm::vec2, 4> applyTransformOnRect(const glm::vec4& rect, const glm::mat4& model) noexcept {
    return {
        glm::vec2(model * glm::vec4(rect.x, rect.y, 0, 1)),
        glm::vec2(model * glm::vec4(rect.x, rect.y + rect.w, 0, 1)),
        glm::vec2(model * glm::vec4(rect.x + rect.z, rect.y + rect.w, 0, 1)),
        glm::vec2(model * glm::vec4(rect.x + rect.z, rect.y, 0, 1))
    };
}

///////////////////////////////////////////////////////////////////////////////////

[[nodiscard]] static glm::vec2 rotateAround(const glm::vec2& oldPos, const glm::vec2& point, float angle) noexcept {
    glm::mat3 model(1.0f);
    model = glm::translate(model, point);
    model = glm::rotate(model, glm::radians(angle));
    model = glm::translate(model, oldPos);
    return {model[2][0], model[2][1]};
}

///////////////////////////////////////////////////////////////////////////////////

[[maybe_unused]] [[nodiscard]] static float lookRotation(const glm::vec2& direction) noexcept {
    return glm::degrees(glm::atan(direction.y, direction.x));
}

///////////////////////////////////////////////////////////////////////////////////

[[nodiscard]] float randomRangeFloat(float min, float max) noexcept {
    return min + static_cast <float> (rand()) / ( static_cast <float>(RAND_MAX) /(max - min));
}

[[nodiscard]] float randomRangeFloat(const glm::vec2& minMax) noexcept {
    return minMax[0] + static_cast <float> (rand()) / ( static_cast <float>(RAND_MAX) /(minMax[1] - minMax[0]));
}


///////////////////////////////////////////////////////////////////////////////////






///////////////////////////////////////////////////////////////////////////////////

[[nodiscard]] std::array<glm::vec2, 4> applyTransformOnCol(const glm::vec4& col, const glm::mat4& model) noexcept {
    return {
        glm::vec2(model * glm::vec4(col.x, col.y, 0, 1)),
        glm::vec2(model * glm::vec4(col.x, col.y + col.w, 0, 1)),
        glm::vec2(model * glm::vec4(col.x + col.z, col.y + col.w, 0, 1)),
        glm::vec2(model * glm::vec4(col.x + col.z, col.y, 0, 1))
    };
}

[[nodiscard]] std::array<glm::vec2, 4> getAxes(const std::array<glm::vec2, 4>& newVertices) noexcept {
    auto axe0 = newVertices[0] - newVertices[1];
    auto axe1 = newVertices[1] - newVertices[2];
    auto axe2 = newVertices[2] - newVertices[3];
    auto axe3 = newVertices[3] - newVertices[0];

    return {
        glm::normalize(glm::vec2(-axe0.y, axe0.x)),
        glm::normalize(glm::vec2(-axe1.y, axe1.x)),
        glm::normalize(glm::vec2(-axe2.y, axe2.x)),
        glm::normalize(glm::vec2(-axe3.y, axe3.x))
    };
}

[[nodiscard]] std::array<glm::vec2, 2> getAxes(const std::array<glm::vec2, 2>& newVertices) noexcept {
    auto axe0 = newVertices[0] - newVertices[1];

    return {
        glm::normalize(glm::vec2(-axe0.y, axe0.x))
    };
}

[[nodiscard]] glm::vec2 getProjection(const std::array<glm::vec2, 4>& newVertices, const glm::vec2& newAxis) noexcept {
    float min = glm::dot(newAxis, newVertices[0]);
    float max = min;
    for (std::size_t i = 1; i < newVertices.size(); i++) {
        float p = glm::dot(newAxis, newVertices[i]);
        if (p < min) {
            min = p;
        } else if (p > max) {
            max = p;
        }
    }
    return {min, max};
}

[[nodiscard]] glm::vec2 getProjection(const std::array<glm::vec2, 2>& newVertices, const glm::vec2& newAxis) noexcept {
    float min = glm::dot(newAxis, newVertices[0]);
    float max = min;
    for (std::size_t i = 1; i < newVertices.size(); i++) {
        float p = glm::dot(newAxis, newVertices[i]);
        if (p < min) {
            min = p;
        } else if (p > max) {
            max = p;
        }
    }
    return {min, max};
}

[[nodiscard]] bool isOverlap(const glm::vec2& lhs, const glm::vec2& rhs) noexcept {
    return rhs.x < lhs.y && lhs.x < rhs.y;
}

[[nodiscard]] bool isContains(const glm::vec2& lhs, const glm::vec2& rhs) noexcept {
    return lhs.x <= rhs.x && lhs.y >= rhs.y;
}

[[nodiscard]] float getOverlap(const glm::vec2& lhs, const glm::vec2& rhs) noexcept {
    if (lhs.y > rhs.x) {
        return glm::distance(lhs.y, rhs.x);
    } else if (lhs.x > rhs.y) {
        return glm::distance(lhs.x, rhs.y);
    }
    return 0;
}

[[nodiscard]] bool computeProjection(const std::array<glm::vec2, 4>& newVertices1, const std::array<glm::vec2, 4>& newVertices2) noexcept {
    for (const auto& axe: getAxes(newVertices1)) {
        auto projectionBox1 = getProjection(newVertices1, axe);
        auto projectionBox2 = getProjection(newVertices2, axe);

        if (!isOverlap(projectionBox1, projectionBox2)) {
            return false;
        }
    }

    return true;
}

// [[nodiscard]] bool computeProjectionWithRay(const std::array<glm::vec2, 2>& newRay, const std::array<glm::vec2, 4>& newVertices1) noexcept {
//     for (const auto& axe: getAxes(newRay)) {
//         auto projectionBox1 = getProjection(newRay, axe);
//         auto projectionBox2 = getProjection(newVertices1, axe);

//         if (!isOverlap(projectionBox1, projectionBox2)) {
//             return false;
//         }
//     }

//     return true;
// }

[[nodiscard]] bool computeProjectionWithRay(const std::array<glm::vec2, 4>& newVertices1, const std::array<glm::vec2, 2>& newRay) noexcept {
    for (const auto& axe: getAxes(newVertices1)) {
        auto projectionBox1 = getProjection(newVertices1, axe);
        auto projectionBox2 = getProjection(newRay, axe);

        if (!isOverlap(projectionBox1, projectionBox2)) {
            return false;
        }
    }

    return true;
}

[[nodiscard]] bool computeProjectionWithMTV(const std::array<glm::vec2, 4>& newVertices1, const std::array<glm::vec2, 4>& newVertices2, float& minOverlap, glm::vec2& smallestAxis, bool useOverlap) noexcept {
    for (const auto& axe: getAxes(newVertices1)) {
        auto projectionBox1 = getProjection(newVertices1, axe);
        auto projectionBox2 = getProjection(newVertices2, axe);

        if (!isOverlap(projectionBox1, projectionBox2)) {
            return false;
        } else if (useOverlap) {
            float o = getOverlap(projectionBox1, projectionBox2);
            if (isContains(projectionBox1, projectionBox2) || isContains(projectionBox2, projectionBox1)) {
                float mins = fabs(projectionBox1.x - projectionBox2.x);
                float maxs = fabs(projectionBox1.y - projectionBox2.y);

                if (mins < maxs) {
                    o += mins;
                } else {
                    o += maxs;
                }
            }
            if (o < minOverlap) {
                minOverlap = o;
                smallestAxis = axe;
            }
        }
    }

    return true;
}

[[nodiscard]] bool intersectOBB(const glm::vec4& col1, const glm::mat4& model1, const glm::vec4& col2, const glm::mat4& model2) noexcept {
    auto newVertices1 = applyTransformOnCol(col1, model1);
    auto newVertices2 = applyTransformOnCol(col2, model2);

    if (!computeProjection(newVertices1, newVertices2)) {
        return false;
    }

    if (!computeProjection(newVertices2, newVertices1)) {
        return false;
    }

    return true;
}

[[nodiscard]] bool intersectOBBWithRay(const glm::vec4& col1, const glm::mat4& model1, const glm::vec2& vecBegin, const glm::vec2& vecEnd) noexcept {
    auto newVertices1 = applyTransformOnCol(col1, model1);
    std::array<glm::vec2, 2> newVerticesRay = {vecBegin, vecEnd};

    if (!computeProjectionWithRay(newVertices1, newVerticesRay)) {
        return false;
    }

    // if (!computeProjectionWithRay(newVerticesRay, newVertices1)) {
    //     return false;
    // }

    return true;
}

[[nodiscard]] std::pair<bool, glm::vec2> intersectOBBWithMTV(const glm::vec4& dynCol, const glm::mat4& dynModel, const glm::vec4& staticCol, const glm::mat4& staticModel) noexcept {
    float minOverlap = std::numeric_limits<float>::max();
    glm::vec2 smallestAxis;

    auto newVertices1 = applyTransformOnCol(dynCol, dynModel);
    auto newVertices2 = applyTransformOnCol(staticCol, staticModel);

    if (!computeProjectionWithMTV(newVertices1, newVertices2, minOverlap, smallestAxis, false)) {
        return {false, glm::vec2()};
    }

    if (!computeProjectionWithMTV(newVertices2, newVertices1, minOverlap, smallestAxis, true)) {
        return {false, glm::vec2()};
    }

    return {true, smallestAxis * minOverlap};
}

///////////////////////////////////////////////////////////////////////////////////

glm::vec4 getGlobalBoundingBox(const glm::vec4& col, const glm::mat4& model) {
    glm::vec4 aabb {
        std::numeric_limits<float>::max(),
        std::numeric_limits<float>::max(),
        std::numeric_limits<float>::min(),
        std::numeric_limits<float>::min()
    };

    for (const auto& vertice: applyTransformOnCol(col, model)) {
        if (vertice.x < aabb.x) {
            aabb.x = vertice.x;
        }
        if (vertice.x > aabb.z) {
            aabb.z = vertice.x;
        }
        if (vertice.y < aabb.y) {
            aabb.y = vertice.y;
        }
        if (vertice.y > aabb.w) {
            aabb.w = vertice.y;
        }
    }

    return aabb;
}

///////////////////////////////////////////////////////////////////////////////////
