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


#include <tide/views/view_base.h>

#include <stdexcept>

using namespace tide;


ViewBase::ViewBase()
    : start_time_(0), end_time_(0), next_mdl_(0)
{
}


ViewBase::~ViewBase()
{
}


ModelID ViewBase::add_model(LogBase& model)
{
    models_[next_mdl_++] = &model;
    update_view();
}


void ViewBase::rem_model(ModelID& id)
{
    if (models_.find(id) == models_.end())
    {
        throw std::runtime_error("Bad model ID");
    }
    models_.erase(id);
    update_view();
}

