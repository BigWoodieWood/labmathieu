/**
 * @file temps.cpp
 * @brief Implementation of class TTemps - Time management and performance measurements
 * @author elliot wood
 * @date 26 October 2025
 * @version 1.0
 *
 * This class implements tools to measure execution time,
 * obtain formatted current time and compute precise time intervals
 * in microseconds for performance analysis of real-time tasks.
 */

#include "temps.hpp"

TTemps::TTemps(void)
    {
    memset(&tDebut,0,sizeof(struct timeval));
    memset(&tFin,0,sizeof(struct timeval));
    memset(&temps,0,sizeof(time_t));
    }

char *TTemps::now(void)
    {
    time(&temps);
    localtime_r(&temps,&tmTemps);

    strftime(strTemps,sizeof strTemps,"%F %T",&tmTemps);

    return strTemps;
    }

void TTemps::startMesure(void)
    {
    gettimeofday(&tDebut,NULL);
    }

void TTemps::stopMesure(void)
    {
    gettimeofday(&tFin,NULL);
    }

double TTemps::mesure_us(void)
    {
    return (((tFin.tv_sec - tDebut.tv_sec) * 1000000) + (tFin.tv_usec - tDebut.tv_usec));
    }

