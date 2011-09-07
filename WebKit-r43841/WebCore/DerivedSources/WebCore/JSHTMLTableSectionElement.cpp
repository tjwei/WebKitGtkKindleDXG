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

#include "JSHTMLTableSectionElement.h"

#include <wtf/GetPtr.h>

#include "HTMLCollection.h"
#include "HTMLElement.h"
#include "HTMLTableSectionElement.h"
#include "JSHTMLCollection.h"
#include "JSHTMLElement.h"
#include "KURL.h"

#include <runtime/Error.h>
#include <runtime/JSNumberCell.h>
#include <runtime/JSString.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSHTMLTableSectionElement);

/* Hash table */

static const HashTableValue JSHTMLTableSectionElementTableValues[7] =
{
    { "align", DontDelete, (intptr_t)jsHTMLTableSectionElementAlign, (intptr_t)setJSHTMLTableSectionElementAlign },
    { "ch", DontDelete, (intptr_t)jsHTMLTableSectionElementCh, (intptr_t)setJSHTMLTableSectionElementCh },
    { "chOff", DontDelete, (intptr_t)jsHTMLTableSectionElementChOff, (intptr_t)setJSHTMLTableSectionElementChOff },
    { "vAlign", DontDelete, (intptr_t)jsHTMLTableSectionElementVAlign, (intptr_t)setJSHTMLTableSectionElementVAlign },
    { "rows", DontDelete|ReadOnly, (intptr_t)jsHTMLTableSectionElementRows, (intptr_t)0 },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsHTMLTableSectionElementConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLTableSectionElementTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 7, JSHTMLTableSectionElementTableValues, 0 };
#else
    { 16, 15, JSHTMLTableSectionElementTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSHTMLTableSectionElementConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLTableSectionElementConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSHTMLTableSectionElementConstructorTableValues, 0 };
#else
    { 1, 0, JSHTMLTableSectionElementConstructorTableValues, 0 };
#endif

class JSHTMLTableSectionElementConstructor : public DOMObject {
public:
    JSHTMLTableSectionElementConstructor(ExecState* exec)
        : DOMObject(JSHTMLTableSectionElementConstructor::createStructure(exec->lexicalGlobalObject()->objectPrototype()))
    {
        putDirect(exec->propertyNames().prototype, JSHTMLTableSectionElementPrototype::self(exec, exec->lexicalGlobalObject()), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValue proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, ImplementsHasInstance)); 
    }
};

const ClassInfo JSHTMLTableSectionElementConstructor::s_info = { "HTMLTableSectionElementConstructor", 0, &JSHTMLTableSectionElementConstructorTable, 0 };

bool JSHTMLTableSectionElementConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSHTMLTableSectionElementConstructor, DOMObject>(exec, &JSHTMLTableSectionElementConstructorTable, this, propertyName, slot);
}

/* Hash table for prototype */

static const HashTableValue JSHTMLTableSectionElementPrototypeTableValues[3] =
{
    { "insertRow", DontDelete|Function, (intptr_t)jsHTMLTableSectionElementPrototypeFunctionInsertRow, (intptr_t)1 },
    { "deleteRow", DontDelete|Function, (intptr_t)jsHTMLTableSectionElementPrototypeFunctionDeleteRow, (intptr_t)1 },
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLTableSectionElementPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 15, JSHTMLTableSectionElementPrototypeTableValues, 0 };
#else
    { 5, 3, JSHTMLTableSectionElementPrototypeTableValues, 0 };
#endif

const ClassInfo JSHTMLTableSectionElementPrototype::s_info = { "HTMLTableSectionElementPrototype", 0, &JSHTMLTableSectionElementPrototypeTable, 0 };

JSObject* JSHTMLTableSectionElementPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSHTMLTableSectionElement>(exec, globalObject);
}

bool JSHTMLTableSectionElementPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticFunctionSlot<JSObject>(exec, &JSHTMLTableSectionElementPrototypeTable, this, propertyName, slot);
}

const ClassInfo JSHTMLTableSectionElement::s_info = { "HTMLTableSectionElement", &JSHTMLElement::s_info, &JSHTMLTableSectionElementTable, 0 };

JSHTMLTableSectionElement::JSHTMLTableSectionElement(PassRefPtr<Structure> structure, PassRefPtr<HTMLTableSectionElement> impl)
    : JSHTMLElement(structure, impl)
{
}

JSObject* JSHTMLTableSectionElement::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSHTMLTableSectionElementPrototype(JSHTMLTableSectionElementPrototype::createStructure(JSHTMLElementPrototype::self(exec, globalObject)));
}

bool JSHTMLTableSectionElement::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSHTMLTableSectionElement, Base>(exec, &JSHTMLTableSectionElementTable, this, propertyName, slot);
}

JSValue jsHTMLTableSectionElementAlign(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLTableSectionElement* imp = static_cast<HTMLTableSectionElement*>(static_cast<JSHTMLTableSectionElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->align());
}

JSValue jsHTMLTableSectionElementCh(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLTableSectionElement* imp = static_cast<HTMLTableSectionElement*>(static_cast<JSHTMLTableSectionElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->ch());
}

JSValue jsHTMLTableSectionElementChOff(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLTableSectionElement* imp = static_cast<HTMLTableSectionElement*>(static_cast<JSHTMLTableSectionElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->chOff());
}

JSValue jsHTMLTableSectionElementVAlign(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLTableSectionElement* imp = static_cast<HTMLTableSectionElement*>(static_cast<JSHTMLTableSectionElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->vAlign());
}

JSValue jsHTMLTableSectionElementRows(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLTableSectionElement* imp = static_cast<HTMLTableSectionElement*>(static_cast<JSHTMLTableSectionElement*>(asObject(slot.slotBase()))->impl());
    return toJS(exec, WTF::getPtr(imp->rows()));
}

JSValue jsHTMLTableSectionElementConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    return static_cast<JSHTMLTableSectionElement*>(asObject(slot.slotBase()))->getConstructor(exec);
}
void JSHTMLTableSectionElement::put(ExecState* exec, const Identifier& propertyName, JSValue value, PutPropertySlot& slot)
{
    lookupPut<JSHTMLTableSectionElement, Base>(exec, propertyName, value, &JSHTMLTableSectionElementTable, this, slot);
}

void setJSHTMLTableSectionElementAlign(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLTableSectionElement* imp = static_cast<HTMLTableSectionElement*>(static_cast<JSHTMLTableSectionElement*>(thisObject)->impl());
    imp->setAlign(valueToStringWithNullCheck(exec, value));
}

void setJSHTMLTableSectionElementCh(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLTableSectionElement* imp = static_cast<HTMLTableSectionElement*>(static_cast<JSHTMLTableSectionElement*>(thisObject)->impl());
    imp->setCh(valueToStringWithNullCheck(exec, value));
}

void setJSHTMLTableSectionElementChOff(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLTableSectionElement* imp = static_cast<HTMLTableSectionElement*>(static_cast<JSHTMLTableSectionElement*>(thisObject)->impl());
    imp->setChOff(valueToStringWithNullCheck(exec, value));
}

void setJSHTMLTableSectionElementVAlign(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLTableSectionElement* imp = static_cast<HTMLTableSectionElement*>(static_cast<JSHTMLTableSectionElement*>(thisObject)->impl());
    imp->setVAlign(valueToStringWithNullCheck(exec, value));
}

JSValue JSHTMLTableSectionElement::getConstructor(ExecState* exec)
{
    return getDOMConstructor<JSHTMLTableSectionElementConstructor>(exec);
}

JSValue JSC_HOST_CALL jsHTMLTableSectionElementPrototypeFunctionInsertRow(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSHTMLTableSectionElement::s_info))
        return throwError(exec, TypeError);
    JSHTMLTableSectionElement* castedThisObj = static_cast<JSHTMLTableSectionElement*>(asObject(thisValue));
    HTMLTableSectionElement* imp = static_cast<HTMLTableSectionElement*>(castedThisObj->impl());
    ExceptionCode ec = 0;
    int index = args.at(0).toInt32(exec);


    JSC::JSValue result = toJS(exec, WTF::getPtr(imp->insertRow(index, ec)));
    setDOMException(exec, ec);
    return result;
}

JSValue JSC_HOST_CALL jsHTMLTableSectionElementPrototypeFunctionDeleteRow(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSHTMLTableSectionElement::s_info))
        return throwError(exec, TypeError);
    JSHTMLTableSectionElement* castedThisObj = static_cast<JSHTMLTableSectionElement*>(asObject(thisValue));
    HTMLTableSectionElement* imp = static_cast<HTMLTableSectionElement*>(castedThisObj->impl());
    ExceptionCode ec = 0;
    int index = args.at(0).toInt32(exec);

    imp->deleteRow(index, ec);
    setDOMException(exec, ec);
    return jsUndefined();
}

HTMLTableSectionElement* toHTMLTableSectionElement(JSC::JSValue value)
{
    return value.isObject(&JSHTMLTableSectionElement::s_info) ? static_cast<JSHTMLTableSectionElement*>(asObject(value))->impl() : 0;
}

}
