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

#include "JSPluginArray.h"

#include <wtf/GetPtr.h>

#include <runtime/PropertyNameArray.h>
#include "AtomicString.h"
#include "JSPlugin.h"
#include "Plugin.h"
#include "PluginArray.h"

#include <runtime/Error.h>
#include <runtime/JSNumberCell.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSPluginArray);

/* Hash table */

static const HashTableValue JSPluginArrayTableValues[3] =
{
    { "length", DontDelete|ReadOnly, (intptr_t)jsPluginArrayLength, (intptr_t)0 },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsPluginArrayConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSPluginArrayTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 15, JSPluginArrayTableValues, 0 };
#else
    { 5, 3, JSPluginArrayTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSPluginArrayConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSPluginArrayConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSPluginArrayConstructorTableValues, 0 };
#else
    { 1, 0, JSPluginArrayConstructorTableValues, 0 };
#endif

class JSPluginArrayConstructor : public DOMObject {
public:
    JSPluginArrayConstructor(ExecState* exec)
        : DOMObject(JSPluginArrayConstructor::createStructure(exec->lexicalGlobalObject()->objectPrototype()))
    {
        putDirect(exec->propertyNames().prototype, JSPluginArrayPrototype::self(exec, exec->lexicalGlobalObject()), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValue proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, ImplementsHasInstance)); 
    }
};

const ClassInfo JSPluginArrayConstructor::s_info = { "PluginArrayConstructor", 0, &JSPluginArrayConstructorTable, 0 };

bool JSPluginArrayConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSPluginArrayConstructor, DOMObject>(exec, &JSPluginArrayConstructorTable, this, propertyName, slot);
}

/* Hash table for prototype */

static const HashTableValue JSPluginArrayPrototypeTableValues[4] =
{
    { "item", DontDelete|Function, (intptr_t)jsPluginArrayPrototypeFunctionItem, (intptr_t)1 },
    { "namedItem", DontDelete|Function, (intptr_t)jsPluginArrayPrototypeFunctionNamedItem, (intptr_t)1 },
    { "refresh", DontDelete|Function, (intptr_t)jsPluginArrayPrototypeFunctionRefresh, (intptr_t)1 },
    { 0, 0, 0, 0 }
};

static const HashTable JSPluginArrayPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 7, JSPluginArrayPrototypeTableValues, 0 };
#else
    { 8, 7, JSPluginArrayPrototypeTableValues, 0 };
#endif

const ClassInfo JSPluginArrayPrototype::s_info = { "PluginArrayPrototype", 0, &JSPluginArrayPrototypeTable, 0 };

JSObject* JSPluginArrayPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSPluginArray>(exec, globalObject);
}

bool JSPluginArrayPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticFunctionSlot<JSObject>(exec, &JSPluginArrayPrototypeTable, this, propertyName, slot);
}

const ClassInfo JSPluginArray::s_info = { "PluginArray", 0, &JSPluginArrayTable, 0 };

JSPluginArray::JSPluginArray(PassRefPtr<Structure> structure, PassRefPtr<PluginArray> impl)
    : DOMObject(structure)
    , m_impl(impl)
{
}

JSPluginArray::~JSPluginArray()
{
    forgetDOMObject(*Heap::heap(this)->globalData(), m_impl.get());
}

JSObject* JSPluginArray::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSPluginArrayPrototype(JSPluginArrayPrototype::createStructure(globalObject->objectPrototype()));
}

bool JSPluginArray::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    const HashEntry* entry = JSPluginArrayTable.entry(exec, propertyName);
    if (entry) {
        slot.setCustom(this, entry->propertyGetter());
        return true;
    }
    bool ok;
    unsigned index = propertyName.toUInt32(&ok, false);
    if (ok && index < static_cast<PluginArray*>(impl())->length()) {
        slot.setCustomIndex(this, index, indexGetter);
        return true;
    }
    if (canGetItemsForName(exec, static_cast<PluginArray*>(impl()), propertyName)) {
        slot.setCustom(this, nameGetter);
        return true;
    }
    return getStaticValueSlot<JSPluginArray, Base>(exec, &JSPluginArrayTable, this, propertyName, slot);
}

bool JSPluginArray::getOwnPropertySlot(ExecState* exec, unsigned propertyName, PropertySlot& slot)
{
    if (propertyName < static_cast<PluginArray*>(impl())->length()) {
        slot.setCustomIndex(this, propertyName, indexGetter);
        return true;
    }
    return getOwnPropertySlot(exec, Identifier::from(exec, propertyName), slot);
}

JSValue jsPluginArrayLength(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    PluginArray* imp = static_cast<PluginArray*>(static_cast<JSPluginArray*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->length());
}

JSValue jsPluginArrayConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    return static_cast<JSPluginArray*>(asObject(slot.slotBase()))->getConstructor(exec);
}
void JSPluginArray::getPropertyNames(ExecState* exec, PropertyNameArray& propertyNames)
{
    for (unsigned i = 0; i < static_cast<PluginArray*>(impl())->length(); ++i)
        propertyNames.add(Identifier::from(exec, i));
     Base::getPropertyNames(exec, propertyNames);
}

JSValue JSPluginArray::getConstructor(ExecState* exec)
{
    return getDOMConstructor<JSPluginArrayConstructor>(exec);
}

JSValue JSC_HOST_CALL jsPluginArrayPrototypeFunctionItem(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSPluginArray::s_info))
        return throwError(exec, TypeError);
    JSPluginArray* castedThisObj = static_cast<JSPluginArray*>(asObject(thisValue));
    PluginArray* imp = static_cast<PluginArray*>(castedThisObj->impl());
    unsigned index = args.at(0).toInt32(exec);


    JSC::JSValue result = toJS(exec, WTF::getPtr(imp->item(index)));
    return result;
}

JSValue JSC_HOST_CALL jsPluginArrayPrototypeFunctionNamedItem(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSPluginArray::s_info))
        return throwError(exec, TypeError);
    JSPluginArray* castedThisObj = static_cast<JSPluginArray*>(asObject(thisValue));
    PluginArray* imp = static_cast<PluginArray*>(castedThisObj->impl());
    const UString& name = args.at(0).toString(exec);


    JSC::JSValue result = toJS(exec, WTF::getPtr(imp->namedItem(name)));
    return result;
}

JSValue JSC_HOST_CALL jsPluginArrayPrototypeFunctionRefresh(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSPluginArray::s_info))
        return throwError(exec, TypeError);
    JSPluginArray* castedThisObj = static_cast<JSPluginArray*>(asObject(thisValue));
    PluginArray* imp = static_cast<PluginArray*>(castedThisObj->impl());
    bool reload = args.at(0).toBoolean(exec);

    imp->refresh(reload);
    return jsUndefined();
}


JSValue JSPluginArray::indexGetter(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSPluginArray* thisObj = static_cast<JSPluginArray*>(asObject(slot.slotBase()));
    return toJS(exec, static_cast<PluginArray*>(thisObj->impl())->item(slot.index()));
}
JSC::JSValue toJS(JSC::ExecState* exec, PluginArray* object)
{
    return getDOMObjectWrapper<JSPluginArray>(exec, object);
}
PluginArray* toPluginArray(JSC::JSValue value)
{
    return value.isObject(&JSPluginArray::s_info) ? static_cast<JSPluginArray*>(asObject(value))->impl() : 0;
}

}
