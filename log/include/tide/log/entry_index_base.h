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


#if !defined(ENTRY_INDEX_BASE_H__)
#define ENTRY_INDEX_BASE_H__


#include <boost/shared_ptr.hpp>
#include <stdint.h>
#include <tide/log/channels.h>


namespace tide
{
    class SerialisedEntry
    {
        public:
            SerialisedEntry(boost::shared_ptr<uint8_t> data, size_t size);
            SerialisedEntry(SerialisedEntry const& rhs);

            boost::shared_ptr<uint8_t> data() const { return data_; };
            size_t size() const { return size_; };

        private:
            boost::shared_ptr<uint8_t> data_;
            size_t size_;
    };


    class EntryIndexBase
    {
        public:
            EntryIndexBase(ChannelID channel, uint64_t timestamp);
            EntryIndexBase(EntryIndexBase const& rhs);
            virtual ~EntryIndexBase();

            virtual ChannelID channel() const { return chan_; };
            virtual uint64_t timestamp() const { return ts_; };

            virtual SerialisedEntry const data() const = 0;

        protected:
            ChannelID chan_;
            uint64_t ts_;
    };


    struct IndexComp
    {
        bool operator()(boost::shared_ptr<EntryIndexBase> const& l,
                boost::shared_ptr<EntryIndexBase> const& r)
        {
            return l->timestamp() < r->timestamp();
        }
    } IndexComp;
};

#endif // !defined(ENTRY_INDEX_BASE_H__)

