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


#if ENABLE(VIDEO)

#include "JSHTMLAudioElement.h"

#include <wtf/GetPtr.h>

#include "HTMLAudioElement.h"

#include <runtime/JSNumberCell.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSHTMLAudioElement);

/* Hash table */

static const HashTableValue JSHTMLAudioElementTableValues[2] =
{
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsHTMLAudioElementConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLAudioElementTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSHTMLAudioElementTableValues, 0 };
#else
    { 2, 1, JSHTMLAudioElementTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSHTMLAudioElementConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLAudioElementConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSHTMLAudioElementConstructorTableValues, 0 };
#else
    { 1, 0, JSHTMLAudioElementConstructorTableValues, 0 };
#endif

class JSHTMLAudioElementConstructor : public DOMObject {
public:
    JSHTMLAudioElementConstructor(ExecState* exec)
        : DOMObject(JSHTMLAudioElementConstructor::createStructure(exec->lexicalGlobalObject()->objectPrototype()))
    {
        putDirect(exec->propertyNames().prototype, JSHTMLAudioElementPrototype::self(exec, exec->lexicalGlobalObject()), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValue proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, ImplementsHasInstance)); 
    }
};

const ClassInfo JSHTMLAudioElementConstructor::s_info = { "HTMLAudioElementConstructor", 0, &JSHTMLAudioElementConstructorTable, 0 };

bool JSHTMLAudioElementConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSHTMLAudioElementConstructor, DOMObject>(exec, &JSHTMLAudioElementConstructorTable, this, propertyName, slot);
}

/* Hash table for prototype */

static const HashTableValue JSHTMLAudioElementPrototypeTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLAudioElementPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSHTMLAudioElementPrototypeTableValues, 0 };
#else
    { 1, 0, JSHTMLAudioElementPrototypeTableValues, 0 };
#endif

const ClassInfo JSHTMLAudioElementPrototype::s_info = { "HTMLAudioElementPrototype", 0, &JSHTMLAudioElementPrototypeTable, 0 };

JSObject* JSHTMLAudioElementPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSHTMLAudioElement>(exec, globalObject);
}

const ClassInfo JSHTMLAudioElement::s_info = { "HTMLAudioElement", &JSHTMLMediaElement::s_info, &JSHTMLAudioElementTable, 0 };

JSHTMLAudioElement::JSHTMLAudioElement(PassRefPtr<Structure> structure, PassRefPtr<HTMLAudioElement> impl)
    : JSHTMLMediaElement(structure, impl)
{
}

JSObject* JSHTMLAudioElement::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSHTMLAudioElementPrototype(JSHTMLAudioElementPrototype::createStructure(JSHTMLMediaElementPrototype::self(exec, globalObject)));
}

bool JSHTMLAudioElement::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSHTMLAudioElement, Base>(exec, &JSHTMLAudioElementTable, this, propertyName, slot);
}

JSValue jsHTMLAudioElementConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    return static_cast<JSHTMLAudioElement*>(asObject(slot.slotBase()))->getConstructor(exec);
}
JSValue JSHTMLAudioElement::getConstructor(ExecState* exec)
{
    return getDOMConstructor<JSHTMLAudioElementConstructor>(exec);
}


}

#endif // ENABLE(VIDEO)
