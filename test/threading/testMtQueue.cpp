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

#include "threading/mtQueue.h"

#include "engineTest.h"


namespace
{
    TEST(MtQueue, SanityCheck)
    {
        MtQueue< U32 > a;
        EXPECT_EQ(0u, a.Size());
        EXPECT_TRUE(a.Empty());
    }

    TEST(MtQueue, Push)
    {
        MtQueue< U32 > a;
        a.Push(51);
        EXPECT_EQ(1u, a.Size());
        EXPECT_FALSE(a.Empty());
    }

    TEST(MtQueue, WaitAndPop)
    {
        MtQueue< U32 > a;
        a.Push(51);
        EXPECT_EQ(51u, a.WaitAndPop());
    }

    TEST(MtQueue, TryPop)
    {
        MtQueue< U32 > a;
        a.Push(51);
        U32 val;
        EXPECT_TRUE(a.TryPop(val));
        EXPECT_EQ(51u, val);
    }
}