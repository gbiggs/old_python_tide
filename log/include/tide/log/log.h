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
 * Base class for log formats.
 */


#if !defined(LOG_BASE_H__)
#define LOG_BASE_H__


#include <boost/shared_ptr.hpp>
#include <map>
#include <stdint.h>
#include <tide/log/channels.h>
#include <vector>


namespace tide
{
    class EntryIndexBase;
    typedef std::vector<boost::shared_ptr<EntryIndexBase> > Index;
    typedef std::map<ChannelID const, ChannelInfo> ChannelIDMap;
    typedef std::map<std::string const, ChannelInfo> ChannelNameMap;

    class LogBase
    {
        public:
            LogBase() {};
            LogBase(LogBase const& rhs) {};
            virtual ~LogBase() {};

            virtual uint64_t start_time() const = 0;
            virtual uint64_t end_time() const = 0;
            virtual ChannelIDMap channels() const = 0;
            virtual ChannelNameMap channels_by_name() const = 0;

            // Still not sure where the separation needs to be between logs
            // and views as regards to data indices. It would be nice to
            // minimise views needing to build their own indices when created,
            // but at the same time we need to avoid making assumptions about
            // what views will do.
            virtual Index get_full_index() const;

            // Add an entry in a channel that is possibly unallocated
            virtual void add_entry(ChannelInfo const& channel,
                    uint64_t timestamp, uint8_t const* const data,
                    size_t size) = 0;
            // Add an entry in a pre-allocated channel
            virtual void add_entry(ChannelID channel, uint64_t timestamp,
                    uint8_t const* const data, size_t size) = 0;
            // Pre-allocate a channel
            virtual ChannelID allocate_channel(ChannelInfo const& channel) = 0;
    };
};

#endif // !defined(LOG_BASE_H__)

