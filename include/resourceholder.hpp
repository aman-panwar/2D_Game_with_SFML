#ifndef RESOURCE_HOLDER_H
#define RESOURCE_HOLDER_H
#include <map>
#include <memory>
#include <string>
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <assert.h>

#include "defines.h"

/** @brief Encapsulates and Holds the Resources 
 *
 * Stores the resource into ResourceMap with ResourceID as the key
 * @note typedefs are available for all valid use case of ResourceHolder
 */
template <typename ResourceType, typename ResourceID>
class ResourceHolder
{
public:
    /** Loads the resource into ResourceMap
     * @param id is the key value
     * @param fileLocation is the location of the asset
     */
    void load(const ResourceID, const std::string);

    /** Return the resource
     * @param id is the key value of the resource to be returned
     */
    ResourceType &get(ResourceID);

private:
    ///holds the key and resource
    std::map<ResourceID, std::unique_ptr<ResourceType>> ResourceMap;
};

//Usefull typedef

typedef ResourceHolder<sf::Image, ImageID> ImageHolder;
typedef ResourceHolder<sf::Texture, TextureID> TextureHolder;
typedef ResourceHolder<sf::Font, FontID> FontHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundID> SoundHolder;
typedef ResourceHolder<sf::Music, MusicID> MusicHolder;

#include "resourceholder.inl"

#endif