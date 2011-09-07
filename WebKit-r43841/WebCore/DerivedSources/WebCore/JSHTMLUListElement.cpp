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

#include "JSHTMLUListElement.h"

#include <wtf/GetPtr.h>

#include "HTMLUListElement.h"
#include "KURL.h"

#include <runtime/JSNumberCell.h>
#include <runtime/JSString.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSHTMLUListElement);

/* Hash table */

static const HashTableValue JSHTMLUListElementTableValues[4] =
{
    { "compact", DontDelete, (intptr_t)jsHTMLUListElementCompact, (intptr_t)setJSHTMLUListElementCompact },
    { "type", DontDelete, (intptr_t)jsHTMLUListElementType, (intptr_t)setJSHTMLUListElementType },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsHTMLUListElementConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLUListElementTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 7, JSHTMLUListElementTableValues, 0 };
#else
    { 8, 7, JSHTMLUListElementTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSHTMLUListElementConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLUListElementConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSHTMLUListElementConstructorTableValues, 0 };
#else
    { 1, 0, JSHTMLUListElementConstructorTableValues, 0 };
#endif

class JSHTMLUListElementConstructor : public DOMObject {
public:
    JSHTMLUListElementConstructor(ExecState* exec)
        : DOMObject(JSHTMLUListElementConstructor::createStructure(exec->lexicalGlobalObject()->objectPrototype()))
    {
        putDirect(exec->propertyNames().prototype, JSHTMLUListElementPrototype::self(exec, exec->lexicalGlobalObject()), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValue proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, ImplementsHasInstance)); 
    }
};

const ClassInfo JSHTMLUListElementConstructor::s_info = { "HTMLUListElementConstructor", 0, &JSHTMLUListElementConstructorTable, 0 };

bool JSHTMLUListElementConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSHTMLUListElementConstructor, DOMObject>(exec, &JSHTMLUListElementConstructorTable, this, propertyName, slot);
}

/* Hash table for prototype */

static const HashTableValue JSHTMLUListElementPrototypeTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLUListElementPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSHTMLUListElementPrototypeTableValues, 0 };
#else
    { 1, 0, JSHTMLUListElementPrototypeTableValues, 0 };
#endif

const ClassInfo JSHTMLUListElementPrototype::s_info = { "HTMLUListElementPrototype", 0, &JSHTMLUListElementPrototypeTable, 0 };

JSObject* JSHTMLUListElementPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSHTMLUListElement>(exec, globalObject);
}

const ClassInfo JSHTMLUListElement::s_info = { "HTMLUListElement", &JSHTMLElement::s_info, &JSHTMLUListElementTable, 0 };

JSHTMLUListElement::JSHTMLUListElement(PassRefPtr<Structure> structure, PassRefPtr<HTMLUListElement> impl)
    : JSHTMLElement(structure, impl)
{
}

JSObject* JSHTMLUListElement::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSHTMLUListElementPrototype(JSHTMLUListElementPrototype::createStructure(JSHTMLElementPrototype::self(exec, globalObject)));
}

bool JSHTMLUListElement::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSHTMLUListElement, Base>(exec, &JSHTMLUListElementTable, this, propertyName, slot);
}

JSValue jsHTMLUListElementCompact(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLUListElement* imp = static_cast<HTMLUListElement*>(static_cast<JSHTMLUListElement*>(asObject(slot.slotBase()))->impl());
    return jsBoolean(imp->compact());
}

JSValue jsHTMLUListElementType(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLUListElement* imp = static_cast<HTMLUListElement*>(static_cast<JSHTMLUListElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->type());
}

JSValue jsHTMLUListElementConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    return static_cast<JSHTMLUListElement*>(asObject(slot.slotBase()))->getConstructor(exec);
}
void JSHTMLUListElement::put(ExecState* exec, const Identifier& propertyName, JSValue value, PutPropertySlot& slot)
{
    lookupPut<JSHTMLUListElement, Base>(exec, propertyName, value, &JSHTMLUListElementTable, this, slot);
}

void setJSHTMLUListElementCompact(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLUListElement* imp = static_cast<HTMLUListElement*>(static_cast<JSHTMLUListElement*>(thisObject)->impl());
    imp->setCompact(value.toBoolean(exec));
}

void setJSHTMLUListElementType(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLUListElement* imp = static_cast<HTMLUListElement*>(static_cast<JSHTMLUListElement*>(thisObject)->impl());
    imp->setType(valueToStringWithNullCheck(exec, value));
}

JSValue JSHTMLUListElement::getConstructor(ExecState* exec)
{
    return getDOMConstructor<JSHTMLUListElementConstructor>(exec);
}


}