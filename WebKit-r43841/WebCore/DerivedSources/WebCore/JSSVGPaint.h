/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#ifndef JSSVGPaint_h
#define JSSVGPaint_h


#if ENABLE(SVG)

#include "JSSVGColor.h"

namespace WebCore {

class SVGPaint;

class JSSVGPaint : public JSSVGColor {
    typedef JSSVGColor Base;
public:
    JSSVGPaint(PassRefPtr<JSC::Structure>, PassRefPtr<SVGPaint>);
    static JSC::JSObject* createPrototype(JSC::ExecState*, JSC::JSGlobalObject*);
    virtual bool getOwnPropertySlot(JSC::ExecState*, const JSC::Identifier& propertyName, JSC::PropertySlot&);
    virtual const JSC::ClassInfo* classInfo() const { return &s_info; }
    static const JSC::ClassInfo s_info;

    static PassRefPtr<JSC::Structure> createStructure(JSC::JSValue prototype)
    {
        return JSC::Structure::create(prototype, JSC::TypeInfo(JSC::ObjectType));
    }

    static JSC::JSValue getConstructor(JSC::ExecState*);
};


class JSSVGPaintPrototype : public JSC::JSObject {
    typedef JSC::JSObject Base;
public:
    static JSC::JSObject* self(JSC::ExecState*, JSC::JSGlobalObject*);
    virtual const JSC::ClassInfo* classInfo() const { return &s_info; }
    static const JSC::ClassInfo s_info;
    virtual bool getOwnPropertySlot(JSC::ExecState*, const JSC::Identifier&, JSC::PropertySlot&);
    static PassRefPtr<JSC::Structure> createStructure(JSC::JSValue prototype)
    {
        return JSC::Structure::create(prototype, JSC::TypeInfo(JSC::ObjectType));
    }
    JSSVGPaintPrototype(PassRefPtr<JSC::Structure> structure) : JSC::JSObject(structure) { }
};

// Functions

JSC::JSValue JSC_HOST_CALL jsSVGPaintPrototypeFunctionSetUri(JSC::ExecState*, JSC::JSObject*, JSC::JSValue, const JSC::ArgList&);
JSC::JSValue JSC_HOST_CALL jsSVGPaintPrototypeFunctionSetPaint(JSC::ExecState*, JSC::JSObject*, JSC::JSValue, const JSC::ArgList&);
// Attributes

JSC::JSValue jsSVGPaintPaintType(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
JSC::JSValue jsSVGPaintUri(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
JSC::JSValue jsSVGPaintConstructor(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
// Constants

JSC::JSValue jsSVGPaintSVG_PAINTTYPE_UNKNOWN(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
JSC::JSValue jsSVGPaintSVG_PAINTTYPE_RGBCOLOR(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
JSC::JSValue jsSVGPaintSVG_PAINTTYPE_RGBCOLOR_ICCCOLOR(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
JSC::JSValue jsSVGPaintSVG_PAINTTYPE_NONE(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
JSC::JSValue jsSVGPaintSVG_PAINTTYPE_CURRENTCOLOR(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
JSC::JSValue jsSVGPaintSVG_PAINTTYPE_URI_NONE(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
JSC::JSValue jsSVGPaintSVG_PAINTTYPE_URI_CURRENTCOLOR(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
JSC::JSValue jsSVGPaintSVG_PAINTTYPE_URI_RGBCOLOR(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
JSC::JSValue jsSVGPaintSVG_PAINTTYPE_URI_RGBCOLOR_ICCCOLOR(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
JSC::JSValue jsSVGPaintSVG_PAINTTYPE_URI(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);

} // namespace WebCore

#endif // ENABLE(SVG)

#endif
