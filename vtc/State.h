#pragma once

class State
{
public:
	virtual ~State() {}

	virtual void Init() {}
	virtual void Close() {}

	virtual void Update(const float dt) {}
	virtual void Draw(const float dt) {}

	virtual void Pause() {}
	virtual void Resume() {}

	virtual void FocusLost() {}
	virtual void FocusGained() {}
};