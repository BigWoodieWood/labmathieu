/**
 * @file temps.hpp
 * @brief Declaration of class TTemps - Time management and performance measurements
 * @author elliot wood
 * @date 26 October 2025
 * @version 1.0
 *
 * This class provides tools to measure execution time
 * and obtain formatted current time for real-time tasks.
 */

#ifndef TEMPS_HPP
#define TEMPS_HPP

#include <time.h>
#include <sys/time.h>
#include <string.h>

#include <unistd.h>

class TTemps
    {
    private:
	char strTemps[50];
	time_t temps;
	struct tm tmTemps;

	struct timeval tDebut,tFin;

    public:
	TTemps(void);

	char *now(void);

	void startMesure(void);
	void stopMesure(void);
	double mesure_us(void);
    };

#endif // TEMPS_HPP
