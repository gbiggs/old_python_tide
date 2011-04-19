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

#include <map>
#include <stdint.h>
#include <tide/common/channels.h>
#include <tide/log/log_base.h>

namespace tide
{
    typedef unsigned int ModelID;

    class ViewBase
    {
        public:
            ViewBase();
            virtual ~ViewBase();

            virtual ModelID add_model(LogBase& model);
            virtual void rem_model(ModelID& id);

            uint64_t start_time() const { return start_time_; };
            uint64_t end_time() const { return end_time_; };

        private:
            std::map<ChannelID, ChannelInfo> channels_;
            uint64_t start_time_, end_time_;

            std::map<ModelID, LogBase*> models_;
            ModelID next_mdl_;

            virtual void update_view() = 0;
    };
};

#endif // !defined(VIEW_BASE_H__)

