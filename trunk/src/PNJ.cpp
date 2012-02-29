#include "PNJ.hpp"

b2Body * PhysicalObject::getBody(){
	return m_body;
}

void PhysicalObject::setBody(b2Body * body){
	m_body = body;
}

Sprite * PhysicalObject::getSprite(){
	return m_sprite;
}