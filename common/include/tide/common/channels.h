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
 * Channel-related objects.
 */

#if !defined(CHANNELS_H__)
#define CHANNELS_H__

#include <string>

namespace tide
{
    typedef unsigned int ChannelID;

    class ChannelInfo
    {
        public:
            ChannelInfo();
            ChannelInfo(std::string name, std::string source_type,
                    std::string source, unsigned char const* const raw_source,
                    unsigned int size);
            ~ChannelInfo();

            std::string name() const { return name_; };
            void name(std::string name) { name_ = name; };
            std::string source_type() const { return source_type_; };
            void source_type(std::string type) { source_type_ = type; };
            std::string source() const { return source_; };
            void source(std::string source) { source_ = source; };
            unsigned char const* raw_source() const { return raw_source_; }
            void raw_source(unsigned char const* const raw_source,
                    unsigned int size);

        private:
            std::string name_;
            std::string source_type_;
            std::string source_;
            unsigned char* raw_source_;
    };
};

#endif // !defined(CHANNELS_H__)

