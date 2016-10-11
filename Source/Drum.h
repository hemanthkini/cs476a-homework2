//----------------------------------------------------------
//
// Code generated with Faust 0.9.90 (http://faust.grame.fr)
//----------------------------------------------------------

/* link with  */
#include <math.h>
#ifndef FAUSTPOWER
#define FAUSTPOWER
#include <cmath>
template <int N> inline int faustpower(int x)              { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline int faustpower<0>(int x)            { return 1; }
template <> 	 inline int faustpower<1>(int x)            { return x; }
template <> 	 inline int faustpower<2>(int x)            { return x*x; }
template <int N> inline float faustpower(float x)            { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline float faustpower<0>(float x)          { return 1; }
template <> 	 inline float faustpower<1>(float x)          { return x; }
template <> 	 inline float faustpower<2>(float x)          { return x*x; }
#endif
// Music 256a / CS 476a | fall 2016
// CCRMA, Stanford University
//
// Author: Romain Michon (rmichonATccrmaDOTstanfordDOTedu)
// Description: Simple Faust architecture file to easily integrate a Faust DSP module
// in a JUCE project

// needed by any Faust arch file
/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 3 of
	the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

 ************************************************************************
 ************************************************************************/
 
#ifndef __misc__
#define __misc__

#include <algorithm>
#include <map>
#include <string.h>
#include <stdlib.h>

/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 3 of
	the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

 ************************************************************************
 ************************************************************************/
 
#ifndef __meta__
#define __meta__

struct Meta
{
    virtual void declare(const char* key, const char* value) = 0;
    virtual ~Meta() {};
};

#endif

using std::max;
using std::min;

struct XXXX_Meta : std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key]=value; }
};

struct MY_Meta : Meta, std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key]=value; }
};

inline int lsr(int x, int n)	{ return int(((unsigned int)x) >> n); }

inline int int2pow2(int x)		{ int r = 0; while ((1<<r) < x) r++; return r; }

inline long lopt(char* argv[], const char* name, long def)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return atoi(argv[i+1]);
	return def;
}

inline bool isopt(char* argv[], const char* name)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return true;
	return false;
}

inline const char* lopts(char* argv[], const char* name, const char* def)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return argv[i+1];
	return def;
}

#endif


// allows to control a Faust DSP module in a simple manner by using parameter's path
/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/

#ifndef FAUST_MAPUI_H
#define FAUST_MAPUI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <vector>
#include <map>
#include <string>

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2016 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/
 
#ifndef FAUST_UI_H
#define FAUST_UI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/*******************************************************************************
 * UI : Faust User Interface
 * This abstract class contains only the method that the faust compiler can
 * generate to describe a DSP interface.
 ******************************************************************************/

class UI
{

    public:

        UI() {}

        virtual ~UI() {}

        // -- widget's layouts

        virtual void openTabBox(const char* label) = 0;
        virtual void openHorizontalBox(const char* label) = 0;
        virtual void openVerticalBox(const char* label) = 0;
        virtual void closeBox() = 0;

        // -- active widgets

        virtual void addButton(const char* label, FAUSTFLOAT* zone) = 0;
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) = 0;
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT*, const char*, const char*) {}
};

//----------------------------------------------------------------
//  Generic decorator
//----------------------------------------------------------------

class DecoratorUI : public UI
{
    protected:
    
        UI* fUI;

    public:
    
        DecoratorUI(UI* ui = 0):fUI(ui)
        {}

        virtual ~DecoratorUI() { delete fUI; }

        // -- widget's layouts
        virtual void openTabBox(const char* label)          { fUI->openTabBox(label); }
        virtual void openHorizontalBox(const char* label)   { fUI->openHorizontalBox(label); }
        virtual void openVerticalBox(const char* label)     { fUI->openVerticalBox(label); }
        virtual void closeBox()                             { fUI->closeBox(); }

        // -- active widgets
        virtual void addButton(const char* label, FAUSTFLOAT* zone)         { fUI->addButton(label, zone); }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)    { fUI->addCheckButton(label, zone); }
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
            { fUI->addVerticalSlider(label, zone, init, min, max, step); }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 	
            { fUI->addHorizontalSlider(label, zone, init, min, max, step); }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 			
            { fUI->addNumEntry(label, zone, init, min, max, step); }

        // -- passive widgets	
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
            { fUI->addHorizontalBargraph(label, zone, min, max); }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
            { fUI->addVerticalBargraph(label, zone, min, max); }

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val) { fUI->declare(zone, key, val); }

};

#endif
/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/

#ifndef FAUST_PATHBUILDER_H
#define FAUST_PATHBUILDER_H

#include <vector>
#include <string>
#include <algorithm>

/*******************************************************************************
 * PathBuilder : Faust User Interface
 * Helper class to build complete hierarchical path for UI items.
 ******************************************************************************/

class PathBuilder
{

    protected:
    
        std::vector<std::string> fControlsLevel;
       
    public:
    
        PathBuilder() {}
        virtual ~PathBuilder() {}
    
        std::string buildPath(const std::string& label) 
        {
            std::string res = "/";
            for (size_t i = 0; i < fControlsLevel.size(); i++) {
                res += fControlsLevel[i];
                res += "/";
            }
            res += label;
            replace(res.begin(), res.end(), ' ', '_');
            return res;
        }
    
};

#endif  // FAUST_PATHBUILDER_H

/*******************************************************************************
 * MapUI : Faust User Interface
 * This class creates a map of complete hierarchical path and zones for each UI items.
 ******************************************************************************/

class MapUI : public UI, public PathBuilder
{
    
    protected:
    
        // Complete path map
        std::map<std::string, FAUSTFLOAT*> fPathZoneMap;
    
        // Label zone map
        std::map<std::string, FAUSTFLOAT*> fLabelZoneMap;
    
    public:
        
        MapUI() {};
        virtual ~MapUI() {};
        
        // -- widget's layouts
        void openTabBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void openHorizontalBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void openVerticalBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void closeBox()
        {
            fControlsLevel.pop_back();
        }
        
        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        
        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        
        // -- metadata declarations
        void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {}
        
        // set/get
        void setParamValue(const std::string& path, float value)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                *fPathZoneMap[path] = value;
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                *fLabelZoneMap[path] = value;
            }
        }
        
        float getParamValue(const std::string& path)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                return *fPathZoneMap[path];
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                return *fLabelZoneMap[path];
            } else {
                return 0.;
            }
        }
    
        // map access 
        std::map<std::string, FAUSTFLOAT*>& getMap() { return fPathZoneMap; }
        
        int getParamsCount() { return fPathZoneMap.size(); }
        
        std::string getParamAdress(int index) 
        { 
            std::map<std::string, FAUSTFLOAT*>::iterator it = fPathZoneMap.begin();
            while (index-- > 0 && it++ != fPathZoneMap.end()) {}
            return (*it).first;
        }
};

#endif // FAUST_MAPUI_H

// needed by any Faust arch file
/************************************************************************
    IMPORTANT NOTE : this file contains two clearly delimited sections :
    the ARCHITECTURE section (in two parts) and the USER section. Each section
    is governed by its own copyright and license. Please check individually
    each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.

 ************************************************************************
 ************************************************************************/
 
/******************************************************************************
*******************************************************************************

								FAUST DSP

*******************************************************************************
*******************************************************************************/

#ifndef __dsp__
#define __dsp__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

class UI;
struct Meta;

/**
* Signal processor definition.
*/

class dsp {

    public:

        dsp() {}
        virtual ~dsp() {}

        /* Return instance number of audio inputs */
        virtual int getNumInputs() = 0;
    
        /* Return instance number of audio outputs */
        virtual int getNumOutputs() = 0;
    
        /**
         * Trigger the UI* parameter with instance specific calls
         * to 'addBtton', 'addVerticalSlider'... in order to build the UI.
         *
         * @param ui_interface - the UI* user interface builder
         */
        virtual void buildUserInterface(UI* ui_interface) = 0;
    
        /* Returns the sample rate currently used by the instance */
        virtual int getSampleRate() = 0;
    
        /** Global init, calls the following methods :
         * - static class 'classInit' : static table initialisation
         * - 'instanceInit' : constants and instance table initialisation
         *
         * @param samplingRate - the sampling rate in Herz
         */
        virtual void init(int samplingRate) = 0;
    
        /** Init instance state
         *
         * @param samplingRate - the sampling rate in Herz
         */
        virtual void instanceInit(int samplingRate) = 0;
    
        /** Init instance constant state
         *
         * @param samplingRate - the sampling rate in Herz
         */
        virtual void instanceConstants(int samplingRate) = 0;
    
        /* Init default control parameters values */
        virtual void instanceResetUserInterface() = 0;
    
        /* Init instance state (delay lines...) */
        virtual void instanceClear() = 0;
    
        /**  
         * Return a clone of the instance.
         *
         * @return a copy of the instance on success, otherwise a null pointer.
         */
        virtual dsp* clone() = 0;
    
        /**
         * Trigger the Meta* parameter with instance specific calls to 'declare' (key, value metadata).
         *
         * @param m - the Meta* meta user
         */
        virtual void metadata(Meta* m) = 0;
    
        /**
         * DSP instance computation, to be called with sucessive in/out audio buffers.
         *
         * @param count - the nomber of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         *
         */
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
    
        /**
         * DSP instance computation : alternative method to be used by subclasses.
         *
         * @param date_usec - the timestamp in microsec given by audio driver.
         * @param count - the nomber of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         *
         */
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

/**
 * Generic DSP decorator.
 */

class decorator_dsp : public dsp {

    protected:

        dsp* fDSP;

    public:

        decorator_dsp(dsp* dsp = 0):fDSP(dsp) {}
        virtual ~decorator_dsp() { delete fDSP; }

        virtual int getNumInputs() { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP->getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { fDSP->buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return fDSP->getSampleRate(); }
        virtual void init(int samplingRate) { fDSP->init(samplingRate); }
        virtual void instanceInit(int samplingRate) { fDSP->instanceInit(samplingRate); }
        virtual void instanceConstants(int samplingRate) { fDSP->instanceConstants(samplingRate); }
        virtual void instanceResetUserInterface() { fDSP->instanceResetUserInterface(); }
        virtual void instanceClear() { fDSP->instanceClear(); }
        virtual decorator_dsp* clone() { return new decorator_dsp(fDSP->clone()); }
        virtual void metadata(Meta* m) { return fDSP->metadata(m); }
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(count, inputs, outputs); }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(date_usec, count, inputs, outputs); }
       
};

/**
 * On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
 * flags to avoid costly denormals.
 */

#ifdef __SSE__
    #include <xmmintrin.h>
    #ifdef __SSE2__
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
    #else
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
    #endif
#else
    #define AVOIDDENORMALS
#endif

#endif

// tags used by the Faust compiler to paste the generated c++ code
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif  


#ifndef FAUSTCLASS 
#define FAUSTCLASS Drum
#endif

class Drum : public dsp {
  private:
	int 	iVec0[2];
	FAUSTFLOAT 	fslider0;
	float 	fRec0[2];
	float 	fConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	float 	fRec2[2];
	FAUSTFLOAT 	fbutton0;
	float 	fVec1[2];
	float 	fRec3[2];
	float 	fConst2;
	float 	fConst3;
	float 	fConst4;
	FAUSTFLOAT 	fslider3;
	float 	fRec6[2];
	float 	fConst5;
	float 	fRec4[2];
	float 	fRec5[2];
	float 	fRec7[2];
	float 	fConst6;
	float 	fRec8[2];
	float 	fRec9[2];
	float 	fRec10[2];
	float 	fConst7;
	float 	fRec11[2];
	float 	fRec12[2];
	float 	fRec13[2];
	float 	fConst8;
	float 	fRec14[2];
	float 	fRec15[2];
	float 	fRec16[2];
	float 	fConst9;
	float 	fRec17[2];
	float 	fRec18[2];
	float 	fRec19[2];
	float 	fConst10;
	float 	fRec20[2];
	float 	fRec21[2];
	float 	fConst11;
	float 	fRec22[2];
	float 	fConst12;
	float 	fRec23[2];
	float 	fRec24[2];
	FAUSTFLOAT 	fslider4;
	float 	fRec25[2];
	float 	fRec1[3];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("signal.lib/name", "Faust Signal Routing Library");
		m->declare("signal.lib/version", "0.0");
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("filter.lib/version", "2.0");
		m->declare("math.lib/name", "Faust Math Library");
		m->declare("math.lib/version", "2.0");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("synth.lib/name", "Faust Synthesizer Library");
		m->declare("synth.lib/version", "0.0");
		m->declare("basic.lib/name", "Faust Basic Element Library");
		m->declare("basic.lib/version", "0.0");
		m->declare("envelope.lib/name", "Faust Envelope Library");
		m->declare("envelope.lib/version", "0.0");
		m->declare("envelope.lib/author", "GRAME");
		m->declare("envelope.lib/copyright", "GRAME");
		m->declare("envelope.lib/license", "LGPL with exception");
		m->declare("miscoscillator.lib/name", "Faust Oscillator Library");
		m->declare("miscoscillator.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 1; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(1.92e+05f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (3.1415927f / fConst0);
		fConst2 = (0.01f * fConst0);
		fConst3 = (5.882353f / fConst0);
		fConst4 = (1e+02f / fConst0);
		fConst5 = (19.917698f / fConst0);
		fConst6 = (17.592918f / fConst0);
		fConst7 = (13.446016f / fConst0);
		fConst8 = (11.623893f / fConst0);
		fConst9 = (10.053097f / fConst0);
		fConst10 = (8.168141f / fConst0);
		fConst11 = (0.18f * fConst0);
		fConst12 = (6.2831855f / fConst0);
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 4.4e+02f;
		fslider1 = 0.5f;
		fslider2 = 0.5f;
		fbutton0 = 0.0;
		fslider3 = 1e+02f;
		fslider4 = 0.7f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iVec0[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<2; i++) fRec9[i] = 0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<2; i++) fRec16[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		for (int i=0; i<2; i++) fRec21[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<2; i++) fRec23[i] = 0;
		for (int i=0; i<2; i++) fRec24[i] = 0;
		for (int i=0; i<2; i++) fRec25[i] = 0;
		for (int i=0; i<3; i++) fRec1[i] = 0;
	}
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	virtual Drum* clone() {
		return new Drum();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("Inst");
		ui_interface->openHorizontalBox("FM");
		ui_interface->addHorizontalSlider("freq", &fslider3, 1e+02f, 1e+02f, 4e+02f, 0.01f);
		ui_interface->addHorizontalSlider("gain", &fslider4, 0.7f, 0.0f, 1.0f, 0.01f);
		ui_interface->addButton("gate", &fbutton0);
		ui_interface->addHorizontalSlider("harmonicdecay", &fslider2, 0.5f, 0.1f, 0.9f, 0.01f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("filter");
		ui_interface->addHorizontalSlider("filterfreq", &fslider0, 4.4e+02f, 1e+02f, 1e+03f, 0.01f);
		ui_interface->addHorizontalSlider("filterq", &fslider1, 0.5f, 0.5f, 3.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		float 	fSlow0 = (0.001f * float(fslider0));
		float 	fSlow1 = (1.0f / float(fslider1));
		float 	fSlow2 = (0.001f * float(fslider2));
		float 	fSlow3 = float(fbutton0);
		float 	fSlow4 = (0.001f * float(fslider3));
		float 	fSlow5 = (0.001f * float(fslider4));
		FAUSTFLOAT* output0 = output[0];
		for (int i=0; i<count; i++) {
			iVec0[0] = 1;
			fRec0[0] = (fSlow0 + (0.999f * fRec0[1]));
			float fTemp0 = tanf((fConst1 * fRec0[0]));
			float fTemp1 = (1.0f / fTemp0);
			float fTemp2 = (1 + ((fSlow1 + fTemp1) / fTemp0));
			fRec2[0] = (fSlow2 + (0.999f * fRec2[1]));
			float fTemp3 = (1 - (0.85714287f * fRec2[0]));
			float fTemp4 = (fConst0 * (0.01f + (0.17f * fTemp3)));
			fVec1[0] = fSlow3;
			int iTemp5 = int((((fSlow3 - fVec1[1]) == 1) > 0));
			fRec3[0] = ((iTemp5)?0:min(fTemp4, (1 + fRec3[1])));
			int iTemp6 = int((fRec3[0] < fConst2));
			fRec6[0] = (fSlow4 + (0.999f * fRec6[1]));
			float fTemp7 = (fConst5 * fRec6[0]);
			float fTemp8 = cosf(fTemp7);
			float fTemp9 = sinf(fTemp7);
			fRec4[0] = ((fRec5[1] * fTemp9) + (fRec4[1] * fTemp8));
			fRec5[0] = ((1 + ((fRec5[1] * fTemp8) + (fRec4[1] * (0 - fTemp9)))) - iVec0[1]);
			float fTemp10 = (1 - (0.71428573f * fRec2[0]));
			float fTemp11 = (fConst0 * (0.01f + (0.17f * fTemp10)));
			fRec7[0] = ((iTemp5)?0:min(fTemp11, (1 + fRec7[1])));
			int iTemp12 = int((fRec7[0] < fConst2));
			float fTemp13 = (fConst6 * fRec6[0]);
			float fTemp14 = cosf(fTemp13);
			float fTemp15 = sinf(fTemp13);
			fRec8[0] = ((fRec9[1] * fTemp15) + (fRec8[1] * fTemp14));
			fRec9[0] = ((1 + ((fRec9[1] * fTemp14) + (fRec8[1] * (0 - fTemp15)))) - iVec0[1]);
			float fTemp16 = (1 - (0.5714286f * fRec2[0]));
			float fTemp17 = (fConst0 * (0.01f + (0.17f * fTemp16)));
			fRec10[0] = ((iTemp5)?0:min(fTemp17, (1 + fRec10[1])));
			int iTemp18 = int((fRec10[0] < fConst2));
			float fTemp19 = (fConst7 * fRec6[0]);
			float fTemp20 = cosf(fTemp19);
			float fTemp21 = sinf(fTemp19);
			fRec11[0] = ((fRec12[1] * fTemp21) + (fRec11[1] * fTemp20));
			fRec12[0] = ((1 + ((fRec12[1] * fTemp20) + (fRec11[1] * (0 - fTemp21)))) - iVec0[1]);
			float fTemp22 = (1 - (0.42857143f * fRec2[0]));
			float fTemp23 = (fConst0 * (0.01f + (0.17f * fTemp22)));
			fRec13[0] = ((iTemp5)?0:min(fTemp23, (1 + fRec13[1])));
			int iTemp24 = int((fRec13[0] < fConst2));
			float fTemp25 = (fConst8 * fRec6[0]);
			float fTemp26 = cosf(fTemp25);
			float fTemp27 = sinf(fTemp25);
			fRec14[0] = ((fRec15[1] * fTemp27) + (fRec14[1] * fTemp26));
			fRec15[0] = ((1 + ((fRec15[1] * fTemp26) + (fRec14[1] * (0 - fTemp27)))) - iVec0[1]);
			float fTemp28 = (1 - (0.2857143f * fRec2[0]));
			float fTemp29 = (fConst0 * (0.01f + (0.17f * fTemp28)));
			fRec16[0] = ((iTemp5)?0:min(fTemp29, (1 + fRec16[1])));
			int iTemp30 = int((fRec16[0] < fConst2));
			float fTemp31 = (fConst9 * fRec6[0]);
			float fTemp32 = cosf(fTemp31);
			float fTemp33 = sinf(fTemp31);
			fRec17[0] = ((fRec18[1] * fTemp33) + (fRec17[1] * fTemp32));
			fRec18[0] = ((1 + ((fRec18[1] * fTemp32) + (fRec17[1] * (0 - fTemp33)))) - iVec0[1]);
			float fTemp34 = (1 - (0.14285715f * fRec2[0]));
			float fTemp35 = (fConst0 * (0.01f + (0.17f * fTemp34)));
			fRec19[0] = ((iTemp5)?0:min(fTemp35, (1 + fRec19[1])));
			int iTemp36 = int((fRec19[0] < fConst2));
			float fTemp37 = (fConst10 * fRec6[0]);
			float fTemp38 = cosf(fTemp37);
			float fTemp39 = sinf(fTemp37);
			fRec20[0] = ((fRec21[1] * fTemp39) + (fRec20[1] * fTemp38));
			fRec21[0] = ((1 + ((fRec21[1] * fTemp38) + (fRec20[1] * (0 - fTemp39)))) - iVec0[1]);
			fRec22[0] = ((iTemp5)?0:min(fConst11, (1 + fRec22[1])));
			int iTemp40 = int((fRec22[0] < fConst2));
			float fTemp41 = (fConst12 * fRec6[0]);
			float fTemp42 = cosf(fTemp41);
			float fTemp43 = sinf(fTemp41);
			fRec23[0] = ((fRec24[1] * fTemp43) + (fRec23[1] * fTemp42));
			fRec24[0] = ((1 + ((fRec24[1] * fTemp42) + (fRec23[1] * (0 - fTemp43)))) - iVec0[1]);
			fRec25[0] = (fSlow5 + (0.999f * fRec25[1]));
			fRec1[0] = ((fRec25[0] * (((((((fRec23[0] * ((iTemp40)?((int((fRec22[0] < 0)))?0:((iTemp40)?(fConst4 * fRec22[0]):1)):((int((fRec22[0] < fConst11)))?(1 + (fConst3 * (fConst2 - fRec22[0]))):0))) + (0.9f * (fRec20[0] * ((iTemp36)?((int((fRec19[0] < 0)))?0:((iTemp36)?(fConst4 * fRec19[0]):1)):((int((fRec19[0] < fTemp35)))?(1 + (fConst3 * ((fConst2 - fRec19[0]) / fTemp34))):0))))) + (0.8f * (fRec17[0] * ((iTemp30)?((int((fRec16[0] < 0)))?0:((iTemp30)?(fConst4 * fRec16[0]):1)):((int((fRec16[0] < fTemp29)))?(1 + (fConst3 * ((fConst2 - fRec16[0]) / fTemp28))):0))))) + (0.7f * (fRec14[0] * ((iTemp24)?((int((fRec13[0] < 0)))?0:((iTemp24)?(fConst4 * fRec13[0]):1)):((int((fRec13[0] < fTemp23)))?(1 + (fConst3 * ((fConst2 - fRec13[0]) / fTemp22))):0))))) + (0.6f * (fRec11[0] * ((iTemp18)?((int((fRec10[0] < 0)))?0:((iTemp18)?(fConst4 * fRec10[0]):1)):((int((fRec10[0] < fTemp17)))?(1 + (fConst3 * ((fConst2 - fRec10[0]) / fTemp16))):0))))) + (0.5f * (fRec8[0] * ((iTemp12)?((int((fRec7[0] < 0)))?0:((iTemp12)?(fConst4 * fRec7[0]):1)):((int((fRec7[0] < fTemp11)))?(1 + (fConst3 * ((fConst2 - fRec7[0]) / fTemp10))):0))))) + (0.4f * (fRec4[0] * ((iTemp6)?((int((fRec3[0] < 0)))?0:((iTemp6)?(fConst4 * fRec3[0]):1)):((int((fRec3[0] < fTemp4)))?(1 + (fConst3 * ((fConst2 - fRec3[0]) / fTemp3))):0)))))) - (((fRec1[2] * (1 + ((fTemp1 - fSlow1) / fTemp0))) + (2 * (fRec1[1] * (1 - (1.0f / faustpower<2>(fTemp0)))))) / fTemp2));
			output0[i] = (FAUSTFLOAT)(0.5f * ((fRec1[0] + (fRec1[2] + (2.0f * fRec1[1]))) / fTemp2));
			// post processing
			fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
			fRec25[1] = fRec25[0];
			fRec24[1] = fRec24[0];
			fRec23[1] = fRec23[0];
			fRec22[1] = fRec22[0];
			fRec21[1] = fRec21[0];
			fRec20[1] = fRec20[0];
			fRec19[1] = fRec19[0];
			fRec18[1] = fRec18[0];
			fRec17[1] = fRec17[0];
			fRec16[1] = fRec16[0];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			fRec13[1] = fRec13[0];
			fRec12[1] = fRec12[0];
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			fRec9[1] = fRec9[0];
			fRec8[1] = fRec8[0];
			fRec7[1] = fRec7[0];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
			fRec6[1] = fRec6[0];
			fRec3[1] = fRec3[0];
			fVec1[1] = fVec1[0];
			fRec2[1] = fRec2[0];
			fRec0[1] = fRec0[0];
			iVec0[1] = iVec0[0];
		}
	}
};


