#pragma once

#include <chrono>

class Timer
{
public:
	Timer();

	/// <summary>
	/// Get the global timer instance.
	/// </summary>
	/// <returns></returns>
	static Timer& Get();

	/// <summary>
	/// Tick once per frame (done by the game class).
	/// </summary>
	void Tick();

	/// <summary>
	/// Reset timer.
	/// </summary>
	void Reset();

	double ElapsedMilliSeconds() const;
	double ElapsedSeconds() const;

	double TotalTimeSeconds() const;
	double TotalTimeMilliseconds() const;

private:
	std::chrono::high_resolution_clock::time_point t0, t1;
	double elapsedTime;
	double totalTime;
};

