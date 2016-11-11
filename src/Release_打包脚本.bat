@echo off
echo －－－－－ 1-1编译 eSpaceStatusCtrl Release版本 －－－－－－－－－－－－－
@"%VS90COMNTOOLS%\..\IDE\devenv.com" ..\eSpaceStatusCtrl\eSpaceStatusVS2008.sln /Rebuild "Release|Win32"
echo －－－－－ 1-2编译 eSpaceStatusCtrl Release版本成功 －－－－－－－－－－－

::关闭回显
@echo off

::获得当前时间，作为生成版本的目录名
for /F "tokens=1-4 delims=-/ " %%i in ('date /t') do (
   set Year=%%i
   set Month=%%j
   set Day=%%k
   set DayOfWeek=%%l
)
for /F "tokens=1-2 delims=: " %%i in ('time /t') do (
   set Hour=%%i
   set Minute=%%j
)

::设置各变量名
set   	DateTime=%Year%-%Month%-%Day%-%Hour%-%Minute%
set	WinRarRoot=C:\Program Files\WinRAR

@echo off
echo %DateTime%
@echo .


echo －－－－－2-2创建打包文件夹成功－－－－－

echo －－－－－3-1 拷贝espaceStatusCtrl.dll Release版本－－－－－－－－－－－－－
xcopy /Y ..\eSpaceStatusCtrl\output\release\espaceStatusCtrl.dll 	           ".\version\"
xcopy /Y ..\eSpaceStatusCtrl\output\release\espaceStatusCtrl.pdb 	           ".\version\"
xcopy /Y ..\eSpaceStatusCtrl\output\release\espaceStatusCtrl.lib 	           ".\version\"
xcopy /Y ..\eSpaceStatusCtrl\output\release\eSDKClientLogCfg.ini	           ".\version\"
echo －－－－－3-2拷贝 espaceStatusCtrl.dll Release版本  成功－－－－－－－－－－－－

echo －－－－－4-1 拷贝 espaceStatusCtrl依赖的资源文件 －－－－－－－－－－－－－
xcopy /Y /S .\..\..\platform\eSDKClientLogAPI\release\eSDKLogAPI.dll	          ".\version\"
xcopy /Y /S .\..\..\platform\eSDKClientLogAPI\release\eSDKLogAPI.lib	          ".\version\"
xcopy /Y /S .\..\..\platform\eSDKClientLogAPI\release\eSDKLogAPI.pdb	          ".\version\"
echo －－－－－4-2拷贝 espaceStatusCtrl依赖的资源文件 成功－－－－－－－－－－－－

echo －－－－－5-1 拷贝 版本说明文件 －－－－－－－－－－－－－－－－－－－－－－－
xcopy /Y  .\readme.txt	                                                           ".\version\"
echo －－－－－5-2拷贝 版本说明文件－－－－－－－－－－－－－－－－－－－－－－－－

@echo .
@echo －－－－－－－－－－－－－－开始打包版本－－－－－－－－－－－－－－－－	

cd version
"%WinRarRoot%\WinRAR.exe" a -r eSDK_UC_PC_eSpaceStatusCtrl.zip .\
move eSDK_UC_PC_eSpaceStatusCtrl.zip ..\
cd ..
rd /Q /S version

@echo .
@echo －－－－－－－－－－－－－－完成打包版本－－－－－－－－－－－－－－－－	

pause