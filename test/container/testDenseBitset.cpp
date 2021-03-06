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


#include "container/denseBitset.h"

#include "engineTest.h"

namespace
{
    TEST(DenseBitset, SanityCheck)
    {
        DenseBitset m;
    }

    TEST(DenseBitset, SanityCheck2)
    {
        DenseBitset m(2);
        EXPECT_FALSE(m[0]);
        EXPECT_FALSE(m[1]);
    }

    TEST(DenseBitset, Set)
    {
        DenseBitset m(2);
        m[0] = true;
        EXPECT_TRUE(m[0]);
    }

    TEST(DenseBitset, Set2)
    {
        DenseBitset m(2);
        DenseBitset::BitReference f = m[0];
        f = true;

        EXPECT_TRUE(f);
    }

    TEST(DenseBitset, Set3)
    {
        DenseBitset m(2);
        DenseBitset::BitReference f = m[0];
        f = true;
        f = false;

        EXPECT_FALSE(f);
    }

    TEST(DenseBitset, Resize)
    {
        DenseBitset m(0);
        m.Resize(2);
        DenseBitset::BitReference f(m[0]);
        f = true;

        EXPECT_TRUE(f);
    }

    TEST(DenseBitset, Reset)
    {
        DenseBitset m(0);
        m.Resize(2);
        DenseBitset::BitReference f = m[0];
        f = true;
        m.Reset();
        EXPECT_FALSE(f);
    }

}