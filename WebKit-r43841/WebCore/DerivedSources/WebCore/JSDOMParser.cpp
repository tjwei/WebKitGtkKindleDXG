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

#include "config.h"

#include "JSDOMParser.h"

#include <wtf/GetPtr.h>

#include "DOMParser.h"
#include "Document.h"
#include "JSDocument.h"
#include "NodeFilter.h"

#include <runtime/Error.h>
#include <runtime/JSNumberCell.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSDOMParser);

/* Hash table */

static const HashTableValue JSDOMParserTableValues[2] =
{
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsDOMParserConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSDOMParserTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSDOMParserTableValues, 0 };
#else
    { 2, 1, JSDOMParserTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSDOMParserConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSDOMParserConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSDOMParserConstructorTableValues, 0 };
#else
    { 1, 0, JSDOMParserConstructorTableValues, 0 };
#endif

class JSDOMParserConstructor : public DOMObject {
public:
    JSDOMParserConstructor(ExecState* exec)
        : DOMObject(JSDOMParserConstructor::createStructure(exec->lexicalGlobalObject()->objectPrototype()))
    {
        putDirect(exec->propertyNames().prototype, JSDOMParserPrototype::self(exec, exec->lexicalGlobalObject()), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValue proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, ImplementsHasInstance)); 
    }
    static JSObject* construct(ExecState* exec, JSObject*, const ArgList&)
    {
        return asObject(toJS(exec, DOMParser::create()));
    }
    virtual ConstructType getConstructData(ConstructData& constructData)
    {
        constructData.native.function = construct;
        return ConstructTypeHost;
    }
};

const ClassInfo JSDOMParserConstructor::s_info = { "DOMParserConstructor", 0, &JSDOMParserConstructorTable, 0 };

bool JSDOMParserConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSDOMParserConstructor, DOMObject>(exec, &JSDOMParserConstructorTable, this, propertyName, slot);
}

/* Hash table for prototype */

static const HashTableValue JSDOMParserPrototypeTableValues[2] =
{
    { "parseFromString", DontDelete|Function, (intptr_t)jsDOMParserPrototypeFunctionParseFromString, (intptr_t)2 },
    { 0, 0, 0, 0 }
};

static const HashTable JSDOMParserPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSDOMParserPrototypeTableValues, 0 };
#else
    { 2, 1, JSDOMParserPrototypeTableValues, 0 };
#endif

const ClassInfo JSDOMParserPrototype::s_info = { "DOMParserPrototype", 0, &JSDOMParserPrototypeTable, 0 };

JSObject* JSDOMParserPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSDOMParser>(exec, globalObject);
}

bool JSDOMParserPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticFunctionSlot<JSObject>(exec, &JSDOMParserPrototypeTable, this, propertyName, slot);
}

const ClassInfo JSDOMParser::s_info = { "DOMParser", 0, &JSDOMParserTable, 0 };

JSDOMParser::JSDOMParser(PassRefPtr<Structure> structure, PassRefPtr<DOMParser> impl)
    : DOMObject(structure)
    , m_impl(impl)
{
}

JSDOMParser::~JSDOMParser()
{
    forgetDOMObject(*Heap::heap(this)->globalData(), m_impl.get());
}

JSObject* JSDOMParser::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSDOMParserPrototype(JSDOMParserPrototype::createStructure(globalObject->objectPrototype()));
}

bool JSDOMParser::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSDOMParser, Base>(exec, &JSDOMParserTable, this, propertyName, slot);
}

JSValue jsDOMParserConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    return static_cast<JSDOMParser*>(asObject(slot.slotBase()))->getConstructor(exec);
}
JSValue JSDOMParser::getConstructor(ExecState* exec)
{
    return getDOMConstructor<JSDOMParserConstructor>(exec);
}

JSValue JSC_HOST_CALL jsDOMParserPrototypeFunctionParseFromString(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSDOMParser::s_info))
        return throwError(exec, TypeError);
    JSDOMParser* castedThisObj = static_cast<JSDOMParser*>(asObject(thisValue));
    DOMParser* imp = static_cast<DOMParser*>(castedThisObj->impl());
    const UString& str = args.at(0).toString(exec);
    const UString& contentType = args.at(1).toString(exec);


    JSC::JSValue result = toJS(exec, WTF::getPtr(imp->parseFromString(str, contentType)));
    return result;
}

JSC::JSValue toJS(JSC::ExecState* exec, DOMParser* object)
{
    return getDOMObjectWrapper<JSDOMParser>(exec, object);
}
DOMParser* toDOMParser(JSC::JSValue value)
{
    return value.isObject(&JSDOMParser::s_info) ? static_cast<JSDOMParser*>(asObject(value))->impl() : 0;
}

}
