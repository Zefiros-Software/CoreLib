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

#include "common/file.h"
#include <iostream>

namespace Directory
{

    bool Exists(const std::string &directory) noexcept
    {
        return boost::filesystem::exists(directory) && boost::filesystem::is_directory(directory);
    }

    bool IsEmpty(const std::string &directory, bool includeDirectories /*= true */) noexcept
    {
        if (includeDirectories)
        {
            return Path::List(directory, false).empty();
        }

        return File::List(directory, false).empty();
    }

    std::vector< std::string > List(const std::string &directory, bool recursive /*= false */) noexcept
    {
        const std::vector< boost::filesystem::path > contents = Path::List(directory, recursive);
        std::vector< std::string > directories;

        for (const boost::filesystem::path &fsPath : contents)
        {
            if (boost::filesystem::is_directory(fsPath))
            {
                directories.push_back(Path::FixStyle(fsPath.generic_string()));
            }
        }

        return directories;
    }

    bool Delete(const std::string &directory) noexcept
    {
        if (Exists(directory))
        {
            try
            {
                boost::filesystem::remove(directory);

                return true;
            }
            catch (const boost::filesystem::filesystem_error &)
            {
                // We tried to delete a non empty folder, which is not allowed with this function
            }
        }

        return false;
    }

    bool DeleteAll(const std::string &directory) noexcept
    {
        if (Exists(directory))
        {
            try
            {
                boost::filesystem::remove_all(directory);
                return true;
            }
            catch (boost::filesystem::filesystem_error &)
            {
                // also false
            }
        }

        return false;
    }

    bool Create(const std::string &directory) noexcept
    {
        try
        {
            return boost::filesystem::create_directory(directory);
        }
        catch (const std::exception &)
        {
            return false;
        }
    }

    bool CreateAll(const std::string &directories) noexcept
    {
        try
        {
            boost::filesystem::create_directories(directories);
        }
        catch (const boost::filesystem::filesystem_error &)
        {
            return false;
        }

        return Exists(directories);
    }

    bool Copy(const std::string &from, const std::string &to) noexcept
    {
        if (Exists(from) && !Exists(to))
        {
            // boost::filesystem::absolute( from ) != boost::filesystem::absolute( to ) && is only true if Exists( from ) && !Exists( to )
            if (!Path::IsParent(from, to))
            {
                boost::filesystem::copy_directory(from, to);

                return true;
            }
        }

        return false;
    }

    bool Move(const std::string &from, const std::string &to) noexcept
    {
        if (Exists(from) && !Exists(to))
        {
            // boost::filesystem::absolute( from ) != boost::filesystem::absolute( to ) && is only true if Exists( from ) && !Exists( to )
            if (!Path::IsParent(from, to))
            {
                boost::filesystem::rename(from, to);

                return true;
            }
        }

        return false;
    }

}
