#include "game.h"

#include <cassert>

#include "surface.h"
#include "template.h"
#include "Color.h"
#include <cstdio> //printf

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
	}

	static Sprite rotatingGun(new Surface("assets/aagun.tga"), 36);
	static int frame = 0;

	// Source: https://stackoverflow.com/a/22681410
	Pixel spectral_color(double l) // RGB <Pixel> <- lambda l <400,700> [nm]
	{
		double t;  
		double r = 0.0, g = 0.0, b = 0.0;
		if ((l >= 400.0) && (l < 410.0)) { t = (l - 400.0) / (410.0 - 400.0); r = +(0.33 * t) - (0.20 * t * t); }
		else if ((l >= 410.0) && (l < 475.0)) { t = (l - 410.0) / (475.0 - 410.0); r = 0.14 - (0.13 * t * t); }
		else if ((l >= 545.0) && (l < 595.0)) { t = (l - 545.0) / (595.0 - 545.0); r = +(1.98 * t) - (t * t); }
		else if ((l >= 595.0) && (l < 650.0)) { t = (l - 595.0) / (650.0 - 595.0); r = 0.98 + (0.06 * t) - (0.40 * t * t); }
		else if ((l >= 650.0) && (l < 700.0)) { t = (l - 650.0) / (700.0 - 650.0); r = 0.65 - (0.84 * t) + (0.20 * t * t); }
		if ((l >= 415.0) && (l < 475.0)) { t = (l - 415.0) / (475.0 - 415.0); g = +(0.80 * t * t); }
		else if ((l >= 475.0) && (l < 590.0)) { t = (l - 475.0) / (590.0 - 475.0); g = 0.8 + (0.76 * t) - (0.80 * t * t); }
		else if ((l >= 585.0) && (l < 639.0)) { t = (l - 585.0) / (639.0 - 585.0); g = 0.84 - (0.84 * t); }
		if ((l >= 400.0) && (l < 475.0)) { t = (l - 400.0) / (475.0 - 400.0); b = +(2.20 * t) - (1.50 * t * t); }
		else if ((l >= 475.0) && (l < 560.0)) { t = (l - 475.0) / (560.0 - 475.0); b = 0.7 - (t)+(0.30 * t * t); }

		// Gamma correction
		//r = pow(r, 1.0 / 2.2);
		//g = pow(g, 1.0 / 2.2);
		//b = pow(b, 1.0 / 2.2);

		// Now convert to pixel.
		return static_cast<Pixel>(r * 255.0) << 16 | static_cast<Pixel>(g * 255.0) << 8 | static_cast<Pixel>(b * 255.0);
	}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		// clear the graphics window
		screen->Clear(0);

		constexpr double minWavelength = 400.0;
		constexpr double maxWaveLength = 700.0;

		const double step = (maxWaveLength - minWavelength) / ScreenWidth;
		int x = 0;
		float l = minWavelength;
		while (l <= maxWaveLength && x < ScreenWidth)
		{
			Pixel c = spectral_color(l);
			screen->Line(x, 0, x, ScreenHeight - 1, c);
			l += step;
			x += 1;
		}
	}
};