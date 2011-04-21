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
 * Example using the simple memory-based logger.
 */

#include <boost/shared_ptr.hpp>
#include <iostream>
#include <stdexcept>
#include <string.h>
#include <tide/log/log.h>
#include <tide/log/memory_log.h>
#include <tide/views/basic_stream_view.h>
#include <tide/views/direct_writer.h>

#include <stdio.h>

// This function creates a log with two channels. The first channel contains
// the alphabet, the second contains the numbers from 10 to 0. The data is
// spread over about 10 seconds.
// Note that the entries are written in time order, even across channels. This
// is not a requirement of the interface. The log format in use will determine
// how much impact writing entries out of time order will have on performance.
// For example, a format that allows it may have no impact on write performance
// but a high impact on read performance when the entries are re-ordered for
// playback. On the other hand, a format that ensures entries are written into
// the file in time-order no matter how they are presented may have slower
// write performance but no impact on read performance. It is a general
// principle of using TIDE that if you wish to ensure both good read and good
// write performance, you should present the data in an order suited to the
// format in use; even more generally, writing all values in time order is a
// good practice for best average performance across all formats.
// Of course, what would really be useful are some benchmarks of logging
// performance across varying write orders and formats to help users make an
// informed decision.
void write_log(boost::shared_ptr<tide::Log> log)
{
    // Data to add
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    int nums[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    // Create a writeable view onto the log
    tide::DirectWriter writer(log);

    // Make a channel for the alphabet
    boost::shared_array<uint8_t> raw_src(new uint8_t[6]);
    raw_src[0] = 'm';
    raw_src[1] = 'e';
    raw_src[2] = 'm';
    raw_src[3] = 'o';
    raw_src[4] = 'r';
    raw_src[5] = 'y';
    boost::shared_array<uint8_t> fmt(new uint8_t);
    fmt[0] = 'b';
    tide::ChannelInfo alphabet_info("alphabet", "c_types", "memory",
            raw_src, 6, fmt, 1);
    tide::ChannelID a_id = writer.add_channel("alphabet", "c_types", "memory",
            raw_src, 6, fmt, 1);
    // Add a few entries (remember that timestamps are in nanoseconds)
    writer.add_entry(a_id, 384615384,
            reinterpret_cast<uint8_t*>(&alphabet[0]), 1);
    writer.add_entry(alphabet_info, 769230768,
            reinterpret_cast<uint8_t const* const>(&alphabet[1]), 1);
    writer.add_entry(alphabet_info, 1153846152,
            reinterpret_cast<uint8_t const* const>(&alphabet[2]), 1);
    writer.add_entry(a_id, 1538461536,
            reinterpret_cast<uint8_t const* const>(&alphabet[3]), 1);
    // Add an entry in a so-far unallocated channel
    boost::shared_array<uint8_t> fmt2(new uint8_t);
    fmt2[0] = 'd';
    tide::ChannelInfo nums_info("numbers", "c_types", "memory", raw_src, 6,
            fmt2, 1);
    writer.add_entry(nums_info, 1609285920,
            reinterpret_cast<uint8_t const* const>(&nums[0]), sizeof(nums[0]));
    writer.add_entry(a_id, 1923076920,
            reinterpret_cast<uint8_t const* const>(&alphabet[4]), 1);
    writer.add_entry(nums_info, 2000000000,
            reinterpret_cast<uint8_t const* const>(&nums[1]), sizeof(nums[0]));
    writer.add_entry(alphabet_info, 2307692304,
            reinterpret_cast<uint8_t const* const>(&alphabet[5]), 1);
    writer.add_entry(a_id, 2692307688,
            reinterpret_cast<uint8_t const* const>(&alphabet[6]), 1);
    writer.add_entry(a_id, 3076923072,
            reinterpret_cast<uint8_t const* const>(&alphabet[7]), 1);
    writer.add_entry(alphabet_info, 3461538456,
            reinterpret_cast<uint8_t const* const>(&alphabet[8]), 1);
    writer.add_entry(nums_info, 3604698657,
            reinterpret_cast<uint8_t const* const>(&nums[2]), sizeof(nums[0]));
    writer.add_entry(a_id, 3846153840,
            reinterpret_cast<uint8_t const* const>(&alphabet[9]), 1);
    writer.add_entry(a_id, 4230769224,
            reinterpret_cast<uint8_t const* const>(&alphabet[10]), 1);
    writer.add_entry(nums_info, 4496357890,
            reinterpret_cast<uint8_t const* const>(&nums[3]), sizeof(nums[0]));
    writer.add_entry(nums_info, 4496357890,
            reinterpret_cast<uint8_t const* const>(&nums[4]), sizeof(nums[0]));
    writer.add_entry(nums_info, 4496357891,
            reinterpret_cast<uint8_t const* const>(&nums[5]), sizeof(nums[0]));
    writer.add_entry(alphabet_info, 4615384608,
            reinterpret_cast<uint8_t const* const>(&alphabet[11]), 1);
    writer.add_entry(alphabet_info, 4999999992,
            reinterpret_cast<uint8_t const* const>(&alphabet[12]), 1);
    writer.add_entry(a_id, 5384615376,
            reinterpret_cast<uint8_t const* const>(&alphabet[13]), 1);
    writer.add_entry(nums_info, 5768230759,
            reinterpret_cast<uint8_t const* const>(&nums[6]), sizeof(nums[0]));
    writer.add_entry(a_id, 5769230760,
            reinterpret_cast<uint8_t const* const>(&alphabet[14]), 1);
    writer.add_entry(alphabet_info, 6153846144,
            reinterpret_cast<uint8_t const* const>(&alphabet[15]), 1);
    writer.add_entry(alphabet_info, 6538461528,
            reinterpret_cast<uint8_t const* const>(&alphabet[16]), 1);
    writer.add_entry(nums_info, 6586046934,
            reinterpret_cast<uint8_t const* const>(&nums[7]), sizeof(nums[0]));
    writer.add_entry(alphabet_info, 6923076912,
            reinterpret_cast<uint8_t const* const>(&alphabet[17]), 1);
    writer.add_entry(alphabet_info, 7307692296,
            reinterpret_cast<uint8_t const* const>(&alphabet[18]), 1);
    writer.add_entry(nums_info, 7436947254,
            reinterpret_cast<uint8_t const* const>(&nums[8]), sizeof(nums[0]));
    writer.add_entry(a_id, 7692307680,
            reinterpret_cast<uint8_t const* const>(&alphabet[19]), 1);
    writer.add_entry(a_id, 8076923064,
            reinterpret_cast<uint8_t const* const>(&alphabet[20]), 1);
    writer.add_entry(alphabet_info, 8461538448,
            reinterpret_cast<uint8_t const* const>(&alphabet[21]), 1);
    writer.add_entry(a_id, 8846153832,
            reinterpret_cast<uint8_t const* const>(&alphabet[22]), 1);
    writer.add_entry(nums_info, 9136725615,
            reinterpret_cast<uint8_t const* const>(&nums[9]), sizeof(nums[0]));
    writer.add_entry(alphabet_info, 9230769216,
            reinterpret_cast<uint8_t const* const>(&alphabet[23]), 1);
    writer.add_entry(a_id, 9615384600,
            reinterpret_cast<uint8_t const* const>(&alphabet[24]), 1);
    writer.add_entry(a_id, 9999999984,
            reinterpret_cast<uint8_t const* const>(&alphabet[25]), 1);
    writer.add_entry(nums_info, 10000000000,
            reinterpret_cast<uint8_t const* const>(&nums[10]), sizeof(nums[0]));
}


// This function demonstrates reading a stream of data from a log. It reads
// every entry from the given log in time-order and prints them to the
// terminal.
void stream_log(boost::shared_ptr<tide::Log> const log)
{
    // Create a basic streaming view
    tide::BasicStreamView view(log);

    // Print out the channel names
    std::vector<tide::ChannelInfo> channels(view.channel_list());
    std::vector<tide::ChannelInfo>::const_iterator ii(channels.begin());
    std::cout << "Channel names: " << ii->name();
    ++ii;
    for (; ii != channels.end(); ++ii)
    {
        std::cout << ", " << ii->name();
    }
    std::cout << '\n';

    std::cout << "Logged data:\n";
    tide::StreamIterator data_itr(view.begin());
    for (; data_itr != view.end(); ++data_itr)
    {
        std::cout << data_itr->get()->channel() << ":" <<
            view.channels()[data_itr->get()->channel()].name() << ":" <<
            data_itr->get()->timestamp() << '\t';

        if (*(view.channels()[data_itr->get()->channel()].format().get()) == 'b')
        {
            std::cout << data_itr->get()->data().size() << "\t";
            std::cout <<
                *reinterpret_cast<char const*>(data_itr->get()->data().data().get());
        }
        else if (*(view.channels()[data_itr->get()->channel()].format().get()) == 'd')
        {
            std::cout << data_itr->get()->data().size() << "\t";
            std::cout <<
                *reinterpret_cast<int const*>(data_itr->get()->data().data().get());
        }
        else
        {
            throw std::runtime_error("Unknown format");
        }
        std::cout << '\n';
    }
}


void access_log(boost::shared_ptr<tide::Log> const log)
{
}


int main(int argc, char** argv)
{
    // Create an instance of a memory log
    boost::shared_ptr<tide::Log> log(new tide::MemoryLog());
    // Write some data into the log
    write_log(log);
    // Read the data out as a stream
    stream_log(log);
    // Read the data out using random-access
    access_log(log);

    return 0;
}

