/**
 * @cond ___LICENSE___
 *
 * Copyright (c) 2016-2018 Zefiros Software.
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
#ifndef __ENGINE_THREADPOOL_H__
#define __ENGINE_THREADPOOL_H__

#include "common/utilClasses.h"
#include "common/types.h"

#include <condition_variable>
#include <vector>
#include <thread>


class JobQueue;
class Worker;

class ThreadPool
    : public NonCopyable< ThreadPool >
{
    friend class Worker;

public:

    explicit ThreadPool(const U32 capacity = 16, const U32 startThreadID = 0) noexcept;
    ~ThreadPool() noexcept;

    void Init();

    bool IsRunning() const noexcept;

    void Run(JobQueue *jobs);

    void JoinAll();

private:

    std::vector< std::thread > mThreads;
    std::vector< Worker >  mWorkers;

    std::condition_variable mNotification;
    std::condition_variable mRespond;

    std::mutex mMutex;
    std::mutex mRespondMutex;

    JobQueue *mQueueHook;

    size_t mLastQueueSize;

    U32 mStartThreadID;
};

#endif