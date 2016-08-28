/**
 * @cond ___LICENSE___
 *
 * Copyright (c) 2016 Koen Visscher, Paul Visscher and individual contributors.
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

#include "manager/factoryManager.h"

#include "engineTest.h"

namespace
{
    ENGINE_TEST( FactoryManager, Sanity )
    {
        FactoryManager m;
    }

    ENGINE_TEST( FactoryManager, AddFactory )
    {
        FactoryManager m;
        auto fac = m.AddFactory< U32 >();

        EXPECT_TRUE( m.HasFactory< U32 >() );
        EXPECT_EQ( fac, m.GetFactory< U32 >() );
    }

    ENGINE_TEST( FactoryManager, AddFactoryInst )
    {
        FactoryManager m;
        auto instantiator = new Instantiator< U32 >();
        EXPECT_TRUE( m.AddFactory< U32 >( instantiator ) );

        EXPECT_TRUE( m.HasFactory< U32 >() );
        EXPECT_EQ( instantiator, m.GetFactory< U32 >() );
    }

    ENGINE_TEST( FactoryManager, AddFactoryInstTwice )
    {
        FactoryManager m;
        auto instantiator = new Instantiator< U32 >();
        EXPECT_TRUE( m.AddFactory< U32 >( instantiator ) );
        EXPECT_ANY_THROW( m.AddFactory< U32 >( instantiator ) );
    }

    ENGINE_TEST( FactoryManager, CreateInstance )
    {
        FactoryManager m;
        auto fac = m.AddFactory< U32 >();

        EXPECT_TRUE( m.HasFactory< U32 >() );
        EXPECT_EQ( fac, m.GetFactory< U32 >() );
        delete m.CreateInstance< U32 >();
    }

    ENGINE_TEST( FactoryManager, AddFactoryTwice )
    {
        FactoryManager m;
        auto fac = m.AddFactory< U32 >();
        EXPECT_EQ( fac, m.GetFactory< U32 >() );
        EXPECT_ANY_THROW( m.AddFactory< U32 >() );
    }

    ENGINE_TEST( FactoryManager, ReleaseFactory )
    {
        FactoryManager m;
        auto fac = m.AddFactory< U32 >();

        EXPECT_TRUE( m.HasFactory< U32 >() );
        EXPECT_EQ( fac, m.GetFactory< U32 >() );

        m.ReleaseFactory< U32 >();

        EXPECT_FALSE( m.HasFactory< U32 >() );
        EXPECT_EQ( nullptr, m.GetFactory< U32 >() );
    }

}