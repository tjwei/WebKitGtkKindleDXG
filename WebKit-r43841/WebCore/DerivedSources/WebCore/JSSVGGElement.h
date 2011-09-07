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

#ifndef JSSVGGElement_h
#define JSSVGGElement_h


#if ENABLE(SVG)

#include "JSSVGElement.h"

namespace WebCore {

class SVGGElement;

class JSSVGGElement : public JSSVGElement {
    typedef JSSVGElement Base;
public:
    JSSVGGElement(PassRefPtr<JSC::Structure>, PassRefPtr<SVGGElement>);
    static JSC::JSObject* createPrototype(JSC::ExecState*, JSC::JSGlobalObject*);
    virtual bool getOwnPropertySlot(JSC::ExecState*, const JSC::Identifier& propertyName, JSC::PropertySlot&);
    virtual void put(JSC::ExecState*, const JSC::Identifier& propertyName, JSC::JSValue, JSC::PutPropertySlot&);
    virtual const JSC::ClassInfo* classInfo() const { return &s_info; }
    static const JSC::ClassInfo s_info;

    static PassRefPtr<JSC::Structure> createStructure(JSC::JSValue prototype)
    {
        return JSC::Structure::create(prototype, JSC::TypeInfo(JSC::ObjectType));
    }

};


class JSSVGGElementPrototype : public JSC::JSObject {
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
    JSSVGGElementPrototype(PassRefPtr<JSC::Structure> structure) : JSC::JSObject(structure) { }
};

// Functions

JSC::JSValue JSC_HOST_CALL jsSVGGElementPrototypeFunctionHasExtension(JSC::ExecState*, JSC::JSObject*, JSC::JSValue, const JSC::ArgList&);
JSC::JSValue JSC_HOST_CALL jsSVGGElementPrototypeFunctionGetPresentationAttribute(JSC::ExecState*, JSC::JSObject*, JSC::JSValue, const JSC::ArgList&);
JSC::JSValue JSC_HOST_CALL jsSVGGElementPrototypeFunctionGetBBox(JSC::ExecState*, JSC::JSObject*, JSC::JSValue, const JSC::ArgList&);
JSC::JSValue JSC_HOST_CALL jsSVGGElementPrototypeFunctionGetCTM(JSC::ExecState*, JSC::JSObject*, JSC::JSValue, const JSC::ArgList&);
JSC::JSValue JSC_HOST_CALL jsSVGGElementPrototypeFunctionGetScreenCTM(JSC::ExecState*, JSC::JSObject*, JSC::JSValue, const JSC::ArgList&);
JSC::JSValue JSC_HOST_CALL jsSVGGElementPrototypeFunctionGetTransformToElement(JSC::ExecState*, JSC::JSObject*, JSC::JSValue, const JSC::ArgList&);
// Attributes

JSC::JSValue jsSVGGElementRequiredFeatures(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
JSC::JSValue jsSVGGElementRequiredExtensions(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
JSC::JSValue jsSVGGElementSystemLanguage(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
JSC::JSValue jsSVGGElementXmllang(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
void setJSSVGGElementXmllang(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
JSC::JSValue jsSVGGElementXmlspace(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
void setJSSVGGElementXmlspace(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
JSC::JSValue jsSVGGElementExternalResourcesRequired(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
JSC::JSValue jsSVGGElementClassName(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
JSC::JSValue jsSVGGElementStyle(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
JSC::JSValue jsSVGGElementTransform(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
JSC::JSValue jsSVGGElementNearestViewportElement(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
JSC::JSValue jsSVGGElementFarthestViewportElement(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);

} // namespace WebCore

#endif // ENABLE(SVG)

#endif
