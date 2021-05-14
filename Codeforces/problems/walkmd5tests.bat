@echo off
setlocal enableextensions 
setlocal enabledelayedexpansion

del alltests.lst 2> nul

for /d %%d in (*) do (
  if exist %%d\tests (
    for %%f in (%%d\tests\?? %%d\tests\??.a) do echo %%f >> alltests.lst
  )
)

..\bin\walkmd5 -f alltests.lst -o alltests.tmp
rm alltests.lst

..\bin\walkcompare alltests.md5 alltests.tmp
