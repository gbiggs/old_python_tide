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
 * Base class for views.
 */


#if !defined(VIEW_BASE_H__)
#define VIEW_BASE_H__


#include <tide/log/channels.h>
#include <stdint.h>
#include <vector>


namespace tide
{
    class ViewBase
    {
        public:
            ViewBase();
            virtual ~ViewBase();

            virtual uint64_t start_time() const = 0;
            virtual uint64_t end_time() const = 0;
            virtual std::vector<ChannelInfo> channels() const = 0;

        private:
    };
};

#endif // !defined(VIEW_BASE_H__)

