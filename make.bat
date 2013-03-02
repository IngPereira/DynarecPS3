@echo off
set CONTENTID=LD0000-DYNA00001_00-0000000000000000
make.exe
del EBOOT.self
RD objs /S /Q
RD PKG/DYNA00001/USRDIR /S /Q
tools\scetool.exe --self-app-version=0001000000000000 --sce-type=SELF --compress-data=TRUE --self-add-shdrs=TRUE --skip-sections=FALSE --key-revision=1 --self-auth-id=1010000001000003 --self-vendor-id=01000002 --self-type=NPDRM --np-license-type=FREE --np-app-type=EXEC --np-real-fname=EBOOT.BIN --self-fw-version=0003004000000000 --self-ctrl-flags 4000000000000000000000000000000000000000000000000000000000000002 --self-cap-flags 00000000000000000000000000000000000000000000007B0000000100000000 --np-content-id=%CONTENTID% --encrypt EBOOT.ELF EBOOT.BIN
mkdir PKG\DYNA00001\USRDIR
mv EBOOT.BIN PKG/DYNA00001/USRDIR/EBOOT.BIN
pause
