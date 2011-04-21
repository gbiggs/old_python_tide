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

#include <tide/views/basic_stream_view.h>

using namespace tide;


BasicStreamView::BasicStreamView(LogBase const& log)
    : log_(log), indices_(log.get_full_index())
{
}


BasicStreamView::~BasicStreamView()
{
}


uint64_t BasicStreamView::start_time() const
{
    return log_.start_time();
}


uint64_t BasicStreamView::end_time() const
{
    return log_.end_time();
}


std::vector<ChannelInfo> BasicStreamView::channels() const
{
    std::vector<ChannelInfo> result;
    for(ChannelIDMap::const_iterator ii(log_.channels().begin());
            ii != log_.channels().end(); ++ii)
    {
        result.push_back(ii->second);
    }
    return result;
}


StreamIterator BasicStreamView::begin() const
{
    return indices_.begin();
}


StreamIterator BasicStreamView::end() const
{
    return indices_.end();
}


StreamIterator BasicStreamView::at(uint64_t timestamp) const
{
    Index::const_iterator now(indices_.begin());
    // Increment to the first value beyond the requested timestamp.
    // Obviously, this is massively inefficient for large logs and something
    // better is needed.
    while (now->get()->timestamp() < timestamp)
    {
        now++;
    }
    return now;
}

