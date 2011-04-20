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

#include <tide/log/channels.h>

#include <cstring>

using namespace tide;


ChannelInfo::ChannelInfo()
    : name_(""), source_type_(""), source_(""), raw_source_(0),
    raw_source_size_(0), format_(0), format_size_(0)
{
}


ChannelInfo::ChannelInfo(std::string name, std::string source_type,
        std::string source, uint8_t const* const raw_source, size_t
        raw_src_size, uint8_t const* const format, size_t format_size)
    : name_(name), source_type_(source_type), source_(source), raw_source_(0),
    raw_source_size_(raw_src_size), format_(0), format_size_(format_size)
{
    raw_source_ = new uint8_t[raw_source_size_];
    memcpy(raw_source_, raw_source, raw_source_size_);
    format_ = new uint8_t[format_size_];
    memcpy(format_, format, format_size_);
}


ChannelInfo::ChannelInfo(ChannelInfo const& rhs)
    : name_(rhs.name_), source_type_(rhs.source_type_), source_(rhs.source_),
    raw_source_(0), raw_source_size_(rhs.raw_source_size_), format_(0),
    format_size_(rhs.format_size_)
{
    raw_source_ = new uint8_t[raw_source_size_];
    memcpy(raw_source_, rhs.raw_source_, raw_source_size_);
    format_ = new uint8_t[format_size_];
    memcpy(format_, rhs.format_, format_size_);
}


ChannelInfo::~ChannelInfo()
{
    if (raw_source_ != 0)
    {
        delete[] raw_source_;
    }
    if (format_ != 0)
    {
        delete[] format_;
    }
}


void ChannelInfo::raw_source(unsigned char const* const raw_source, size_t size)
{
    if (raw_source_ != 0)
    {
        delete[] raw_source_;
    }
    raw_source_ = new unsigned char[size];
    memcpy(raw_source_, raw_source, size);
    raw_source_size_ = size;
}


void ChannelInfo::format(unsigned char const* const format, size_t size)
{
    if (format_ != 0)
    {
        delete[] format_;
    }
    format_ = new uint8_t[size];
    memcpy(format_, format, size);
    format_size_ = size;
}


bool ChannelInfo::operator==(ChannelInfo const& rhs)
{
    return name_ == rhs.name_;
}


bool ChannelInfo::operator!=(ChannelInfo const& rhs)
{
    return !(*this == rhs);
}

