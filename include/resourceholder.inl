#include "resourceholder.hpp"

template <typename ResourceType, typename ResourceID>
inline void ResourceHolder<ResourceType, ResourceID>::
    load(const ResourceID id, const std::string fileLocation)
{
    std::unique_ptr<ResourceType> resource(new ResourceType());
    if (!resource->loadFromFile(fileLocation))
    {
        throw std::runtime_error("failed to load resource: " + fileLocation + " :(");
    }
    auto inserted = ResourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}

template <typename ResourceType, typename ResourceID>
inline ResourceType &ResourceHolder<ResourceType, ResourceID>::
    get(ResourceID id)
{
    auto resource = ResourceMap.find(id);
    assert(resource != ResourceMap.end());
    return *resource->second;
}