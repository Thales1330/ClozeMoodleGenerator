##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=ClozeMoodleGenerator
ConfigurationName      :=Release
WorkspaceConfiguration := $(ConfigurationName)
WorkspacePath          :=C:/Users/Pichau/Documents/GitHub/ClozeMoodleGenerator
ProjectPath            :=C:/Users/Pichau/Documents/GitHub/ClozeMoodleGenerator/ClozeMoodleGenerator
IntermediateDirectory  :=../build-$(ConfigurationName)/ClozeMoodleGenerator
OutDir                 :=../build-$(ConfigurationName)/ClozeMoodleGenerator
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Pichau
Date                   :=02/05/2021
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=C:/TDM-GCC-32/bin/g++.exe
SharedObjectLinkerName :=C:/TDM-GCC-32/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=..\build-$(ConfigurationName)\bin\$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)NDEBUG $(PreprocessorSwitch)UNICODE 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
RcCmpOptions           := $(shell wx-config --rcflags)
RcCompilerName         :=C:/TDM-GCC-32/bin/windres.exe
LinkOptions            :=  $(shell wx-config --libs std,stc,webview) -static -limm32
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)C:\Users\Pichau\AppData\Local\Programs\Python\Python39-32\include $(IncludeSwitch)C:\Users\thale\AppData\Local\Programs\Python\Python39-32\include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)python39 
ArLibs                 :=  "python39" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)C:\Users\Pichau\AppData\Local\Programs\Python\Python39-32\libs $(LibraryPathSwitch)C:\Users\thale\AppData\Local\Programs\Python\Python39-32\libs 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/TDM-GCC-32/bin/ar.exe rcu
CXX      := C:/TDM-GCC-32/bin/g++.exe
CC       := C:/TDM-GCC-32/bin/gcc.exe
CXXFLAGS :=  -O2 -std=gnu++17 -Wall $(shell wx-config --cflags) $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/TDM-GCC-32/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
WXWIN:=C:\wxWidgets-3.1.5
WXCFG:=gcc_lib\mswu
Objects0=../build-$(ConfigurationName)/ClozeMoodleGenerator/wxcrafter.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/ClozeMoodleGenerator/ExportClose.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/ClozeMoodleGenerator/HTMLPreview.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/ClozeMoodleGenerator/main.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/ClozeMoodleGenerator/XMLParser.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/ClozeMoodleGenerator/MainFrame.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/ClozeMoodleGenerator/wxcrafter_bitmaps.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/ClozeMoodleGenerator/win_resources.rc$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): ../build-$(ConfigurationName)/ClozeMoodleGenerator/.d $(Objects) 
	@if not exist "..\build-$(ConfigurationName)\ClozeMoodleGenerator" mkdir "..\build-$(ConfigurationName)\ClozeMoodleGenerator"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@if not exist "..\build-$(ConfigurationName)\ClozeMoodleGenerator" mkdir "..\build-$(ConfigurationName)\ClozeMoodleGenerator"
	@if not exist ""..\build-$(ConfigurationName)\bin"" mkdir ""..\build-$(ConfigurationName)\bin""

../build-$(ConfigurationName)/ClozeMoodleGenerator/.d:
	@if not exist "..\build-$(ConfigurationName)\ClozeMoodleGenerator" mkdir "..\build-$(ConfigurationName)\ClozeMoodleGenerator"

PreBuild:


##
## Objects
##
../build-$(ConfigurationName)/ClozeMoodleGenerator/wxcrafter.cpp$(ObjectSuffix): wxcrafter.cpp ../build-$(ConfigurationName)/ClozeMoodleGenerator/wxcrafter.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Pichau/Documents/GitHub/ClozeMoodleGenerator/ClozeMoodleGenerator/wxcrafter.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/ClozeMoodleGenerator/wxcrafter.cpp$(DependSuffix): wxcrafter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/ClozeMoodleGenerator/wxcrafter.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/ClozeMoodleGenerator/wxcrafter.cpp$(DependSuffix) -MM wxcrafter.cpp

../build-$(ConfigurationName)/ClozeMoodleGenerator/wxcrafter.cpp$(PreprocessSuffix): wxcrafter.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/ClozeMoodleGenerator/wxcrafter.cpp$(PreprocessSuffix) wxcrafter.cpp

../build-$(ConfigurationName)/ClozeMoodleGenerator/ExportClose.cpp$(ObjectSuffix): ExportClose.cpp ../build-$(ConfigurationName)/ClozeMoodleGenerator/ExportClose.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Pichau/Documents/GitHub/ClozeMoodleGenerator/ClozeMoodleGenerator/ExportClose.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ExportClose.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/ClozeMoodleGenerator/ExportClose.cpp$(DependSuffix): ExportClose.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/ClozeMoodleGenerator/ExportClose.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/ClozeMoodleGenerator/ExportClose.cpp$(DependSuffix) -MM ExportClose.cpp

../build-$(ConfigurationName)/ClozeMoodleGenerator/ExportClose.cpp$(PreprocessSuffix): ExportClose.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/ClozeMoodleGenerator/ExportClose.cpp$(PreprocessSuffix) ExportClose.cpp

../build-$(ConfigurationName)/ClozeMoodleGenerator/HTMLPreview.cpp$(ObjectSuffix): HTMLPreview.cpp ../build-$(ConfigurationName)/ClozeMoodleGenerator/HTMLPreview.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Pichau/Documents/GitHub/ClozeMoodleGenerator/ClozeMoodleGenerator/HTMLPreview.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/HTMLPreview.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/ClozeMoodleGenerator/HTMLPreview.cpp$(DependSuffix): HTMLPreview.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/ClozeMoodleGenerator/HTMLPreview.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/ClozeMoodleGenerator/HTMLPreview.cpp$(DependSuffix) -MM HTMLPreview.cpp

../build-$(ConfigurationName)/ClozeMoodleGenerator/HTMLPreview.cpp$(PreprocessSuffix): HTMLPreview.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/ClozeMoodleGenerator/HTMLPreview.cpp$(PreprocessSuffix) HTMLPreview.cpp

../build-$(ConfigurationName)/ClozeMoodleGenerator/main.cpp$(ObjectSuffix): main.cpp ../build-$(ConfigurationName)/ClozeMoodleGenerator/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Pichau/Documents/GitHub/ClozeMoodleGenerator/ClozeMoodleGenerator/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/ClozeMoodleGenerator/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/ClozeMoodleGenerator/main.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/ClozeMoodleGenerator/main.cpp$(DependSuffix) -MM main.cpp

../build-$(ConfigurationName)/ClozeMoodleGenerator/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/ClozeMoodleGenerator/main.cpp$(PreprocessSuffix) main.cpp

../build-$(ConfigurationName)/ClozeMoodleGenerator/XMLParser.cpp$(ObjectSuffix): XMLParser.cpp ../build-$(ConfigurationName)/ClozeMoodleGenerator/XMLParser.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Pichau/Documents/GitHub/ClozeMoodleGenerator/ClozeMoodleGenerator/XMLParser.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/XMLParser.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/ClozeMoodleGenerator/XMLParser.cpp$(DependSuffix): XMLParser.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/ClozeMoodleGenerator/XMLParser.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/ClozeMoodleGenerator/XMLParser.cpp$(DependSuffix) -MM XMLParser.cpp

../build-$(ConfigurationName)/ClozeMoodleGenerator/XMLParser.cpp$(PreprocessSuffix): XMLParser.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/ClozeMoodleGenerator/XMLParser.cpp$(PreprocessSuffix) XMLParser.cpp

../build-$(ConfigurationName)/ClozeMoodleGenerator/MainFrame.cpp$(ObjectSuffix): MainFrame.cpp ../build-$(ConfigurationName)/ClozeMoodleGenerator/MainFrame.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Pichau/Documents/GitHub/ClozeMoodleGenerator/ClozeMoodleGenerator/MainFrame.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/ClozeMoodleGenerator/MainFrame.cpp$(DependSuffix): MainFrame.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/ClozeMoodleGenerator/MainFrame.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/ClozeMoodleGenerator/MainFrame.cpp$(DependSuffix) -MM MainFrame.cpp

../build-$(ConfigurationName)/ClozeMoodleGenerator/MainFrame.cpp$(PreprocessSuffix): MainFrame.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/ClozeMoodleGenerator/MainFrame.cpp$(PreprocessSuffix) MainFrame.cpp

../build-$(ConfigurationName)/ClozeMoodleGenerator/wxcrafter_bitmaps.cpp$(ObjectSuffix): wxcrafter_bitmaps.cpp ../build-$(ConfigurationName)/ClozeMoodleGenerator/wxcrafter_bitmaps.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Pichau/Documents/GitHub/ClozeMoodleGenerator/ClozeMoodleGenerator/wxcrafter_bitmaps.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/ClozeMoodleGenerator/wxcrafter_bitmaps.cpp$(DependSuffix): wxcrafter_bitmaps.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/ClozeMoodleGenerator/wxcrafter_bitmaps.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/ClozeMoodleGenerator/wxcrafter_bitmaps.cpp$(DependSuffix) -MM wxcrafter_bitmaps.cpp

../build-$(ConfigurationName)/ClozeMoodleGenerator/wxcrafter_bitmaps.cpp$(PreprocessSuffix): wxcrafter_bitmaps.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/ClozeMoodleGenerator/wxcrafter_bitmaps.cpp$(PreprocessSuffix) wxcrafter_bitmaps.cpp

../build-$(ConfigurationName)/ClozeMoodleGenerator/win_resources.rc$(ObjectSuffix): win_resources.rc
	$(RcCompilerName) -i "C:/Users/Pichau/Documents/GitHub/ClozeMoodleGenerator/ClozeMoodleGenerator/win_resources.rc" $(RcCmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/win_resources.rc$(ObjectSuffix) $(RcIncludePath)

-include ../build-$(ConfigurationName)/ClozeMoodleGenerator//*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


