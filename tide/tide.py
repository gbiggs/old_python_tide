# -*- Python -*-
# -*- coding: utf-8 -*-

'''TIDE

Copyright (C) 2011
    Geoffrey Biggs
    RT-Synthesis Research Group
    Intelligent Systems Research Institute,
    National Institute of Advanced Industrial Science and Technology (AIST),
    Japan
    All rights reserved.
Licensed under the Eclipse Public License -v 1.0 (EPL)
http://www.opensource.org/licenses/eclipse-1.0.txt

Time-Indexed Data Entries (TIDE) log format prototype.

'''


import os
import struct
import time

import chanblock
import chunkblock
import indexblock
import tideblock


READ=1
WRITE=2


class Channel(object):
    def __init__(self, id, name, src, fmt):
        self.id = id
        self.name = name
        self.src_len = len(src)
        self.src = src
        self.fmt_len = len(fmt)
        self.fmt = fmt


class Index(object):
    def __init__(self, chan_id):
        self.chan_id = chan_id
        self.indices = []


class IndexEntry(object):
    def __init__(self, chunk_id, timestamp, offset):
        self.chunk_id = chunk_id
        self.ts = timestamp
        self.offset = offset


class TIDE(object):
    def __init__(self, filename, mode=READ):
        self._fn = filename
        self._mode = mode
        self._hdr_str = struct.Struct('<4sQ')
        self._open()
        if self._mode == READ:
            # Read the first block
            blk = self._read_block()
            if blk.tag != 'TIDE':
                raise ValueError(filename)
            if blk.major_ver != 1:
                raise ValueError(blk.major_ver)

            # Read and print the file
            print blk
            while True:
                blk = self._read_block()
                if not blk:
                    break
                print blk

    def add_chan(self, name, src, fmt):
        chan_id = max(self._chans.keys()) + 1
        self._chans[name] = Channel(chan_id, name, src, fmt)
        self._indices[chan_id] = Index(chan_id)

    # Value must be a string containing the raw data
    def add_entry(self, chan, timestamp, value):
        # Get the channel ID for this value
        chan_id = self._chans[name].id
        # Add it to the index
        self._indices[chan_id].indices.append(IndexEntry(self._cur_chunk,
            timestamp, self.f.tell() - self._chunk_offsets[self._cur_chunk]))
        # Write the value into the chunk
        self._f.write('<IQ{0}s'.format(len(value)), chan_id, timestamp, value)
        self._cur_chunk_end_ts = timestamp
        self._cur_chunk_count += 1

    def close(self):
        if self._mode == WRITE:
            self._finalise_write()
        self._f.close()

    def _finalise_write(self):
        # Close the current chunk
        self._close_chunk()
        # Write the counts into the TIDE block (which is always at the same
        # place in the file - the start)
        self._f.seek(14, os.SEEK_SET)
        self._f.write(struct.pack('<II', len(self._chans), self._num_chunks))
        self._f.seek(0, os.SEEK_END)
        self._write_chan_blocks()
        self._write_index_blocks()

    def _write_chan_blocks(self):
        for c in self._chans:
            packed = struct.pack('<4sIB{0}sB{1}sI{2}s'.format(len(c.name),
                c.src_len, c.fmt_len),
                'CHAN', c.id, len(c.name), c.name, c.src_len, c.src, c.fmt_len,
                c.fmt)
            self._f.write(packed)

    def _write_index_blocks(self):
        for index in self._indices:
            packed = struct.pack('<4sII', 'INDX', index.chan_id, len(index.indices))
            packer = struct.Struct('<IQQ')
            for i in index.indices:
                packed += packer.pack(i.chunk_id, i.ts, i.offset)
            self._f.write(packed)

    def _initialise_write(self):
        # Write the initial TIDE block
        self._chans = {}
        self._indices = {}
        self._cur_chunk = -1
        self._chunk_offsets = {}
        self._num_chunks = 1
        self._f.write(struct.pack('<4sQBBII', 'TIDE', 10, 1, 0, 0, 0))
        self._new_chunk()

    def _close_chunk(self):
        self._f.seek(self._chunk_offsets[self._cur_chunk] + 16, os.SEEK_SET)
        self._f.write(struct.pack('<I', self._cur_chunk_count))
        self._f.seek(self._chunk_offsets[self._cur_chunk] + 28, os.SEEK_SET)
        self._f.write(struct.pack('<Q', self._cur_chunk_end_ts))

    def _new_chunk(self):
        # Start the chunk block to receive data
        self._f.seek(0, os.SEEK_END)
        self._cur_chunk += 1
        self._cur_chunk_count = 0
        self._chunk_offsets[self._cur_chunk] = self._f.tell()
        self._cur_chunk_end_ts = int(time.time() * 1e9)
        self._f.write(struct.pack('<4sQIIQQB', 'CHNK', 0, self._cur_chunk, 0,
            self._cur_chunk_end_ts, 0, 0))
        self._num_chunks += 1

    def _open(self):
        if self._mode == WRITE:
            self._f = file(self._fn, 'wb')
            self._initialise_write()
        else:
            self._f = file(self._fn, 'rb')

    def _read_block(self):
        if self._mode != READ:
            raise IOError
        # Read the block header
        hdr = self._f.read(self._hdr_str.size)
        if len(hdr) == 0:
            return None
        tag, size = self._hdr_str.unpack(hdr)
        data = self._f.read(size)
        if tag == 'TIDE':
            return tideblock.TideBlock(data)
        elif tag == 'CHAN':
            return chanblock.ChanBlock(data)
        elif tag == 'INDX':
            return indexblock.IndexBlock(data)
        elif tag == 'CHNK':
            return chunkblock.ChunkBlock(data)
        else:
            raise ValueError(tag)


# vim: tw=79

