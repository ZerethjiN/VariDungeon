#pragma once

#include <Zerengine.hpp>

class BuildVersion final: public IResource {
public:
    BuildVersion(const std::string& newVersion):
        version(newVersion) {
    }

public:
    const std::string version;
};