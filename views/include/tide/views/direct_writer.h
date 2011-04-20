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
 * Simple writer view.
 */


#if !defined(DIRECT_WRITER_H__)
#define DIRECT_WRITER_H__


#include <stdint.h>
#include <string>
#include <tide/log/channels.h>
#include <tide/log/log_base.h>
#include <tide/views/view_base.h>


namespace tide
{
    class DirectWriter
        : public ViewBase
    {
        public:
            DirectWriter(LogBase& log);
            DirectWriter(DirectWriter const& rhs);
            virtual ~DirectWriter();

            virtual uint64_t start_time() const;
            virtual uint64_t end_time() const;
            virtual std::vector<ChannelInfo> channels() const;

            virtual ChannelID add_channel(std::string name,
                std::string source_type, std::string source,
                uint8_t const* const raw_source, size_t raw_source_size,
                uint8_t const* const format, size_t format_size);

            virtual void add_entry(ChannelID const& channel,
                uint64_t timestamp, uint8_t const* const data, size_t size);
            virtual void add_entry(ChannelInfo const& channel,
                uint64_t timestamp, uint8_t const* const data, size_t size);

        protected:
            LogBase& log_;
    };
};

#endif // !defined(DIRECT_WRITER_H__)

