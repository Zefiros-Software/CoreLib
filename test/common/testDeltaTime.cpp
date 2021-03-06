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

#include "math/scalar/mathf.h"

#include "common/deltaTime.h"

#include "engineTest.h"

#include <thread>

namespace
{

    TEST(DeltaTime, GetDeltaTime, NoValue)
    {
        //! [Get]
        DeltaTime time;

        EXPECT_FLOAT_EQ(Mathf::GetEpsilon< F32 >(), time.GetDeltaTime());
        EXPECT_FLOAT_EQ(Mathf::GetEpsilon< F32 >(), time.GetEasedDeltaTime());
        //! [Get]
    }

    TEST(DeltaTime, GetElapsedMilliseconds, NoValue)
    {
        //! [GetMS]
        DeltaTime time;
        EXPECT_LE(Mathf::GetEpsilon< F32 >(), time.GetElapsedMilliseconds());
        //! [GetMS]
    }

    TEST(DeltaTime, Update, Value)
    {
        DeltaTime time;

        time.Update();

        EXPECT_LE(1e-9, time.GetDeltaTime());
        EXPECT_LE(1e-9, time.GetEasedDeltaTime());
    }

    TEST(DeltaTime, Update, ValueSleep)
    {
        //! [Update]
        DeltaTime time;

        std::this_thread::sleep_for(std::chrono::milliseconds(17));

        time.Update();

        // at least 16ms should have passed, sadly we don't know the right border of this interval
        // however, so we should check with >= comparison.
        EXPECT_LE(16 / 1000.0f, time.GetDeltaTime());
        EXPECT_LE(16 / 1000.0f, time.GetEasedDeltaTime());
        EXPECT_LE(Mathf::GetEpsilon< F32 >(), time.GetElapsedMilliseconds());
        //! [Update]
    }

    TEST(DeltaTime, Update, SleepUpdate)
    {
        DeltaTime time;

        std::this_thread::sleep_for(std::chrono::seconds(1));

        time.Update();

        EXPECT_LE(1, time.GetDeltaTime());
        EXPECT_LE(1, time.GetEasedDeltaTime());

        std::this_thread::sleep_for(std::chrono::milliseconds(17));

        EXPECT_LE(17, time.GetElapsedMilliseconds());
    }

    TEST(DeltaTime, GetElapsedMilliseconds, ValueSleep)
    {
        //! [UpdateMS]
        DeltaTime time;

        std::this_thread::sleep_for(std::chrono::milliseconds(16));

        time.Update();

        std::this_thread::sleep_for(std::chrono::milliseconds(32));

        EXPECT_LE(32, time.GetElapsedMilliseconds());
        //! [UpdateMS]
    }
}