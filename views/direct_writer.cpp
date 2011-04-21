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
 * Simple writer view.
 */

#include <tide/views/direct_writer.h>

using namespace tide;


DirectWriter::DirectWriter(boost::shared_ptr<Log> const log)
    : log_(log)
{
}


DirectWriter::~DirectWriter()
{
}


uint64_t DirectWriter::start_time() const
{
    return log_->start_time();
}


uint64_t DirectWriter::end_time() const
{
    return log_->end_time();
}


ChannelIDMap DirectWriter::channels() const
{
    return log_->channels();
}


ChannelID DirectWriter::add_channel(std::string name, std::string source_type,
        std::string source, boost::shared_array<uint8_t> const raw_source,
        size_t raw_source_size, boost::shared_array<uint8_t> const format,
        size_t format_size)
{
    ChannelInfo info(name, source_type, source, raw_source, raw_source_size,
            format, format_size);
    return log_->allocate_channel(info);
}


void DirectWriter::add_entry(ChannelID const& channel, uint64_t timestamp,
        uint8_t const* const data, size_t size)
{
    log_->add_entry(channel, timestamp, data, size);
}


void DirectWriter::add_entry(ChannelInfo const& channel, uint64_t timestamp,
        uint8_t const* const data, size_t size)
{
    log_->add_entry(channel, timestamp, data, size);
}

