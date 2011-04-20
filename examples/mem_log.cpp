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

#include <iostream>
#include <string.h>
#include <tide/views/basic_stream_view.h>
#include <tide/log/log_base.h>
#include <tide/log/memory_log.h>


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
void write_log(LogBase* const log)
{
    // Data to add
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    int nums[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    // Create a writeable view onto the log
    DirectWriter writer(log);

    // Make a channel for the alphabet
    ChannelInfo alphabet_info("alphabet", "c_types", "memory", "memory",
            strlen("memory"), "b", strlen("b"));
    ChannelID a_id = writer.add_channel("alphabet", "c_types", "memory",
            "memory", strlen("memory"), "b", strlen("b"));
    // Add a few entries (remember that timestamps are in nanoseconds)
    writer.add_entry(a_id, 384615384, static_cast<uint8_t*>(&alphabet[0]));
    writer.add_entry(alphabet_info, 769230768, static_cast<uint8_t const* const>(&alphabet[1]));
    writer.add_entry(alphabet_info, 1153846152, static_cast<uint8_t const* const>(&alphabet[2]));
    writer.add_entry(a_id, 1538461536, static_cast<uint8_t const* const>(&alphabet[3]));
    // Add an entry in a so-far unallocated channel
    ChannelInfo nums_info("numbers", "c_types", "memory", "memory",
            strlen("memory"), "d", strlen("d"));
    writer.add_entry(nums_info, 1609285920,
            static_cast<uint8_t const* const>(&nums[0]));
    writer.add_entry(a_id, 1923076920,
            static_cast<uint8_t const* const>(&alphabet[4]));
    writer.add_entry(nums_info, 2000000000,
            static_cast<uint8_t const* const>(&nums[1]));
    writer.add_entry(alphabet_info, 2307692304,
            static_cast<uint8_t const* const>(&alphabet[5]));
    writer.add_entry(a_id, 2692307688,
            static_cast<uint8_t const* const>(&alphabet[6]));
    writer.add_entry(a_id, 3076923072,
            static_cast<uint8_t const* const>(&alphabet[7]));
    writer.add_entry(alphabet_info, 3461538456,
            static_cast<uint8_t const* const>(&alphabet[8]));
    writer.add_entry(nums_info, 3604698657,
            static_cast<uint8_t const* const>(&nums[2]));
    writer.add_entry(a_id, 3846153840,
            static_cast<uint8_t const* const>(&alphabet[9]));
    writer.add_entry(a_id, 4230769224,
            static_cast<uint8_t const* const>(&alphabet[10]));
    writer.add_entry(nums_info, 4496357890,
            static_cast<uint8_t const* const>(&nums[3]));
    writer.add_entry(nums_info, 4496357890,
            static_cast<uint8_t const* const>(&nums[4]));
    writer.add_entry(nums_info, 4496357891,
            static_cast<uint8_t const* const>(&nums[5]));
    writer.add_entry(alphabet_info, 4615384608,
            static_cast<uint8_t const* const>(&alphabet[11]));
    writer.add_entry(alphabet_info, 4999999992,
            static_cast<uint8_t const* const>(&alphabet[12]));
    writer.add_entry(a_id, 5384615376,
            static_cast<uint8_t const* const>(&alphabet[13]));
    writer.add_entry(nums_info, 5768230759,
            static_cast<uint8_t const* const>(&nums[6]));
    writer.add_entry(a_id, 5769230760,
            static_cast<uint8_t const* const>(&alphabet[14]));
    writer.add_entry(alphabet_info, 6153846144,
            static_cast<uint8_t const* const>(&alphabet[15]));
    writer.add_entry(alphabet_info, 6538461528,
            static_cast<uint8_t const* const>(&alphabet[16]));
    writer.add_entry(nums_info, 6586046934,
            static_cast<uint8_t const* const>(&nums[7]));
    writer.add_entry(alphabet_info, 6923076912,
            static_cast<uint8_t const* const>(&alphabet[17]));
    writer.add_entry(alphabet_info, 7307692296,
            static_cast<uint8_t const* const>(&alphabet[18]));
    writer.add_entry(nums_info, 7436947254,
            static_cast<uint8_t const* const>(&nums[8]));
    writer.add_entry(a_id, 7692307680,
            static_cast<uint8_t const* const>(&alphabet[19]));
    writer.add_entry(a_id, 8076923064,
            static_cast<uint8_t const* const>(&alphabet[20]));
    writer.add_entry(alphabet_info, 8461538448,
            static_cast<uint8_t const* const>(&alphabet[21]));
    writer.add_entry(a_id, 8846153832,
            static_cast<uint8_t const* const>(&alphabet[22]));
    writer.add_entry(nums_info, 9136725615,
            static_cast<uint8_t const* const>(&nums[9]));
    writer.add_entry(alphabet_info, 9230769216,
            static_cast<uint8_t const* const>(&alphabet[23]));
    writer.add_entry(a_id, 9615384600,
            static_cast<uint8_t const* const>(&alphabet[24]));
    writer.add_entry(a_id, 9999999984,
            static_cast<uint8_t const* const>(&alphabet[25]));
    writer.add_entry(nums_info, 10000000000,
            static_cast<uint8_t const* const>(&nums[10]));
}


// This function demonstrates reading a stream of data from a log. It reads
// every entry from the given log in time-order and prints them to the
// terminal.
void stream_log(LogBase const* const log)
{
    // Create a basic streaming view
    BasicStreamView view(*log);

    // Print out the channel names
    std::vector<ChannelInfo>::const_iterator ii(view.channels().begin());
    std::cout << "Channel names: " << ii->name();
    ++ii;
    for (; ii != view.channels().end(); ++ii)
    {
        std::cout << ", " << ii->name();
    }
    std::cout << '\n';
}


void access_log(LogBase const* const log)
{
}


int main(int argc, char** argv)
{
    // Create an instance of a memory log
    LogBase* log(new MemoryLog());
    // Write some data into the log
    write_log(log);
    // Read the data out as a stream
    stream_log(log);
    // Read the data out using random-access
    access_log(log);

    delete log;
    return 0;
}

