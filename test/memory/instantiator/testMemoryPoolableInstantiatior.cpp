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

#include "memory/instantiator/memoryPoolableInstantiator.h"


#include "engineTest.h"

namespace
{
    class Base
    {
    public:
        virtual ~Base()
        {
        }

        virtual void OnInit()
        {
        }

        virtual void OnRelease()
        {
        }

        virtual bool IsDerived()
        {
            return false;
        }
    };

    class Child
        : public Base
    {
    public:

        virtual bool IsDerived() override
        {
            return true;
        }
    };

    typedef MemoryPoolableInstantiator< Child, Base > MemoryPoolableInstantiatorImpl;

    TEST(MemoryPoolableInstantiator, SanityCheck)
    {
        volatile MemoryPoolableInstantiatorImpl inst;
    }

    TEST(MemoryPoolableInstantiator, Create)
    {
        MemoryPoolableInstantiatorImpl inst;

        Base *child = inst.Create();

        EXPECT_TRUE(child->IsDerived());

        inst.Destroy(child);
    }

    TEST(MemoryPoolableInstantiator, EmptyCreate)
    {
        MemoryPoolableInstantiatorImpl inst(0, 0);

        Base *child = inst.Create();

        EXPECT_TRUE(child->IsDerived());

        inst.Destroy(child);
    }

    TEST(MemoryPoolableInstantiator, NearEmptyCreate)
    {
        MemoryPoolableInstantiatorImpl inst(1, 1);

        Base *child = inst.Create();
        Base *child2 = inst.Create();

        EXPECT_TRUE(child->IsDerived());
        EXPECT_TRUE(child2->IsDerived());

        inst.Destroy(child);
        inst.Destroy(child2);
    }

    TEST(MemoryPoolableInstantiator, ContiguousMemoryCheck)
    {
        MemoryPoolableInstantiatorImpl inst(2, 1);

        Base *child = inst.Create();
        Base *child2 = inst.Create();

        EXPECT_TRUE(child->IsDerived());
        EXPECT_TRUE(child2->IsDerived());

        inst.Destroy(child);
        inst.Destroy(child2);

        EXPECT_EQ(1, Mathf::Abs(static_cast< S32 >(child2 - child)));
    }

    TEST(MemoryPoolableInstantiator, MultipleBlocks)
    {
        MemoryPoolableInstantiatorImpl inst(1, 2);

        Base *child = inst.Create();
        Base *child2 = inst.Create();

        EXPECT_TRUE(child->IsDerived());
        EXPECT_TRUE(child2->IsDerived());

        inst.Destroy(child);
        inst.Destroy(child2);
    }

    TEST(MemoryPoolableInstantiator, MemoryLeaks)
    {
        MemoryPoolableInstantiatorImpl inst(10, 10);
        std::vector< Base * > ptrs;

        for (U32 i = 0; i < 500; ++i)
        {
            ptrs.push_back(inst.Create());
        }

        for (Base *ptr : ptrs)
        {
            inst.Destroy(ptr);
        }
    }

    TEST(MemoryPoolableInstantiator, Copy)
    {
        MemoryPoolableInstantiatorImpl instantiator;
        delete instantiator.Copy();
    }
}