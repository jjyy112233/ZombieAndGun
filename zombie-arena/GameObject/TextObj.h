#pragma once
#include "Object.h"

class TextObj : public Object
{
protected:
	Text text;

public:
	TextObj();
	virtual ~TextObj();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	Text& GetSFMLText() { return text; }
	void SetFont(Font& font);
	void SetText(string text);
	const string& GetText() const;
};

