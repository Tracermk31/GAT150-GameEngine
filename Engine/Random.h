#pragma once

#include <cstdlib>

namespace ChiefEngine {
	inline int RandomInt() {
		return rand();
	}

	/// <summary>
	/// Get random integer value [0, max)
	/// </summary>
	/// <param name="max">exclusive max</param>
	/// <returns> Random integer between 0 and max (exclusive)</returns>
	inline int RandomInt(int max) {
		return RandomInt() % max;
	}

	/// <summary>
	/// Get random integer value [min, max)
	/// </summary>
	/// <param name="min">inclusive min</param>
	/// <param name="max">exclusive max</param>
	/// <returns> Random integer between min (inclusive) and max (exclusive)</returns>
	inline int RandomInt(int min, int max) {
		return min + RandomInt(max - min);
	}

	/// <summary>
	/// Get random number [0, 1]
	/// </summary>
	/// <returns> A number between 0 - 1</returns>
	inline float RandomFloat() {
		return RandomInt() / (float)RAND_MAX;
	}


	/// <summary>
	/// Get random number [0, max]
	/// </summary>
	/// <param name="max"> Inclusive maximum possible value</param>
	/// <returns> Random number between 0 and max (inclusive)</returns>
	inline float RandomFloat(float max) {
		return RandomFloat() * max;
	}

	/// <summary>
	/// Get random number [min, max]
	/// </summary>
	/// <param name="min"> Inclusive minimum possible value</param>
	/// <param name="max"> Inclusive maximum possible value</param>
	/// <returns> Random number between min (inclusive) and max (inclusive) </returns>
	inline float RandomFloat(float min, float max) {
		return min + RandomFloat(max - min);
	}
}