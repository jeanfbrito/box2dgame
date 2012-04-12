#include "DebugDraw.h"

const sf::Color mcolor = sf::Color::Red;

DebugDraw::DebugDraw(sf::RenderWindow* target)
	: Target(target)
{
	SetFlags(e_shapeBit | e_jointBit | e_centerOfMassBit | e_aabbBit);
	//SetFlags(0xFFFF);
}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    sf::VertexArray points;
    points.setPrimitiveType(sf::LinesStrip);
    points.resize(vertexCount+1); //we need to connect the last line too

    for(int i = 0; i < vertexCount; i++)
    {
        b2Vec2 v = vertices[i];
        points[i] = sf::Vertex(sf::Vector2f(v.x*PPM, v.y*PPM), sf::Color::Red);
    }
    points[vertexCount] = sf::Vertex(sf::Vector2f(vertices[0].x*PPM, vertices[0].y*PPM), sf::Color::Red);

    Target->draw(points);
}
void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{

}
void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
;
}
void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{

}
void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{

}
void DebugDraw::DrawTransform(const b2Transform& xf)
{

}
void DebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
    //sf::CircleShape shape(1, 1);
    //shape.setPosition(p.x, p.y);
	//Target->draw(shape);
}
void DebugDraw::DrawAABB(b2AABB* aabb, const b2Color& color)
{
    sf::RectangleShape rect(sf::Vector2f((aabb->upperBound.x - aabb->lowerBound.x)*PPM, (aabb->lowerBound.y - aabb->upperBound.y)*PPM));
    rect.setOutlineColor(mcolor);
    rect.setOutlineThickness(3);
    rect.setFillColor(sf::Color::Transparent);
    rect.setPosition(aabb->lowerBound.x*PPM, aabb->upperBound.y*PPM);
    Target->draw(rect);
}
