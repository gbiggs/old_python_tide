/* TIDE
 *
 * Copyright (C) 2011
 *     Geoffrey Biggs and contributors
 *     RT-Synthesis Research Group
 *     Intelligent Systems Research Institute,
 *     National Institute of Advanced Industrial Science and Technology (AIST),
 *     Japan
 *     All rights reserved.
 * Licensed under the Eclipse Public License -v 1.0 (EPL)
 * http://www.opensource.org/licenses/eclipse-1.0.txt
 *
 * Channel-related objects.
 */

#include <tide/common/channels.h>

#include <cstring>

using namespace tide;


ChannelInfo::ChannelInfo()
    : name_(""), source_type_(""), source_(""), raw_source_(0)
{
}


ChannelInfo::ChannelInfo(std::string name, std::string source_type,
        std::string source, unsigned char const* const raw_source,
        unsigned int size)
    : name_(name), source_type_(source_type), source_(source), raw_source_(0)
{
    raw_source_ = new unsigned char[size];
    memcpy(raw_source_, raw_source, size);
}


ChannelInfo::~ChannelInfo()
{
    if (raw_source_ != 0)
    {
        delete[] raw_source_;
    }
}


void ChannelInfo::raw_source(unsigned char const* const raw_source,
        unsigned int size)
{
    if (raw_source_ != 0)
    {
        delete[] raw_source;
    }
    raw_source_ = new unsigned char[size];
    memcpy(raw_source_, raw_source, size);
}

