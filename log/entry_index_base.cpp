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
 * Base class for log entry indices.
 */

#include <tide/log/entry_index_base.h>

using namespace tide;


SerialisedEntry::SerialisedEntry(boost::shared_ptr<uint8_t> data, size_t size)
    : data_(data), size_(size)
{
}


SerialisedEntry::SerialisedEntry(SerialisedEntry const& rhs)
    : data_(rhs.data_), size_(rhs.size_)
{
}


EntryIndexBase::EntryIndexBase(ChannelID channel, uint64_t timestamp)
    : chan_(channel), ts_(timestamp)
{
}


EntryIndexBase::EntryIndexBase(EntryIndexBase const& rhs)
    : chan_(rhs.chan_), ts_(rhs.ts_)
{
}


EntryIndexBase::~EntryIndexBase()
{
}

