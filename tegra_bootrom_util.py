#!/usr/bin/env python3

import binascii
import copy
from ctypes import *
# import ctypes
import enum
import os
import sys

os.environ['PYUSB_DEBUG'] = 'debug'
import usb

from cmd2 import Cmd

USB_XFER_MAX = 0x1000

DEFAULT_VID = 0x0955
DEFAULT_PID = 0x7330

class cmd_type(enum.IntEnum):
	CMD_TTY = 0x1

class StructureVariableSized(LittleEndianStructure):
	_variable_sized_ = []

	def __new__(self, variable_sized=(), **kwargs):
		def name_builder(name, variable_sized):
			for variable_sized_field_name, variable_size in variable_sized:
				name += variable_sized_field_name.title() + '[{0}]'.format(variable_size)
			return name

		local_fields = copy.deepcopy(self._fields_)
		for variable_sized_field_name, variable_size in variable_sized:
			match_type = None
			for matching_field_name, matching_type in self._variable_sized_:
				if variable_sized_field_name == matching_field_name:
					match_type = matching_type
					break
			if match_type is None:
				raise Exception
			local_fields.append((variable_sized_field_name, match_type*variable_size),)
		print("local_fields: {}".format(local_fields))
		name = name_builder(self.__name__, variable_sized)
		class BaseCtypesStruct(Structure):
			_fields_ = local_fields
			_variable_sized_ = self._variable_sized_
		classdef = BaseCtypesStruct
		classdef.__name__ = name
		return BaseCtypesStruct(**kwargs)


class StructwithVariableArrayLength(StructureVariableSized):
    _fields_ = [
        ('static', c_uint32),
        ('another_static', c_uint64),
        ('len', c_uint32),
        ]
    _variable_sized_ = [
        ('data', c_uint8)
    ]

struct_map = {
    1: StructwithVariableArrayLength
} 
sval32 = struct_map[1](variable_sized=(('data', 32),),)
print(sval32)
print(sval32.data)
sval128 = struct_map[1](variable_sized=(('data', 128),),)
print(sval128)
print(sval128.data)

class cmd_hdr(LittleEndianStructure):
	_pack_ = 1
	_fields_ = [('cmd_type', c_uint32),
				('cmd_size', c_uint32)]

class cmd_tty(StructureVariableSized):
	_pack_ = 1
	_fields_ = [('hdr', cmd_hdr),]
	_variable_sized_ = [('tty_buf', c_char)]

class cmd_tty_fixed(LittleEndianStructure):
	_fields_ = [('hdr', cmd_hdr), ('tty_buf', c_char * 32),]

class RCMDevice:
	# Default to the T30 RCM VID and PID.
	DEFAULT_VID = 0x0955
	DEFAULT_PID = 0x7330

	def __init__(self, wait_for_device=False, vid=DEFAULT_VID, pid=DEFAULT_PID):
		self.dev = usb.core.find(idVendor=vid, idProduct=pid)
		if self.dev is None:
			# ... and we're allowed to wait for one, wait indefinitely for one to appear...
			if wait_for_device:
				print("Waiting for a TegraRCM device to come online...")
				while self.dev is None:
					self.dev = usb.core.find(idVendor=vid, idProduct=pid)

			# ... or bail out.
			else:
				raise IOError("No TegraRCM device found?")

	def read(self, length=USB_XFER_MAX, timeout=3000):
		assert length <= USB_XFER_MAX
		""" Reads data from the RCM protocol endpoint. """
		return bytes(self.dev.read(0x81, length, timeout))

	def write(self, data, timeout=3000):
		"""
		Writes a single RCM buffer, which should be USB_XFER_MAX long.
		The last packet may be shorter, and should trigger a ZLP (e.g. not divisible by 512).
		If it's not, send a ZLP.
		"""
		assert len(data) <= USB_XFER_MAX
		return self.dev.write(0x01, data, timeout)

def main():
	rcmdev = RCMDevice()
	buf = rcmdev.read()
	print(buf)
	print(binascii.hexlify(buf))
	recv_cmd = cmd_hdr.from_buffer_copy(buf)
	print(recv_cmd)
	print(recv_cmd.cmd_type)
	print(recv_cmd.cmd_size)
	if recv_cmd.cmd_type == cmd_type.CMD_TTY:
		tty_buf_size = recv_cmd.cmd_size - sizeof(recv_cmd)
		print(tty_buf_size)
		recv_cmd_tty_t = cmd_tty(variable_sized=(('tty_buf', tty_buf_size),),)
		print(recv_cmd_tty_t.__class__)
		print(recv_cmd_tty_t.__repr__)
		print(sizeof(recv_cmd_tty_t))
		print(sizeof(recv_cmd))
		print(sizeof(recv_cmd_tty_t.hdr))
		print(recv_cmd_tty_t)
		recv_cmd_tty = recv_cmd_tty_t.__class__.from_buffer_copy(buf)
		print(recv_cmd_tty)
		tty_str = recv_cmd_tty.tty_buf.decode('utf-8')
		print(tty_str)
	return 0

if __name__ == '__main__':
	sys.exit(main())
