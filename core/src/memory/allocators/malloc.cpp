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

#include "memory/allocators/malloc.h"

#include <stdlib.h>
#include <emmintrin.h>

void *_InternalAlignedMalloc(size_t bytes, size_t alignment)
{
    /*
    size_t offset = alignment; //+ sizeof( size_t );

    void *ptr = malloc( bytes + offset );

    if ( !ptr )
    {
        return nullptr;
    }

    //offset and truncate under alignment
    void **ptr2 = reinterpret_cast< void ** >( ( reinterpret_cast< size_t >( ptr ) & ~( alignment - 1 ) ) + offset );

    //store malloc address above the requested memory
    ptr2[-1] = ptr;

    return ptr2;
    */

    // Just use the sse alloc
    return _mm_malloc(bytes, alignment);
}

void _InternalAlignedFree(void *ptr)
{
    /*
    if ( ptr != nullptr )
    {
        free( *( static_cast< void ** >( ptr ) - 1 ) );
    }
    */

    _mm_free(ptr);
}

void *ZefAlignedMalloc(size_t bytes, size_t alignment)
{
    // TODO add lib specific allocs
    return _InternalAlignedMalloc(bytes, alignment);
}

void ZefAlignedFree(void *ptr)
{
    // TODO add lib specific frees
    return _InternalAlignedFree(ptr);
}