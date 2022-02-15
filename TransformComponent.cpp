#include "TransformComponent.h"
#include "Timer.h"
#include "surface.h"
#include <string>

void TransformComponent::Update()
{
	int i = 3;
}

void TransformComponent::Render(Tmpl8::Surface& screen)
{
	const Timer& t = Timer::Get();

	static double fps = 0.0;
	static int numFrames = 0;
	static double totalTime = 0.0;

	totalTime += t.ElapsedSeconds();
	numFrames++;
	if (totalTime > 1.0)
	{
		fps = numFrames / totalTime;
		numFrames = 0;
		totalTime = 0.0;
	}
	auto s = std::string("FPS: ") + std::to_string(fps);

	screen.Print(s.c_str(), 10, 10, 0xffffffff);
}

