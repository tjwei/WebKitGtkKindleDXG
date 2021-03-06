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

#ifndef JSClientRect_h
#define JSClientRect_h

#include "JSDOMBinding.h"
#include <runtime/JSGlobalObject.h>
#include <runtime/ObjectPrototype.h>

namespace WebCore {

class ClientRect;

class JSClientRect : public DOMObject {
    typedef DOMObject Base;
public:
    JSClientRect(PassRefPtr<JSC::Structure>, PassRefPtr<ClientRect>);
    virtual ~JSClientRect();
    static JSC::JSObject* createPrototype(JSC::ExecState*, JSC::JSGlobalObject*);
    virtual bool getOwnPropertySlot(JSC::ExecState*, const JSC::Identifier& propertyName, JSC::PropertySlot&);
    virtual const JSC::ClassInfo* classInfo() const { return &s_info; }
    static const JSC::ClassInfo s_info;

    static PassRefPtr<JSC::Structure> createStructure(JSC::JSValue prototype)
    {
        return JSC::Structure::create(prototype, JSC::TypeInfo(JSC::ObjectType));
    }

    static JSC::JSValue getConstructor(JSC::ExecState*);
    ClientRect* impl() const { return m_impl.get(); }

private:
    RefPtr<ClientRect> m_impl;
};

JSC::JSValue toJS(JSC::ExecState*, ClientRect*);
ClientRect* toClientRect(JSC::JSValue);

class JSClientRectPrototype : public JSC::JSObject {
    typedef JSC::JSObject Base;
public:
    static JSC::JSObject* self(JSC::ExecState*, JSC::JSGlobalObject*);
    virtual const JSC::ClassInfo* classInfo() const { return &s_info; }
    static const JSC::ClassInfo s_info;
    JSClientRectPrototype(PassRefPtr<JSC::Structure> structure) : JSC::JSObject(structure) { }
};

// Attributes

JSC::JSValue jsClientRectTop(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
JSC::JSValue jsClientRectRight(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
JSC::JSValue jsClientRectBottom(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
JSC::JSValue jsClientRectLeft(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
JSC::JSValue jsClientRectWidth(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
JSC::JSValue jsClientRectHeight(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
JSC::JSValue jsClientRectConstructor(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);

} // namespace WebCore

#endif
