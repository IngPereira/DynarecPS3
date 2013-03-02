@echo off
make.exe
del EBOOT.self
RD objs /S /Q
tools\scetool.exe --self-app-version=0001000000000000 --sce-type=SELF --compress-data=TRUE --self-add-shdrs=TRUE --skip-sections=FALSE --key-revision=1 --self-auth-id=1010000001000003 --self-vendor-id=01000002 --self-type=APP --self-fw-version=0003004000000000 --self-ctrl-flags 4000000000000000000000000000000000000000000000000000000000000002 --self-cap-flags 00000000000000000000000000000000000000000000007B0000000100000000 --encrypt EBOOT.ELF EBOOT.BIN
pause
