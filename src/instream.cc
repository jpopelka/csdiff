/*
 * Copyright (C) 2011 Red Hat, Inc.
 *
 * This file is part of csdiff.
 *
 * csdiff is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * csdiff is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with csdiff.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "instream.hh"

InStream::InStream(const std::string &fileName, const bool silent):
    fileName_(fileName),
    silent_(silent),
    anyError_(false),
    str_((!fileName_.compare("-"))
                ? std::cin
                : fileStr_)
{
    if (&str_ == &fileStr_)
        fileStr_.open(fileName_, std::ios::in);

    if (!fileStr_)
        throw InFileException(fileName_);
}

InStream::InStream(std::istringstream &str, const bool silent):
    silent_(silent),
    anyError_(false),
    str_(str)
{
}

InStream::~InStream()
{
    if (&str_ == &fileStr_)
        fileStr_.close();
}

void InStream::handleError(const std::string msg, const long line)
{
    anyError_ = true;
    if (silent_ || msg.empty())
        return;

    std::cerr << fileName_;

    if (line)
        // line number available
        std::cerr << ":" << line;

    std::cerr << ": error: " << msg << "\n";
}