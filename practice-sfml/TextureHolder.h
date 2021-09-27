#pragma once
#include"SFML/Graphics.hpp"
#include"enums.h"
class TextureHolder
{
	public:
		void load(textureId,const std::string &);
		sf::Texture& get(textureId);
		const sf::Texture& get(textureId) const;
	private:
		std::map<textureId,
			std::unique_ptr<sf::Texture>> mTextureMap;

};

