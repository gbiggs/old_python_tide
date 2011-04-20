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


#include <tide/views/view_base.h>
#include <tide/log/entry_index_base.h>
#include <tide/log/log_base.h>


namespace tide
{
    typedef std::vector<EntryIndexBase>::const_iterator StreamIterator;

    class BasicStreamView
        : public ViewBase
    {
        public:
            BasicStreamView(LogBase const& log);
            virtual ~BasicStreamView();

            virtual uint64_t start_time() const;
            virtual uint64_t end_time() const;
            virtual std::vector<ChannelInfo> channels() const;

            virtual StreamIterator begin() const;
            virtual StreamIterator end() const;
            virtual StreamIterator at(uint64_t timestamp) const;

        protected:
            LogBase const& log_;
            std::vector<EntryIndexBase> indices_;
    };
};

#endif // !defined(BASIC_STREAM_VIEW_H__)

