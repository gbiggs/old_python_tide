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

Channel block.

'''


import struct


class ChanBlock(object):
    def __init__(self, data):
        self.tag = 'CHAN'
        self.id, name_size = struct.unpack_from('<IB', data)
        data = data[struct.calcsize('<IB'):]
        self.name, src_size = struct.unpack_from('<{0}sB'.format(name_size),
                data)
        data = data[struct.calcsize('<{0}sB'.format(name_size)):]
        self.src, fmt_size = struct.unpack_from('<{0}BI'.format(src_size),
                data)
        data = data[struct.calcsize('<{0}BI'.format(src_size)):]
        self.fmt = struct.unpack_from('<{0}s'.format(fmt_size), data)[0]

    def __str__(self):
        return 'CHAN {0}:{1}:{2}/{3}'.format(self.id, self.name, self.src,
                self.fmt)


# vim: tw=79

