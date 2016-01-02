#ifndef _Layer_
#define _Layer_

#include <vector>
#include <string>

class Layer
{
public:
	virtual void render() = 0;
	virtual void update() = 0;

protected:
	virtual ~Layer() {}
};

#endif