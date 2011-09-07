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

#include "JSHTMLBaseFontElement.h"

#include <wtf/GetPtr.h>

#include "HTMLBaseFontElement.h"
#include "KURL.h"

#include <runtime/JSNumberCell.h>
#include <runtime/JSString.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSHTMLBaseFontElement);

/* Hash table */

static const HashTableValue JSHTMLBaseFontElementTableValues[5] =
{
    { "color", DontDelete, (intptr_t)jsHTMLBaseFontElementColor, (intptr_t)setJSHTMLBaseFontElementColor },
    { "face", DontDelete, (intptr_t)jsHTMLBaseFontElementFace, (intptr_t)setJSHTMLBaseFontElementFace },
    { "size", DontDelete, (intptr_t)jsHTMLBaseFontElementSize, (intptr_t)setJSHTMLBaseFontElementSize },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsHTMLBaseFontElementConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLBaseFontElementTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 15, JSHTMLBaseFontElementTableValues, 0 };
#else
    { 9, 7, JSHTMLBaseFontElementTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSHTMLBaseFontElementConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLBaseFontElementConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSHTMLBaseFontElementConstructorTableValues, 0 };
#else
    { 1, 0, JSHTMLBaseFontElementConstructorTableValues, 0 };
#endif

class JSHTMLBaseFontElementConstructor : public DOMObject {
public:
    JSHTMLBaseFontElementConstructor(ExecState* exec)
        : DOMObject(JSHTMLBaseFontElementConstructor::createStructure(exec->lexicalGlobalObject()->objectPrototype()))
    {
        putDirect(exec->propertyNames().prototype, JSHTMLBaseFontElementPrototype::self(exec, exec->lexicalGlobalObject()), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValue proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, ImplementsHasInstance)); 
    }
};

const ClassInfo JSHTMLBaseFontElementConstructor::s_info = { "HTMLBaseFontElementConstructor", 0, &JSHTMLBaseFontElementConstructorTable, 0 };

bool JSHTMLBaseFontElementConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSHTMLBaseFontElementConstructor, DOMObject>(exec, &JSHTMLBaseFontElementConstructorTable, this, propertyName, slot);
}

/* Hash table for prototype */

static const HashTableValue JSHTMLBaseFontElementPrototypeTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLBaseFontElementPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSHTMLBaseFontElementPrototypeTableValues, 0 };
#else
    { 1, 0, JSHTMLBaseFontElementPrototypeTableValues, 0 };
#endif

const ClassInfo JSHTMLBaseFontElementPrototype::s_info = { "HTMLBaseFontElementPrototype", 0, &JSHTMLBaseFontElementPrototypeTable, 0 };

JSObject* JSHTMLBaseFontElementPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSHTMLBaseFontElement>(exec, globalObject);
}

const ClassInfo JSHTMLBaseFontElement::s_info = { "HTMLBaseFontElement", &JSHTMLElement::s_info, &JSHTMLBaseFontElementTable, 0 };

JSHTMLBaseFontElement::JSHTMLBaseFontElement(PassRefPtr<Structure> structure, PassRefPtr<HTMLBaseFontElement> impl)
    : JSHTMLElement(structure, impl)
{
}

JSObject* JSHTMLBaseFontElement::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSHTMLBaseFontElementPrototype(JSHTMLBaseFontElementPrototype::createStructure(JSHTMLElementPrototype::self(exec, globalObject)));
}

bool JSHTMLBaseFontElement::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSHTMLBaseFontElement, Base>(exec, &JSHTMLBaseFontElementTable, this, propertyName, slot);
}

JSValue jsHTMLBaseFontElementColor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLBaseFontElement* imp = static_cast<HTMLBaseFontElement*>(static_cast<JSHTMLBaseFontElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->color());
}

JSValue jsHTMLBaseFontElementFace(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLBaseFontElement* imp = static_cast<HTMLBaseFontElement*>(static_cast<JSHTMLBaseFontElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->face());
}

JSValue jsHTMLBaseFontElementSize(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLBaseFontElement* imp = static_cast<HTMLBaseFontElement*>(static_cast<JSHTMLBaseFontElement*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->size());
}

JSValue jsHTMLBaseFontElementConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    return static_cast<JSHTMLBaseFontElement*>(asObject(slot.slotBase()))->getConstructor(exec);
}
void JSHTMLBaseFontElement::put(ExecState* exec, const Identifier& propertyName, JSValue value, PutPropertySlot& slot)
{
    lookupPut<JSHTMLBaseFontElement, Base>(exec, propertyName, value, &JSHTMLBaseFontElementTable, this, slot);
}

void setJSHTMLBaseFontElementColor(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLBaseFontElement* imp = static_cast<HTMLBaseFontElement*>(static_cast<JSHTMLBaseFontElement*>(thisObject)->impl());
    imp->setColor(valueToStringWithNullCheck(exec, value));
}

void setJSHTMLBaseFontElementFace(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLBaseFontElement* imp = static_cast<HTMLBaseFontElement*>(static_cast<JSHTMLBaseFontElement*>(thisObject)->impl());
    imp->setFace(valueToStringWithNullCheck(exec, value));
}

void setJSHTMLBaseFontElementSize(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLBaseFontElement* imp = static_cast<HTMLBaseFontElement*>(static_cast<JSHTMLBaseFontElement*>(thisObject)->impl());
    imp->setSize(value.toInt32(exec));
}

JSValue JSHTMLBaseFontElement::getConstructor(ExecState* exec)
{
    return getDOMConstructor<JSHTMLBaseFontElementConstructor>(exec);
}


}
