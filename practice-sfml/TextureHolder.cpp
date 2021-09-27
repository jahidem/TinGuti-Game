#include "TextureHolder.h"

bool TextureHolder::load(textureId id,const std::string& filename)
{
	std::unique_ptr<sf::Texture> texture(new sf::Texture);
	bool isLoaded = texture->loadFromFile(filename);
	mTextureMap.insert(std::make_pair(id,move(texture)));
	return isLoaded;
}

sf::Texture& TextureHolder::get(textureId id)
{
	auto found = mTextureMap.find(id);
	return *found->second;
}

const sf::Texture& TextureHolder::get(textureId id) const
{
	auto found = mTextureMap.find(id);
	return *found->second;
}
