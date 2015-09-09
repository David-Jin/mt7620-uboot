U-Boot for wrtnode
==================

Prerequisites
-------------

Get Ralink SDK, filename: MTK_Ralink_ApSoC_SDK_4120_20120607.tar.bz2

Unpack the "toolchain/buildroot-gcc342" folder to "/opt/buildroot-gcc342", or wherever you want, but then you need to replace the paths below.


Building
--------

	$ git clone git@github.com:agustim/u-boot_wrtnode.git
	$ export CONFIG_CROSS_COMPILER_PATH=/opt/buildroot-gcc342/bin  # necessary if not in /opt
	$ export PATH=/opt/buildroot-gcc342/bin:$PATH
	$ cp wrtnode_config .config
	$ make menuconfig # Exit and save 
	$ make
	$ hexdump -C uboot.bin | head  # look at first bytes to verify

NOTE: The output filename for directly flashing the binary has to be **uboot.bin**.


Reference first bytes
---------------------

The first bytes of uboot.bin are some sort of interrupt vector table and should look approximately like this (exact address entries may vary):

	00000000  ff 00 00 10 00 00 00 00  fd 00 00 10 00 00 00 00  |................|
	00000010  7f 02 00 10 00 00 00 00  7d 02 00 10 00 00 00 00  |........}.......|
	00000020  7b 02 00 10 00 00 00 00  79 02 00 10 00 00 00 00  |{.......y.......|
	00000030  77 02 00 10 00 00 00 00  75 02 00 10 00 00 00 00  |w.......u.......|
	00000040  73 02 00 10 00 00 00 00  71 02 00 10 00 00 00 00  |s.......q.......|


