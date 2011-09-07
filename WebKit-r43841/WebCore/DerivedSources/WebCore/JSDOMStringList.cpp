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

#include "JSDOMStringList.h"

#include <wtf/GetPtr.h>

#include <runtime/PropertyNameArray.h>
#include "DOMStringList.h"

#include <runtime/Error.h>
#include <runtime/JSNumberCell.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSDOMStringList);

/* Hash table */

static const HashTableValue JSDOMStringListTableValues[3] =
{
    { "length", DontDelete|ReadOnly, (intptr_t)jsDOMStringListLength, (intptr_t)0 },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsDOMStringListConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSDOMStringListTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 15, JSDOMStringListTableValues, 0 };
#else
    { 5, 3, JSDOMStringListTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSDOMStringListConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSDOMStringListConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSDOMStringListConstructorTableValues, 0 };
#else
    { 1, 0, JSDOMStringListConstructorTableValues, 0 };
#endif

class JSDOMStringListConstructor : public DOMObject {
public:
    JSDOMStringListConstructor(ExecState* exec)
        : DOMObject(JSDOMStringListConstructor::createStructure(exec->lexicalGlobalObject()->objectPrototype()))
    {
        putDirect(exec->propertyNames().prototype, JSDOMStringListPrototype::self(exec, exec->lexicalGlobalObject()), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValue proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, ImplementsHasInstance)); 
    }
};

const ClassInfo JSDOMStringListConstructor::s_info = { "DOMStringListConstructor", 0, &JSDOMStringListConstructorTable, 0 };

bool JSDOMStringListConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSDOMStringListConstructor, DOMObject>(exec, &JSDOMStringListConstructorTable, this, propertyName, slot);
}

/* Hash table for prototype */

static const HashTableValue JSDOMStringListPrototypeTableValues[3] =
{
    { "item", DontDelete|Function, (intptr_t)jsDOMStringListPrototypeFunctionItem, (intptr_t)1 },
    { "contains", DontDelete|Function, (intptr_t)jsDOMStringListPrototypeFunctionContains, (intptr_t)1 },
    { 0, 0, 0, 0 }
};

static const HashTable JSDOMStringListPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 1, JSDOMStringListPrototypeTableValues, 0 };
#else
    { 4, 3, JSDOMStringListPrototypeTableValues, 0 };
#endif

const ClassInfo JSDOMStringListPrototype::s_info = { "DOMStringListPrototype", 0, &JSDOMStringListPrototypeTable, 0 };

JSObject* JSDOMStringListPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSDOMStringList>(exec, globalObject);
}

bool JSDOMStringListPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticFunctionSlot<JSObject>(exec, &JSDOMStringListPrototypeTable, this, propertyName, slot);
}

const ClassInfo JSDOMStringList::s_info = { "DOMStringList", 0, &JSDOMStringListTable, 0 };

JSDOMStringList::JSDOMStringList(PassRefPtr<Structure> structure, PassRefPtr<DOMStringList> impl)
    : DOMObject(structure)
    , m_impl(impl)
{
}

JSDOMStringList::~JSDOMStringList()
{
    forgetDOMObject(*Heap::heap(this)->globalData(), m_impl.get());
}

JSObject* JSDOMStringList::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSDOMStringListPrototype(JSDOMStringListPrototype::createStructure(globalObject->objectPrototype()));
}

bool JSDOMStringList::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    bool ok;
    unsigned index = propertyName.toUInt32(&ok, false);
    if (ok && index < static_cast<DOMStringList*>(impl())->length()) {
        slot.setValue(getByIndex(exec, index));
        return true;
    }
    return getStaticValueSlot<JSDOMStringList, Base>(exec, &JSDOMStringListTable, this, propertyName, slot);
}

bool JSDOMStringList::getOwnPropertySlot(ExecState* exec, unsigned propertyName, PropertySlot& slot)
{
    if (propertyName < static_cast<DOMStringList*>(impl())->length()) {
        slot.setValue(getByIndex(exec, propertyName));
        return true;
    }
    return getOwnPropertySlot(exec, Identifier::from(exec, propertyName), slot);
}

JSValue jsDOMStringListLength(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    DOMStringList* imp = static_cast<DOMStringList*>(static_cast<JSDOMStringList*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->length());
}

JSValue jsDOMStringListConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    return static_cast<JSDOMStringList*>(asObject(slot.slotBase()))->getConstructor(exec);
}
void JSDOMStringList::getPropertyNames(ExecState* exec, PropertyNameArray& propertyNames)
{
    for (unsigned i = 0; i < static_cast<DOMStringList*>(impl())->length(); ++i)
        propertyNames.add(Identifier::from(exec, i));
     Base::getPropertyNames(exec, propertyNames);
}

JSValue JSDOMStringList::getConstructor(ExecState* exec)
{
    return getDOMConstructor<JSDOMStringListConstructor>(exec);
}

JSValue JSC_HOST_CALL jsDOMStringListPrototypeFunctionItem(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSDOMStringList::s_info))
        return throwError(exec, TypeError);
    JSDOMStringList* castedThisObj = static_cast<JSDOMStringList*>(asObject(thisValue));
    return castedThisObj->item(exec, args);
}

JSValue JSC_HOST_CALL jsDOMStringListPrototypeFunctionContains(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSDOMStringList::s_info))
        return throwError(exec, TypeError);
    JSDOMStringList* castedThisObj = static_cast<JSDOMStringList*>(asObject(thisValue));
    DOMStringList* imp = static_cast<DOMStringList*>(castedThisObj->impl());
    const UString& str = args.at(0).toString(exec);


    JSC::JSValue result = jsBoolean(imp->contains(str));
    return result;
}

JSC::JSValue toJS(JSC::ExecState* exec, DOMStringList* object)
{
    return getDOMObjectWrapper<JSDOMStringList>(exec, object);
}
DOMStringList* toDOMStringList(JSC::JSValue value)
{
    return value.isObject(&JSDOMStringList::s_info) ? static_cast<JSDOMStringList*>(asObject(value))->impl() : 0;
}

}
