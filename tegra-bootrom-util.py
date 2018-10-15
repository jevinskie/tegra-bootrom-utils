#!/usr/bin/env python3

import binascii
import ctypes
import os
import sys

os.environ['PYUSB_DEBUG'] = 'debug'
import usb

from cmd2 import Cmd

USB_XFER_MAX = 0x1000

DEFAULT_VID = 0x0955
DEFAULT_PID = 0x7330

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
	return 0

if __name__ == '__main__':
	sys.exit(main())
