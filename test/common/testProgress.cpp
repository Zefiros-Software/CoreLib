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


#include "common/progress.h"

#include "engineTest.h"

#include <thread>

namespace
{
    TEST(Progress, InitializerList)
    {
        for (auto i : Progress({ 1, 2, 3, 4 }))
        {
            (void)i;
            //std::cout << i;
            //std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
        }
    }

    TEST(Progress, Vector)
    {
        for (volatile size_t j = 0; j < 100; ++j)
        {
            std::vector< U32 > vec = { 1, 2, 3, 4 };

            for (auto i : Progress(vec))
            {
                (void)i;
                //std::cout << i;
                //std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
            }
        }
    }

    TEST(Progress, Nested)
    {
        for (auto j : Progress(10))
        {
            for (auto i : Progress(5))
            {
                for (auto k : Progress(3))
                {
                    (void)i, (void)j, (void)k;
                    //std::cout << i;
                    //std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }
            }
        }
    }
}
