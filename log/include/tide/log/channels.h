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


#include <boost/shared_array.hpp>
#include <iostream>
#include <map>
#include <stdint.h>
#include <string>


namespace tide
{
    typedef unsigned int ChannelID;

    class ChannelInfo
    {
        public:
            ChannelInfo();
            ChannelInfo(std::string name, std::string source_type, std::string
                    source, boost::shared_array<uint8_t> const raw_source,
                    size_t raw_source_size,
                    boost::shared_array<uint8_t> const format,
                    size_t format_size);
            ChannelInfo(ChannelInfo const& rhs);
            ~ChannelInfo();

            std::string name() const { return name_; };
            void name(std::string name) { name_ = name; };
            std::string source_type() const { return source_type_; };
            void source_type(std::string type) { source_type_ = type; };
            std::string source() const { return source_; };
            void source(std::string source) { source_ = source; };
            boost::shared_array<uint8_t> const raw_source() const
                { return raw_source_; };
            size_t raw_source_size() const { return raw_source_size_; };
            void raw_source(boost::shared_array<uint8_t> const raw_source,
                    size_t size);
            boost::shared_array<uint8_t> const format() const { return format_; };
            size_t format_size() const { return format_size_; };
            void format(boost::shared_array<uint8_t> const format, size_t size);

            // Equivalence for a channel is defined as having the same name
            bool operator==(ChannelInfo const& rhs);
            bool operator!=(ChannelInfo const& rhs);

            friend std::ostream& operator<<(std::ostream& o,
                    ChannelInfo const& ci);

        private:
            std::string name_;
            std::string source_type_;
            std::string source_;
            boost::shared_array<uint8_t> raw_source_;
            size_t raw_source_size_;
            boost::shared_array<uint8_t> format_;
            size_t format_size_;
    };


    typedef std::map<ChannelID const, ChannelInfo> ChannelIDMap;
    typedef std::map<std::string const, ChannelInfo> ChannelNameMap;


    std::ostream& operator<<(std::ostream& o, ChannelInfo const& ci);
};


#endif // !defined(CHANNELS_H__)

