; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
AppName=VTP Software
AppVerName=VTP Software 1.61 BETA (2015.09.13)
AppPublisher=Virtual Terrain Project
AppPublisherURL=http://vterrain.org/
AppSupportURL=http://vterrain.org/
AppUpdatesURL=http://vterrain.org/
DefaultDirName={pf}\VTP
DefaultGroupName=VTP
AllowNoIcons=yes
LicenseFile=C:\VTP\license.txt
OutputBaseFilename=setup_vtp
OutputDir=C:\Distrib
; We need the following because Windows won't turn Registry settings into Enviroment variables w/o a reboot
AlwaysRestart=yes

[Types]
Name: "standard"; Description: "Standard installation"; Flags: iscustom

[Components]
Name: "main"; Description: "The VTP applications"; Types: standard
Name: "data"; Description: "Data used by the applications"; Types: standard
Name: "docs"; Description: "Documentation for the applications"; Types: standard
Name: "proj"; Description: "Data files for coordinate systems (GDAL/PROJ.4)"; Types: standard
Name: "dlls"; Description: "Third-party DLL files (wxWidgets, OSG, etc.)"; Types: standard

[Tasks]
Name: env; Description: "Set environment variables for coordinate system data files"; GroupDescription: "Environment variables:"; Components: proj

[Registry]
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Control\Session Manager\Environment"; ValueType: string; ValueName: "GDAL_DATA"; ValueData: "{app}\GDAL-data"; Components: proj
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Control\Session Manager\Environment"; ValueType: string; ValueName: "PROJ_LIB"; ValueData: "{app}\PROJ4-data"; Components: proj

[Files]
Source: "C:\VTP\vc14\TerrainApps\CManager\Release\CManager.exe"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: main
Source: "C:\VTP\TerrainApps\CManager\itemtypes.txt"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: main
Source: "C:\VTP\TerrainApps\CManager\tags.txt"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: main
Source: "C:\VTP\TerrainApps\CManager\Docs\*"; DestDir: "{app}/Docs/CManager"; Flags: ignoreversion recursesubdirs; Components: docs

Source: "C:\VTP\vc14\TerrainApps\Enviro\Release\Enviro.exe"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: main
Source: "C:\VTP\Installers\Enviro.xml"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: main
Source: "C:\VTP\TerrainApps\Enviro\Docs\*"; DestDir: "{app}\Docs\Enviro"; Flags: ignoreversion recursesubdirs; Components: docs

Source: "C:\VTP\vc14\TerrainApps\VTBuilder\Release\VTBuilder.exe"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: main
Source: "C:\VTP\Installers\VTBuilder.xml"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: main
Source: "C:\VTP\TerrainApps\VTBuilder\Docs\*"; DestDir: "{app}\Docs\VTBuilder"; Flags: ignoreversion recursesubdirs; Components: docs

Source: "C:\VTP\vc14\TerrainApps\Simple\Release\Simple.exe"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: main

; Common to all documentation
Source: "C:\VTP\TerrainApps\docs.css"; DestDir: "{app}\Docs"; Flags: ignoreversion recursesubdirs; Components: docs

; Translation files
Source: "C:\VTP\i18n\*"; DestDir: "{app}\Apps"; Excludes: "*.po"; Flags: ignoreversion recursesubdirs; Components: main

; Core Data
Source: "G:\Data-Distro\*"; DestDir: "{app}\Data"; Flags: ignoreversion recursesubdirs; Components: data

; overview docs
Source: "C:\VTP\Docs\*"; DestDir: "{app}\Docs"; Flags: ignoreversion recursesubdirs; Components: docs

; Projection Stuff
Source: "C:\APIs\gdal-2.0.0\data\*"; DestDir: "{app}\GDAL-data"; Flags: ignoreversion; Components: proj
Source: "C:\APIs\proj-4.9.1\nad\*"; DestDir: "{app}\PROJ4-data"; Flags: ignoreversion; Components: proj

; DLLs
Source: "C:\APIs\bzip2-1.0.6\Release\libbz2.dll"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: dlls
Source: "C:\APIs\gdal-2.0.0\bin-release\gdal200-vc14.dll"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: dlls
Source: "C:\APIs\gdal-2.0.0\bin-release\proj.dll"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: dlls
Source: "C:\APIs\gdal-2.0.0\bin-release\*.exe"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: dlls
Source: "C:\APIs\curl-7.44.0\vc14\lib\Release\libcurl.dll"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: dlls
Source: "C:\APIs\lpng1618\vc14\Release\libpng16.dll"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: dlls
Source: "C:\APIs\lpng1618\vc14\Release\zlib1.dll"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: dlls
;Source: "C:\APIs\netcdf-3.6.1-1-bin\bin\netcdf.dll"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: dlls
Source: "C:\APIs\OpenSceneGraph-3.4.0\build\bin-rel-only\*.dll"; DestDir: "{app}\Apps"; Flags: ignoreversion recursesubdirs; Components: dlls
Source: "C:\APIs\wxWidgets-3.0.2\lib\vc_dll\*u_*.dll"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: dlls
;Source: "C:\APIs\expat-2.0.1\win32\bin\Release\libexpat.dll"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: dlls
Source: "C:\APIs\openssl-1.0.2d-install\bin\*.dll"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: dlls

; DAE plugin might want this:
;Source: "C:\APIs\Collada_DOM_2.2\dom\external-libs\libxml2\win32\lib\libxml2.dll"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: dlls
 
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\Documentation"; Filename: "{app}\Docs\index.html"
;Name: "{group}\BExtractor"; Filename: "{app}\Apps\BExtractor.exe"; WorkingDir: "{app}\Apps"
Name: "{group}\CManager"; Filename: "{app}\Apps\CManager.exe"; WorkingDir: "{app}\Apps"
Name: "{group}\Enviro"; Filename: "{app}\Apps\Enviro.exe"; WorkingDir: "{app}\Apps"
Name: "{group}\VTBuilder"; Filename: "{app}\Apps\VTBuilder.exe"; WorkingDir: "{app}\Apps"
Name: "{group}\Simple test - in window"; Filename: "{app}\Apps\Simple.exe"; Parameters: "--window 100 100 800 600"; WorkingDir: "{app}\Apps"
Name: "{group}\Simple test - full screen"; Filename: "{app}\Apps\Simple.exe"; Parameters: "--screen 0"; WorkingDir: "{app}\Apps"
Name: "{group}\Uninstall VTP Software"; Filename: "{uninstallexe}"

