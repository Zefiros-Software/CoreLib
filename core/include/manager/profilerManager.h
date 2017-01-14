/**
 * @cond ___LICENSE___
 *
 * Copyright (c) 2017 Koen Visscher, Paul Visscher and individual contributors.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @endcond
 */

#pragma once
#ifndef __ENGINE_PROFILERMANAGER_H__
#define __ENGINE_PROFILERMANAGER_H__

#include "manager/abstract/abstractManager.h"

#include <unordered_map>
#include <chrono>
#include <string>
#include <mutex>

/// @addtogroup Profiling
/// @{

class ProfilerManager
    : public AbstractManager
{
public:

    ProfilerManager();

    /// @name Events
    /// @{

    virtual void OnUpdate() override;

    /// @}

    void Start( const std::string &name );

    void Waypoint( const std::string &name, const std::string &comment );

    void End( const std::string &name );

private:

    std::unordered_map< std::string, std::chrono::time_point< std::chrono::high_resolution_clock > > mTimings;
    std::chrono::time_point< std::chrono::high_resolution_clock > mLastUpdate;
    std::mutex mMutex;

    /**
     * Starts memory leak detection.
     */

    static void StartMemoryLeakDetection();
};

/// @}

#endif