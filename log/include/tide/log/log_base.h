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

namespace tide
{
    class LogBase
    {
        public:
            LogBase();
            LogBase(LogBase const& rhs);
            virtual ~LogBase();
    };
};

#endif // !defined(LOG_BASE_H__)

