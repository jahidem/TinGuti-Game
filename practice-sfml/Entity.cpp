#include "Entity.h"

bool Entity::load(const std::string& filename, sf::Vector2f msize, int pos)
{
    mPos = pos; mMovable=false;
    // load the tileset texture
    if (!mTexture.loadFromFile(filename))
        return false;

    // resize the vertex array to fit the level size
    mVertices.setPrimitiveType(sf::Quads);
    mVertices.resize(4);
    // define its 4 corners
    mVertices[0].position = sf::Vector2f(0.f, 0.f);
    mVertices[1].position = sf::Vector2f(msize.x, 0.f);
    mVertices[2].position = sf::Vector2f(msize.x, msize.y);
    mVertices[3].position = sf::Vector2f(0.f, msize.y);

       // define its 4 texture coordinates
    mVertices[0].texCoords = sf::Vector2f(0.f, 0.f);
    mVertices[1].texCoords = sf::Vector2f(msize.x, 0.f);
    mVertices[2].texCoords = sf::Vector2f(msize.x, msize.y);
    mVertices[3].texCoords = sf::Vector2f(0.f, msize.y);
    
    return true;
}