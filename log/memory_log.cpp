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
 * Simple memory-based log.
 */

#include <tide/log/memory_log.h>

#include <boost/shared_array.hpp>
#include <cstring>

using namespace tide;


MemoryLogEntryIndex::MemoryLogEntryIndex(ChannelID channel,
        uint64_t timestamp, unsigned int offset,
        MemoryLog const* const source)
    : EntryIndexBase(channel, timestamp), offset_(offset), source_(source)
{
}


MemoryLogEntryIndex::MemoryLogEntryIndex(MemoryLogEntryIndex const& rhs)
    : EntryIndexBase(rhs), offset_(rhs.offset_), source_(rhs.source_)
{
}


SerialisedEntry const MemoryLogEntryIndex::data() const
{
    // operator[] is not const for maps so can't use it in a const method
    std::map<ChannelID, std::vector<SerialisedEntry> >::const_iterator ii =
        source_->data_.find(chan_);
    return ii->second[offset_];
}


MemoryLog::MemoryLog()
{
}


MemoryLog::MemoryLog(MemoryLog const& rhs)
    : channels_(rhs.channels_), next_id_(rhs.next_id_), data_(rhs.data_),
    indices_(rhs.indices_), start_time_(rhs.start_time_),
    end_time_(rhs.end_time_)
{
}


MemoryLog::~MemoryLog()
{
}


ChannelIDMap MemoryLog::channels() const
{
    // Need to reverse the 
}


ChannelNameMap MemoryLog::channels_by_name() const
{
    std::map<std::string const, ChannelInfo> result;
    for (ChannelIDMap::const_iterator ii(channels_.begin());
                ii != channels_.end(); ++ii)
    {
        result[ii->second.name()] = ii->second;
    }
    return result;
}


Index MemoryLog::get_full_index() const
{
    Index result;
    // Interleave the channel indices in time
    for (std::map<ChannelID, Index>::const_iterator ii(indices_.begin());
            ii != indices_.end(); ++ii)
    {
        result.insert(result.end(), ii->second.begin(), ii->second.end());
    }
    std::sort(result.begin(), result.end(), IndexComp());
}


void MemoryLog::add_entry(ChannelInfo const& channel, uint64_t timestamp,
        uint8_t const* const data, size_t size)
{
    // Remember that channel equivalence in TIDE is defined as having the same
    // name. It is the responsibility of views to ensure they are providing
    // accurate channel information.
    ChannelID id;
    ChannelIDMap::const_iterator ii(channels_.begin());
    for(; ii != channels_.end(); ++ii)
    {
        if (ii->second.name() == channel.name())
            break;
    }
    if (ii == channels_.end())
    {
        // New channel
        id = allocate_channel(channel);
    }
    else
    {
        // Existing channel
        id = ii->first;
    }
    add_entry(id, timestamp, data, size);
}


void MemoryLog::add_entry(ChannelID channel, uint64_t timestamp,
        uint8_t const* const data, size_t size)
{
    // Copy the data
    boost::shared_array<uint8_t> data_ptr(new uint8_t[size]);
    memcpy(data_ptr.get(), data, size);
    boost::shared_ptr<MemoryLogEntryIndex> index_ptr(
            new MemoryLogEntryIndex(channel, timestamp, data_.size(), this));
    indices_[channel].push_back(index_ptr);
    data_[channel].push_back(SerialisedEntry(data_ptr, timestamp));

    if (timestamp < start_time_)
    {
        start_time_ = timestamp;
    }
    else if (timestamp > end_time_)
    {
        end_time_ = timestamp;
    }
}


ChannelID MemoryLog::allocate_channel(ChannelInfo const& channel)
{
    ChannelID new_id(next_id_++);
    channels_[new_id] = channel;
    return new_id;
}

