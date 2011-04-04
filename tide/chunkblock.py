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

Chunk block.

'''


import struct


class ChunkBlock(object):
    def __init__(self, data):
        self.tag = 'CHNK'
        self.id, self.count, self.start, self.end, self.compression = \
                struct.unpack_from('<IIQQB', data)
        self._entry_data = data[struct.calcsize('<IIQQB'):]

    def __str__(self):
        return 'CHNK {0} ({1} entries, {2} to {3}, compression {4}, {5}B)'.format(
                self.id, self.count, self.start, self.end, self.compression,
                len(self._entry_data))


# vim: tw=79

