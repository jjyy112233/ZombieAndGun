#include "TextObj.h"

TextObj::TextObj()
{
}

TextObj::~TextObj()
{
}

void TextObj::Init()
{
	Object::Init();
}

void TextObj::Update(float dt)
{
}

void TextObj::Draw(RenderWindow& window)
{
	window.draw(text);
}

void TextObj::SetFont(Font& font)
{
	text.setFont(font);
}

void TextObj::SetText(string str)
{
	text.setString(str);
}

const string& TextObj::GetText() const
{
	return text.getString();
}
