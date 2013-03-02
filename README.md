DynarecPS3
==========

Homebrew tool loading patches on to LV2 allowing dynamic recompiler code support on PS3 GameOS.
  
The tool make possible running JIT code on GameOS PS3 by loading patches to lv2, using peek | poke lv2 calls based in some codes from libkammy stuff on 3.41, right now just work on cfw 4.21 DEX or CEX, it need to be ported to others CFW.

It can be ported too to work on MFW (implementation on lv2_kernel.self, see bugs)

if anyone need help with porting to MFW (LV2_KERNEL) like cfw ps3ita or Rebug so have dynarec support patched without any pkg or lv2 patcher, just try to send me a pm or email.

Usage
==========

Just run the tool, it will beep and leave a log in /dev_hdd0/APP.log.

Actually the tool make a .log (/dev_hdd0/APP.log) with some info if there are errors with the patches, i made this right now because this can help a lot in the porting process as right now just work on 4.21 dex and the patches when are wrong can actually make appear a black screen so again this can speed up the porting.

Notes
==========

Bugs known:

.- Cannot install pkgs, error 0x80029F0A , because this is recommended right now to use this only when is needed (Before running any emulator for example) and if you have previusly installed what do you need later.

Building
==========

Building requires PS3 SDK right now, included are some batch stuff to help in the compile stuff by using MSYS properly installed.

Porting
==========

Right now it can support any cfw just need rights offsets to work good, by now just use lv1 poke to patch 
lv2 protection and later it use hv call lv1_write_htab_entry (so it install hvsc redirect to call hvcalls)
to apply execution permissions on high area of lv2 0x700000 so we can put executable piece of code right there and apply the right patches that make possible running dynamic recompilers code on PS3 GameOS LV2.

It can work too again by patching lv2_kernel just need to relocate the htab payload address and apply permissions by modifying lv2_kernel.self segments page or in a more easy way by relocating branches of htab_payload to fit it in other space with good execution access known on lv2.

This SOFTWARE is not licensed, approved or endorsed by "Sony Computer Entertainment, Inc." (SCEI), SNEI,
SEN or any other party.
