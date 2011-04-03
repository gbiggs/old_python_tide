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


import struct

import chanblock
import chunkblock
import indexblock
import tideblock


READ=1
WRITE=2


class TIDE(object):
    def __init__(self, filename, mode=READ):
        self._fn = filename
        self._mode = mode
        self._hdr_str = struct.Struct('<4sQ')
        self._open()
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

    def _close(self):
        self._f.close()
        self._f = None

    def _open(self):
        if self._mode == WRITE:
            self._f = file(self._fn, 'wb')
        else:
            self._f = file(self._fn, 'rb')

    def _read_block(self):
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

