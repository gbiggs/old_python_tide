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


#if !defined(MEMORY_LOG_H__)
#define MEMORY_LOG_H__


#include <map>
#include <stdint.h>
#include <tide/log/channels.h>
#include <tide/log/entry_index_base.h>
#include <tide/log/log_base.h>
#include <utility>
#include <vector>


namespace tide
{
    class MemoryLog;

    class MemoryLogEntryIndex
        : public EntryIndexBase
    {
        public:
            MemoryLogEntryIndex(ChannelID channel, uint64_t timestamp,
                    unsigned int offset, MemoryLog const* const source);
            MemoryLogEntryIndex(MemoryLogEntryIndex const& rhs);

            SerialisedEntry const data() const;

        private:
            unsigned int offset_;
            MemoryLog const* const source_;
    };


    class MemoryLog
        : public LogBase
    {
        friend class MemoryLogEntryIndex;

        public:
            MemoryLog();
            MemoryLog(MemoryLog const& rhs);
            virtual ~MemoryLog();

            virtual uint64_t start_time() const { return start_time_; };
            virtual uint64_t end_time() const { return end_time_; };
            virtual ChannelIDMap channels() const;
            virtual ChannelNameMap channels_by_name() const;

            virtual Index get_full_index() const;

            // Add an entry in a channel that is possibly unallocated
            virtual void add_entry(ChannelInfo const& channel,
                    uint64_t timestamp, uint8_t const* const data, size_t size);
            // Add an entry in a pre-allocated channel
            virtual void add_entry(ChannelID channel, uint64_t timestamp,
                    uint8_t const* const data, size_t size);
            // Pre-allocate a channel
            virtual ChannelID allocate_channel(ChannelInfo const& channel);

        protected:
            ChannelIDMap channels_;
            unsigned int next_id_;

            std::map<ChannelID, std::vector<SerialisedEntry> > data_;
            std::map<ChannelID, Index> indices_;
            uint64_t start_time_, end_time_;
    };
};

#endif // !defined(MEMORY_LOG_H__)

