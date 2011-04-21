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
 * Basic stream-based view.
 */

#if !defined(BASIC_STREAM_VIEW_H__)
#define BASIC_STREAM_VIEW_H__


#include <boost/shared_ptr.hpp>
#include <tide/views/view.h>
#include <tide/log/entry_index.h>
#include <tide/log/log.h>


namespace tide
{
    typedef Index::const_iterator StreamIterator;

    class BasicStreamView
        : public View
    {
        public:
            BasicStreamView(boost::shared_ptr<Log> const log);
            virtual ~BasicStreamView();

            virtual uint64_t start_time() const;
            virtual uint64_t end_time() const;
            virtual ChannelIDMap channels() const;
            virtual std::vector<ChannelInfo> channel_list() const;

            virtual StreamIterator begin() const;
            virtual StreamIterator end() const;
            virtual StreamIterator at(uint64_t timestamp) const;

        protected:
            boost::shared_ptr<Log> const log_;
            Index indices_;
    };
};

#endif // !defined(BASIC_STREAM_VIEW_H__)

