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

Index block.

'''


import struct


class IndexBlock(object):
    def __init__(self, data):
        self.tag = 'INDX'
        self.chan_id, self.count = struct.unpack_from('<II', data)
        data = data[struct.calcsize('<II'):]
        self.indices = []
        unpacker = struct.Struct('<IQQ')
        for ii in range(self.count):
            self.indices.append(unpacker.unpack_from(data))
            data = data[unpacker.size:]

    def __str__(self):
        return 'INDX Channel {0}, {1} indices, Index 0: {2}'.format(
                self.chan_id, self.count, self.indices[0])


# vim: tw=79

