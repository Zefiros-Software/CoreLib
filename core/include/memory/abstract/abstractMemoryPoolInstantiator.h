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
#ifndef __ENGINE_ABSTRACTMEMORYPOOLINSTANTIATOR_H__
#define __ENGINE_ABSTRACTMEMORYPOOLINSTANTIATOR_H__

#include "memory/abstract/abstractTInstantiator.h"

/// @addtogroup Instantiators
/// @{

/**
 * Abstract memory pooled instantiator, provides an interface from which every memory pooled
 * instantiator should derive.
 *
 * @sa  AbstractTInstantiator<Base>
 *
 * @tparam   tBase    The base class the instantiator creates objects for.
 */

template< typename tBase >
class AbstractMemoryPoolInstantiator
    : public AbstractTInstantiator< tBase >
{
public:

    /// @name Freeing Memory
    /// @{

    /**
     * Destroys the object created by this instantiator.
     *
     * @note This will be called when the pool decides this
     *       object should be destroyed and not pooled.
     *
     * @param [in,out]  object  If non-null, the object.
     */

    virtual void Destroy(tBase *object) = 0;

    /// @}
};

/// @}

#endif