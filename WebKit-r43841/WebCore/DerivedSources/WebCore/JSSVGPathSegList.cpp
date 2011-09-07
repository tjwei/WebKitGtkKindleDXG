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


#if ENABLE(SVG)

#include "SVGElement.h"
#include "JSSVGPathSegList.h"

#include <wtf/GetPtr.h>

#include "SVGPathSeg.h"
#include "SVGPathSegList.h"

#include <runtime/Error.h>
#include <runtime/JSNumberCell.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGPathSegList);

/* Hash table */

static const HashTableValue JSSVGPathSegListTableValues[2] =
{
    { "numberOfItems", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegListNumberOfItems, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGPathSegListTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGPathSegListTableValues, 0 };
#else
    { 2, 1, JSSVGPathSegListTableValues, 0 };
#endif

/* Hash table for prototype */

static const HashTableValue JSSVGPathSegListPrototypeTableValues[8] =
{
    { "clear", DontDelete|Function, (intptr_t)jsSVGPathSegListPrototypeFunctionClear, (intptr_t)0 },
    { "initialize", DontDelete|Function, (intptr_t)jsSVGPathSegListPrototypeFunctionInitialize, (intptr_t)1 },
    { "getItem", DontDelete|Function, (intptr_t)jsSVGPathSegListPrototypeFunctionGetItem, (intptr_t)1 },
    { "insertItemBefore", DontDelete|Function, (intptr_t)jsSVGPathSegListPrototypeFunctionInsertItemBefore, (intptr_t)2 },
    { "replaceItem", DontDelete|Function, (intptr_t)jsSVGPathSegListPrototypeFunctionReplaceItem, (intptr_t)2 },
    { "removeItem", DontDelete|Function, (intptr_t)jsSVGPathSegListPrototypeFunctionRemoveItem, (intptr_t)1 },
    { "appendItem", DontDelete|Function, (intptr_t)jsSVGPathSegListPrototypeFunctionAppendItem, (intptr_t)1 },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGPathSegListPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 63, JSSVGPathSegListPrototypeTableValues, 0 };
#else
    { 18, 15, JSSVGPathSegListPrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGPathSegListPrototype::s_info = { "SVGPathSegListPrototype", 0, &JSSVGPathSegListPrototypeTable, 0 };

JSObject* JSSVGPathSegListPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSSVGPathSegList>(exec, globalObject);
}

bool JSSVGPathSegListPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticFunctionSlot<JSObject>(exec, &JSSVGPathSegListPrototypeTable, this, propertyName, slot);
}

const ClassInfo JSSVGPathSegList::s_info = { "SVGPathSegList", 0, &JSSVGPathSegListTable, 0 };

JSSVGPathSegList::JSSVGPathSegList(PassRefPtr<Structure> structure, PassRefPtr<SVGPathSegList> impl, SVGElement* context)
    : DOMObject(structure)
    , m_context(context)
    , m_impl(impl)
{
}

JSSVGPathSegList::~JSSVGPathSegList()
{
    forgetDOMObject(*Heap::heap(this)->globalData(), m_impl.get());
}

JSObject* JSSVGPathSegList::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSSVGPathSegListPrototype(JSSVGPathSegListPrototype::createStructure(globalObject->objectPrototype()));
}

bool JSSVGPathSegList::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGPathSegList, Base>(exec, &JSSVGPathSegListTable, this, propertyName, slot);
}

JSValue jsSVGPathSegListNumberOfItems(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    SVGPathSegList* imp = static_cast<SVGPathSegList*>(static_cast<JSSVGPathSegList*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->numberOfItems());
}

JSValue JSC_HOST_CALL jsSVGPathSegListPrototypeFunctionClear(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSSVGPathSegList::s_info))
        return throwError(exec, TypeError);
    JSSVGPathSegList* castedThisObj = static_cast<JSSVGPathSegList*>(asObject(thisValue));
    return castedThisObj->clear(exec, args);
}

JSValue JSC_HOST_CALL jsSVGPathSegListPrototypeFunctionInitialize(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSSVGPathSegList::s_info))
        return throwError(exec, TypeError);
    JSSVGPathSegList* castedThisObj = static_cast<JSSVGPathSegList*>(asObject(thisValue));
    return castedThisObj->initialize(exec, args);
}

JSValue JSC_HOST_CALL jsSVGPathSegListPrototypeFunctionGetItem(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSSVGPathSegList::s_info))
        return throwError(exec, TypeError);
    JSSVGPathSegList* castedThisObj = static_cast<JSSVGPathSegList*>(asObject(thisValue));
    return castedThisObj->getItem(exec, args);
}

JSValue JSC_HOST_CALL jsSVGPathSegListPrototypeFunctionInsertItemBefore(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSSVGPathSegList::s_info))
        return throwError(exec, TypeError);
    JSSVGPathSegList* castedThisObj = static_cast<JSSVGPathSegList*>(asObject(thisValue));
    return castedThisObj->insertItemBefore(exec, args);
}

JSValue JSC_HOST_CALL jsSVGPathSegListPrototypeFunctionReplaceItem(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSSVGPathSegList::s_info))
        return throwError(exec, TypeError);
    JSSVGPathSegList* castedThisObj = static_cast<JSSVGPathSegList*>(asObject(thisValue));
    return castedThisObj->replaceItem(exec, args);
}

JSValue JSC_HOST_CALL jsSVGPathSegListPrototypeFunctionRemoveItem(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSSVGPathSegList::s_info))
        return throwError(exec, TypeError);
    JSSVGPathSegList* castedThisObj = static_cast<JSSVGPathSegList*>(asObject(thisValue));
    return castedThisObj->removeItem(exec, args);
}

JSValue JSC_HOST_CALL jsSVGPathSegListPrototypeFunctionAppendItem(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSSVGPathSegList::s_info))
        return throwError(exec, TypeError);
    JSSVGPathSegList* castedThisObj = static_cast<JSSVGPathSegList*>(asObject(thisValue));
    return castedThisObj->appendItem(exec, args);
}

JSC::JSValue toJS(JSC::ExecState* exec, SVGPathSegList* object, SVGElement* context)
{
    return getDOMObjectWrapper<JSSVGPathSegList>(exec, object, context);
}
SVGPathSegList* toSVGPathSegList(JSC::JSValue value)
{
    return value.isObject(&JSSVGPathSegList::s_info) ? static_cast<JSSVGPathSegList*>(asObject(value))->impl() : 0;
}

}

#endif // ENABLE(SVG)
