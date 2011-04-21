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
        std::string source,
        boost::shared_array<uint8_t> const raw_source, size_t raw_src_size,
        boost::shared_array<uint8_t> const format, size_t format_size)
    : name_(name), source_type_(source_type), source_(source), raw_source_(0),
    raw_source_size_(raw_src_size), format_(0), format_size_(format_size)
{
    raw_source_ = boost::shared_array<uint8_t>(new uint8_t[raw_source_size_]);
    memcpy(raw_source_.get(), raw_source.get(), raw_source_size_);
    format_ = boost::shared_array<uint8_t>(new uint8_t[format_size_]);
    memcpy(format_.get(), format.get(), format_size_);
}


ChannelInfo::ChannelInfo(ChannelInfo const& rhs)
    : name_(rhs.name_), source_type_(rhs.source_type_), source_(rhs.source_),
    raw_source_(0), raw_source_size_(rhs.raw_source_size_), format_(0),
    format_size_(rhs.format_size_)
{
    raw_source_ = boost::shared_array<uint8_t>(new uint8_t[raw_source_size_]);
    memcpy(raw_source_.get(), rhs.raw_source_.get(), raw_source_size_);
    format_ = boost::shared_array<uint8_t>(new uint8_t[format_size_]);
    memcpy(format_.get(), rhs.format_.get(), format_size_);
}


ChannelInfo::~ChannelInfo()
{
}


void ChannelInfo::raw_source(boost::shared_array<uint8_t> const raw_source,
        size_t size)
{
    raw_source_size_ = size;
    raw_source_ = boost::shared_array<uint8_t>(new uint8_t[raw_source_size_]);
    memcpy(raw_source_.get(), raw_source.get(), size);
}


void ChannelInfo::format(boost::shared_array<uint8_t> const format, size_t size)
{
    format_size_ = size;
    format_ = boost::shared_array<uint8_t>(new uint8_t[format_size_]);
    memcpy(format_.get(), format.get(), size);
}


bool ChannelInfo::operator==(ChannelInfo const& rhs)
{
    return name_ == rhs.name_;
}


bool ChannelInfo::operator!=(ChannelInfo const& rhs)
{
    return !(*this == rhs);
}


std::ostream& tide::operator<<(std::ostream& o, ChannelInfo const& ci)
{
    return o << ci.name_ << ':' << ci.source_type_ << ':' << ci.source_;
}

