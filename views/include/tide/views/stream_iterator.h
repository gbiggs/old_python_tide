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
 * Iterator over a stream view's entries.
 */

#if !defined(STREAM_ITERATOR_H__)
#define STREAM_ITERATOR_H__


#include <boost/iterator/iterator_facade.hpp>
#include <boost/shared_ptr.hpp>
#include <tide/log/entry_index_base.h>


namespace tide
{
    // I know this class is basically re-implementing
    // std::vector::const_iterator, but I want to demonstrate that streaming
    // views should provide their own iterators that are more efficient than
    // storing an entire huge index in memory. This class provides a starting
    // point for doing so.
    class StreamIterator
        : public boost::iterator_facade<StreamIterator, EntryIndexBase,
            boost::forward_traversal_tag>
    {
        public:
            StreamIterator(boost::shared_ptr<std::vector<EntryIndexBase> > index,
                    std::vector<EntryIndexBase>:: pos_);
            StreamIterator(StreamIterator const& rhs);

        private:
            std::vector<EntryIndexBase>::const_iterator pos_;
            boost::shared_ptr<std::vector<EntryIndexBase> > index_;
    };
};

#endif // !defined(STREAM_ITERATOR_H__)

