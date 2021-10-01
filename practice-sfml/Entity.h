#pragma once
#include"SFML/Graphics.hpp"
class Entity: public sf::Drawable, public sf::Transformable
{
public:
    bool mMovable;
    int mPos;

public:

    bool load(const std::string& tileset, sf::Vector2f,int);
private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &mTexture;

        // draw the vertex array
        target.draw(mVertices, states);
    }

    sf::VertexArray mVertices;
    sf::Texture mTexture;
    
};