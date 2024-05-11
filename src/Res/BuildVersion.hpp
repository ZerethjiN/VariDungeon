#pragma once

#include <Zerengine.hpp>

class BuildVersion {
public:
    BuildVersion(const std::string& newVersion):
        version(newVersion) {
    }

public:
    const std::string version;
};