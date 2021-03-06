/*
 * Ultrasonic.h - Library for HC-SR04 Ultrasonic Sensing Module.
 *
 * With ideas from:
 *   Created by ITead studio. Alex, Apr 20, 2010.
 *   iteadstudio.com
 *
 * SVN Keywords
 * ----------------------------------
 * $Author$
 * $Date$
 * $Revision$
 * ----------------------------------
 *
 * Thank you to Rowan Simms for pointing out the change in header name with
 * Arduino version 1.0 and up.
 *
 */

#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <stddef.h>

#if defined(ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

// Undefine COMPILE_STD_DEV if you don't want Standard Deviation.
#define COMPILE_STD_DEV


typedef struct bufferCtl
    {
    float *pBegin;
    float *pIndex;
    size_t length;
    bool filled;
    } BufCtl;

class Ultrasonic
    {
    public:
    Ultrasonic(int tp, int ep);
    long timing(void);
    float convert(long microsec, int metric);
    void setMultiplier(float value);
    void setTemperature(float value);
    void setMaxDistance(int value);
    static const int IN = 0;
    static const int CM = 1;
    static const float MULTIPLIER_DEFAULT = 1.0;
    // Hard-coded maximum distance in CM (manual for HC-SR04 says 500cm).
    static const int _MAX_CM_DISTANCE = 500;
    // Set the default temperature to 20C/68F
    static const float _TEMP_CELSIUS_DEFAULT = 20.0;
    /* ***** FIX THIS *****
     * Why 68 and not _divisor*2? There seems to be some processing overhead
     * so a little extra is needed. 68 tests out to be correct at most
     * distances.
     */
    static const int _PING_OVERHEAD = 68;

#ifdef COMPILE_STD_DEV
    bool sampleCreate(size_t size, ...);
    void sampleClear();
    float unbiasedStdDev(float value, size_t bufNum);
#endif // COMPILE_STD_DEV

    private:
    int _trigPin;
    int _echoPin;
    unsigned int _pingTimeout;
    float _maxDistance;
    float _multiplier;
    float _temp;

#ifdef COMPILE_STD_DEV
    size_t _numBufs;
    BufCtl *_pBuffers;
    void _sampleUpdate(BufCtl *buf, float msec);
    void _freeBuffers();
#endif // COMPILE_STD_DEV
    };

#endif // ULTRASONIC_H
