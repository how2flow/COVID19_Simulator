# COVID19_Simulator

***
## About Program
**Be sure to read it.**

This program is based on the coronavirus that hit the world in 2020.

It's a demo version that allows you to easily see how far the virus spreads, depending on the social distancing stage.

This program is expressed as (covid-19) negative - blue (covid-19) positive - red recovery (green).

The program lasts up to 30 seconds and allows you to randomly select people in their 0s and 90s for statistics.

See **how_to_use_COVID19_Simulator.txt** for instructions on **how to use it.**

You can modify with VisualStudio2015(ver.community)

You can also change the dlg and resources.

**Please leave a source if you copy it or quote it elsewhere.**

**Subsequent descriptions related to the source and configuration files. Reading is a choice.**

***

## MFC Library: COVID19_Simulator Project Overview

The application wizard created this COVID19_Simulator application. 

This application not only shows the basic usage of MFCs, but also provides a basic structure for creating applications.

**(only source files due to capacity issues based on ver 0.0.1).**

For each file that configures the COVID19_Simulator application.

Contains a summary description. **(Only upload source files based on ver 0.0.1.)**


**If manufactured in MFC environment**

- COVID19_Simulator.vcxproj

The default project file for a VC++ project created using the Application Wizard. 

Contains information about the Visual C++ version that generated the file and information about the platform, configuration, and project features 

that you selected using the Application Wizard.

- COVID19_Simulator.vcxproj.filters

Filter files for VC++ projects created using the Application Wizard. 

This file contains information about the connection between the files in the project and the filters. 

These links are used by IDE on certain nodes to display files grouped with similar extensions. 

For example, the ".cpp" file is associated with the "source file" filter.

- COVID19_Simulator.h

The default header file for that application.

It contains other project specific headers, including resource.h, and the CCOVID19_SimulatorApp application class is declared.

- COVID19_Simulator.cpp

This is the default application source file containing the application class CCOVID19_SimulatorApp.

- COVID19_Simulator.rc

List of all Microsoft Windows resources that the program uses. This includes icons, bitmaps, and cursors stored in the RES subdirectory. 

This file can be edited directly from Microsoft Visual C++. Project resources are located in 1042.

- res\COVID19_Simulator.ico

An icon file, used as an icon for an application. This icon is included by the default resource file COVID19_Simulator.rc.

- res\COVID19_Simulator.rc2

This file contains resources edited by tools other than Microsoft Visual C++.

All resources that cannot be edited with the Resource Editor must be placed in this file.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Main Frame Window:

Includes standard MFC interfaces.

MainFrm.h, MainFrm.cpp

This file contains the frame class CMainFrame.

It is derived from CFrameWnd and controls all SDI frame functions.

res\Toolbar.bmp

This bitmap file is used to create a Go-board image of the toolbar.

The initial toolbar and status bar are created in the CMainFrame class. 

Edit this toolbar bitmap as the Resource Editor and add a toolbar button by updating the IDR_MAINFRAME TOOLBAR array in COVID19_Simulator.rc.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Create one document format and one view in the application wizard.

COVID19_SimulatorDoc.h, COVID19_SimulatorDoc.cpp  

This file contains the CCOVID19_SimulatorDoc class. 

Edit this file to add special document data and implement file storage and loading via CCOVID19_SimulatorDoc::Serialize.

COVID19_SimulatorView.h, COVID19_SimulatorView.cpp 

This file contains the CCOVID19_SimulatorView class.

The CCOVID19_SimulatorView object is used to view the CCOVID19_SimulatorDoc object.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Other features:

ActiveX controls

The application supports ActiveX controls.

Print and print preview support

You can call a member function from a CView class in the MFC library to generate print, print settings, and print preview command codes in the application wizard.

Windows Socket

Allows applications to establish communication over TCP/IP networks.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Other standard files:

- StdAfx.h, StdAfx.cpp

This file is used to build precompiled header (PCH) file COVID19_Simulator.pch and precompiled format (PCT) file Stdafx.obj.

- Resource.h

A standard header file that defines a new resource ID. Read and update this file in Microsoft Visual C++.

- COVID19_Simulator.manifest

Application manifest files are used in Windows XP to describe application dependencies for specific versions of Side-by-Side assemblies. 

The loader uses this information to load the appropriate assembly from the assembly cache or from private in the application. 

An application manifest is an external .manifest file installed in a folder, such as an application executable, 

that can be included for redistribution or in a resource-type executable.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Other notes:

The **"TODO:"** used by the application wizard indicates the portion of the source code that the user must add or customize.

For applications that use MFC on shared DLLs, you do not need to redistribute MFC DLLs. 

If the application uses a different language than the locale of the operating system, you must also redistribute the corresponding localized resource, mfc110XXX.DLL.

For more information on these two topics, see the Redistribution of Visual C++ Applications section in the MSDN documentation.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

***
**If you think the program is good, please recommend and share it. It is also good for basic and educational purposes of MFC.**
