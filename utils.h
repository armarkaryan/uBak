/**
 * @file		utils.h
 * @brief		Module of definitions and additional special functions (header file).
 * @details		Contains type definitions, structures and additional special functionality.
 * @author		Arthur Markaryan
 * @date		01.05.2026
 * @version		1.0
 * @license		LGPL v3.0
 * @copyright	Copyright (c) 2026
 *
 * @par ChangeLog:
 * 01.05.2026	v1.0	Base creation
 *
 * @see			UTILS_debug()
 * @see			UTILS_getSystemTimeMicroseconds()
 * @see			UTILS_getSystemTimeMicrosecondsSafe()
 */

#ifndef _UTILS_H_
#define _UTILS_H_

#include <QString>
#include <QDebug>
#include <QFileInfo>
#include <cstdint>
#include <mutex>

// Fixed version of macro with multi-arg
#define UTILS_debug() qDebug().noquote() \
<< QStringLiteral("[%1] %2:%3 - %4") \
        .arg(QTime::currentTime().toString("hh:mm:ss.zzz"), \
             QFileInfo(__FILE__).fileName(), \
             QString::number(__LINE__), \
             QString::fromUtf8(__PRETTY_FUNCTION__))

/**
 * @brief		Gets monotonic system time in microseconds
 * @return		Time in microseconds (uint64_t)
 * @note		Fully thread-safe on all architectures
 * @note		Returns time from an arbitrary point (steady_clock)
 */
static inline uint64_t UTILS_getSystemTimeMicroseconds()
{
    // Use thread-local storage for maximum performance and to avoid locks
    static thread_local uint64_t lastTime = 0;

    auto now = std::chrono::steady_clock::now();
    auto duration = now.time_since_epoch();
    uint64_t current = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

    // Check for time jumps within a single thread
    if (current < lastTime) {
        // Time went backwards in this thread, return the last valid value
        return lastTime;
    }

    lastTime = current;
    return current;
}

/**
 * @brief		Gets monotonic system time in microseconds with protection against jumps between threads
 * @return		Time in microseconds (uint64_t)
 * @note		Slower, but protects against cross-thread time jumps
 */
static inline uint64_t UTILS_getSystemTimeMicrosecondsSafe()
{
    static std::mutex timeMutex;
    static uint64_t lastTime = 0;

    auto now = std::chrono::steady_clock::now();
    auto duration = now.time_since_epoch();
    uint64_t current = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

    std::lock_guard<std::mutex> lock(timeMutex);
    if (current < lastTime) {
        return lastTime;
    }
    lastTime = current;
    return current;
}

#endif // _UTILS_H_
