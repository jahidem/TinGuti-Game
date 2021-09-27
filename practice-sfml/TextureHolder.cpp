#include "TextureHolder.h"

void TextureHolder::load(textureId id, const std::string& filename)
{
	std::unique_ptr<sf::Texture> texture(new sf::Texture);
	if (!texture->loadFromFile(filename))
		throw std::runtime_error("TextHolder::load - Failed to load"
			+ filename);
	mTextureMap.insert(std::make_pair(id, move(texture)));

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