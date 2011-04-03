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

Tide block

'''


import struct


class TideBlock(object):
    def __init__(self, data):
        self.tag = 'TIDE'
        self.major_ver, self.minor_ver, self.num_chans, self.num_chunks = \
                struct.unpack_from('<BBII', data)

    def __str__(self):
        return 'TIDE {0}.{1}, {2} channels, {3} chunks'.format(self.major_ver,
                self.minor_ver, self.num_chans, self.num_chunks)


# vim: tw=79

