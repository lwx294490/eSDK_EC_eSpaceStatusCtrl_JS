@echo off
echo ���������� 1-1���� eSpaceStatusCtrl Release�汾 ��������������������������
@"%VS90COMNTOOLS%\..\IDE\devenv.com" ..\eSpaceStatusCtrl\eSpaceStatusVS2008.sln /Rebuild "Release|Win32"
echo ���������� 1-2���� eSpaceStatusCtrl Release�汾�ɹ� ����������������������

::�رջ���
@echo off

::��õ�ǰʱ�䣬��Ϊ���ɰ汾��Ŀ¼��
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

::���ø�������
set   	DateTime=%Year%-%Month%-%Day%-%Hour%-%Minute%
set	WinRarRoot=C:\Program Files\WinRAR

@echo off
echo %DateTime%
@echo .


echo ����������2-2��������ļ��гɹ�����������

echo ����������3-1 ����espaceStatusCtrl.dll Release�汾��������������������������
xcopy /Y ..\eSpaceStatusCtrl\output\release\espaceStatusCtrl.dll 	           ".\version\"
xcopy /Y ..\eSpaceStatusCtrl\output\release\espaceStatusCtrl.pdb 	           ".\version\"
xcopy /Y ..\eSpaceStatusCtrl\output\release\espaceStatusCtrl.lib 	           ".\version\"
xcopy /Y ..\eSpaceStatusCtrl\output\release\eSDKClientLogCfg.ini	           ".\version\"
echo ����������3-2���� espaceStatusCtrl.dll Release�汾  �ɹ�������������������������

echo ����������4-1 ���� espaceStatusCtrl��������Դ�ļ� ��������������������������
xcopy /Y /S .\..\..\platform\eSDKClientLogAPI\release\eSDKLogAPI.dll	          ".\version\"
xcopy /Y /S .\..\..\platform\eSDKClientLogAPI\release\eSDKLogAPI.lib	          ".\version\"
xcopy /Y /S .\..\..\platform\eSDKClientLogAPI\release\eSDKLogAPI.pdb	          ".\version\"
echo ����������4-2���� espaceStatusCtrl��������Դ�ļ� �ɹ�������������������������

echo ����������5-1 ���� �汾˵���ļ� ����������������������������������������������
xcopy /Y  .\readme.txt	                                                           ".\version\"
echo ����������5-2���� �汾˵���ļ�������������������������������������������������

@echo .
@echo ������������������������������ʼ����汾��������������������������������	

cd version
"%WinRarRoot%\WinRAR.exe" a -r eSDK_UC_PC_eSpaceStatusCtrl.zip .\
move eSDK_UC_PC_eSpaceStatusCtrl.zip ..\
cd ..
rd /Q /S version

@echo .
@echo ������������������������������ɴ���汾��������������������������������	

pause