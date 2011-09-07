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

#include "JSHTMLImageElement.h"

#include <wtf/GetPtr.h>

#include "HTMLImageElement.h"
#include "KURL.h"

#include <runtime/JSNumberCell.h>
#include <runtime/JSString.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSHTMLImageElement);

/* Hash table */

static const HashTableValue JSHTMLImageElementTableValues[20] =
{
    { "name", DontDelete, (intptr_t)jsHTMLImageElementName, (intptr_t)setJSHTMLImageElementName },
    { "align", DontDelete, (intptr_t)jsHTMLImageElementAlign, (intptr_t)setJSHTMLImageElementAlign },
    { "alt", DontDelete, (intptr_t)jsHTMLImageElementAlt, (intptr_t)setJSHTMLImageElementAlt },
    { "border", DontDelete, (intptr_t)jsHTMLImageElementBorder, (intptr_t)setJSHTMLImageElementBorder },
    { "height", DontDelete, (intptr_t)jsHTMLImageElementHeight, (intptr_t)setJSHTMLImageElementHeight },
    { "hspace", DontDelete, (intptr_t)jsHTMLImageElementHspace, (intptr_t)setJSHTMLImageElementHspace },
    { "isMap", DontDelete, (intptr_t)jsHTMLImageElementIsMap, (intptr_t)setJSHTMLImageElementIsMap },
    { "longDesc", DontDelete, (intptr_t)jsHTMLImageElementLongDesc, (intptr_t)setJSHTMLImageElementLongDesc },
    { "src", DontDelete, (intptr_t)jsHTMLImageElementSrc, (intptr_t)setJSHTMLImageElementSrc },
    { "useMap", DontDelete, (intptr_t)jsHTMLImageElementUseMap, (intptr_t)setJSHTMLImageElementUseMap },
    { "vspace", DontDelete, (intptr_t)jsHTMLImageElementVspace, (intptr_t)setJSHTMLImageElementVspace },
    { "width", DontDelete, (intptr_t)jsHTMLImageElementWidth, (intptr_t)setJSHTMLImageElementWidth },
    { "complete", DontDelete|ReadOnly, (intptr_t)jsHTMLImageElementComplete, (intptr_t)0 },
    { "lowsrc", DontDelete, (intptr_t)jsHTMLImageElementLowsrc, (intptr_t)setJSHTMLImageElementLowsrc },
    { "naturalHeight", DontDelete|ReadOnly, (intptr_t)jsHTMLImageElementNaturalHeight, (intptr_t)0 },
    { "naturalWidth", DontDelete|ReadOnly, (intptr_t)jsHTMLImageElementNaturalWidth, (intptr_t)0 },
    { "x", DontDelete|ReadOnly, (intptr_t)jsHTMLImageElementX, (intptr_t)0 },
    { "y", DontDelete|ReadOnly, (intptr_t)jsHTMLImageElementY, (intptr_t)0 },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsHTMLImageElementConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLImageElementTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 16383, JSHTMLImageElementTableValues, 0 };
#else
    { 67, 63, JSHTMLImageElementTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSHTMLImageElementConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLImageElementConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSHTMLImageElementConstructorTableValues, 0 };
#else
    { 1, 0, JSHTMLImageElementConstructorTableValues, 0 };
#endif

class JSHTMLImageElementConstructor : public DOMObject {
public:
    JSHTMLImageElementConstructor(ExecState* exec)
        : DOMObject(JSHTMLImageElementConstructor::createStructure(exec->lexicalGlobalObject()->objectPrototype()))
    {
        putDirect(exec->propertyNames().prototype, JSHTMLImageElementPrototype::self(exec, exec->lexicalGlobalObject()), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValue proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, ImplementsHasInstance)); 
    }
};

const ClassInfo JSHTMLImageElementConstructor::s_info = { "HTMLImageElementConstructor", 0, &JSHTMLImageElementConstructorTable, 0 };

bool JSHTMLImageElementConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSHTMLImageElementConstructor, DOMObject>(exec, &JSHTMLImageElementConstructorTable, this, propertyName, slot);
}

/* Hash table for prototype */

static const HashTableValue JSHTMLImageElementPrototypeTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLImageElementPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSHTMLImageElementPrototypeTableValues, 0 };
#else
    { 1, 0, JSHTMLImageElementPrototypeTableValues, 0 };
#endif

const ClassInfo JSHTMLImageElementPrototype::s_info = { "HTMLImageElementPrototype", 0, &JSHTMLImageElementPrototypeTable, 0 };

JSObject* JSHTMLImageElementPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSHTMLImageElement>(exec, globalObject);
}

const ClassInfo JSHTMLImageElement::s_info = { "HTMLImageElement", &JSHTMLElement::s_info, &JSHTMLImageElementTable, 0 };

JSHTMLImageElement::JSHTMLImageElement(PassRefPtr<Structure> structure, PassRefPtr<HTMLImageElement> impl)
    : JSHTMLElement(structure, impl)
{
}

JSObject* JSHTMLImageElement::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSHTMLImageElementPrototype(JSHTMLImageElementPrototype::createStructure(JSHTMLElementPrototype::self(exec, globalObject)));
}

bool JSHTMLImageElement::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSHTMLImageElement, Base>(exec, &JSHTMLImageElementTable, this, propertyName, slot);
}

JSValue jsHTMLImageElementName(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLImageElement* imp = static_cast<HTMLImageElement*>(static_cast<JSHTMLImageElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->name());
}

JSValue jsHTMLImageElementAlign(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLImageElement* imp = static_cast<HTMLImageElement*>(static_cast<JSHTMLImageElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->align());
}

JSValue jsHTMLImageElementAlt(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLImageElement* imp = static_cast<HTMLImageElement*>(static_cast<JSHTMLImageElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->alt());
}

JSValue jsHTMLImageElementBorder(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLImageElement* imp = static_cast<HTMLImageElement*>(static_cast<JSHTMLImageElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->border());
}

JSValue jsHTMLImageElementHeight(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLImageElement* imp = static_cast<HTMLImageElement*>(static_cast<JSHTMLImageElement*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->height());
}

JSValue jsHTMLImageElementHspace(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLImageElement* imp = static_cast<HTMLImageElement*>(static_cast<JSHTMLImageElement*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->hspace());
}

JSValue jsHTMLImageElementIsMap(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLImageElement* imp = static_cast<HTMLImageElement*>(static_cast<JSHTMLImageElement*>(asObject(slot.slotBase()))->impl());
    return jsBoolean(imp->isMap());
}

JSValue jsHTMLImageElementLongDesc(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLImageElement* imp = static_cast<HTMLImageElement*>(static_cast<JSHTMLImageElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->longDesc());
}

JSValue jsHTMLImageElementSrc(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLImageElement* imp = static_cast<HTMLImageElement*>(static_cast<JSHTMLImageElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->src());
}

JSValue jsHTMLImageElementUseMap(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLImageElement* imp = static_cast<HTMLImageElement*>(static_cast<JSHTMLImageElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->useMap());
}

JSValue jsHTMLImageElementVspace(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLImageElement* imp = static_cast<HTMLImageElement*>(static_cast<JSHTMLImageElement*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->vspace());
}

JSValue jsHTMLImageElementWidth(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLImageElement* imp = static_cast<HTMLImageElement*>(static_cast<JSHTMLImageElement*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->width());
}

JSValue jsHTMLImageElementComplete(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLImageElement* imp = static_cast<HTMLImageElement*>(static_cast<JSHTMLImageElement*>(asObject(slot.slotBase()))->impl());
    return jsBoolean(imp->complete());
}

JSValue jsHTMLImageElementLowsrc(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLImageElement* imp = static_cast<HTMLImageElement*>(static_cast<JSHTMLImageElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->lowsrc());
}

JSValue jsHTMLImageElementNaturalHeight(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLImageElement* imp = static_cast<HTMLImageElement*>(static_cast<JSHTMLImageElement*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->naturalHeight());
}

JSValue jsHTMLImageElementNaturalWidth(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLImageElement* imp = static_cast<HTMLImageElement*>(static_cast<JSHTMLImageElement*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->naturalWidth());
}

JSValue jsHTMLImageElementX(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLImageElement* imp = static_cast<HTMLImageElement*>(static_cast<JSHTMLImageElement*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->x());
}

JSValue jsHTMLImageElementY(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLImageElement* imp = static_cast<HTMLImageElement*>(static_cast<JSHTMLImageElement*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->y());
}

JSValue jsHTMLImageElementConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    return static_cast<JSHTMLImageElement*>(asObject(slot.slotBase()))->getConstructor(exec);
}
void JSHTMLImageElement::put(ExecState* exec, const Identifier& propertyName, JSValue value, PutPropertySlot& slot)
{
    lookupPut<JSHTMLImageElement, Base>(exec, propertyName, value, &JSHTMLImageElementTable, this, slot);
}

void setJSHTMLImageElementName(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLImageElement* imp = static_cast<HTMLImageElement*>(static_cast<JSHTMLImageElement*>(thisObject)->impl());
    imp->setName(valueToStringWithNullCheck(exec, value));
}

void setJSHTMLImageElementAlign(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLImageElement* imp = static_cast<HTMLImageElement*>(static_cast<JSHTMLImageElement*>(thisObject)->impl());
    imp->setAlign(valueToStringWithNullCheck(exec, value));
}

void setJSHTMLImageElementAlt(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLImageElement* imp = static_cast<HTMLImageElement*>(static_cast<JSHTMLImageElement*>(thisObject)->impl());
    imp->setAlt(valueToStringWithNullCheck(exec, value));
}

void setJSHTMLImageElementBorder(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLImageElement* imp = static_cast<HTMLImageElement*>(static_cast<JSHTMLImageElement*>(thisObject)->impl());
    imp->setBorder(valueToStringWithNullCheck(exec, value));
}

void setJSHTMLImageElementHeight(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLImageElement* imp = static_cast<HTMLImageElement*>(static_cast<JSHTMLImageElement*>(thisObject)->impl());
    imp->setHeight(value.toInt32(exec));
}

void setJSHTMLImageElementHspace(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLImageElement* imp = static_cast<HTMLImageElement*>(static_cast<JSHTMLImageElement*>(thisObject)->impl());
    imp->setHspace(value.toInt32(exec));
}

void setJSHTMLImageElementIsMap(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLImageElement* imp = static_cast<HTMLImageElement*>(static_cast<JSHTMLImageElement*>(thisObject)->impl());
    imp->setIsMap(value.toBoolean(exec));
}

void setJSHTMLImageElementLongDesc(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLImageElement* imp = static_cast<HTMLImageElement*>(static_cast<JSHTMLImageElement*>(thisObject)->impl());
    imp->setLongDesc(valueToStringWithNullCheck(exec, value));
}

void setJSHTMLImageElementSrc(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLImageElement* imp = static_cast<HTMLImageElement*>(static_cast<JSHTMLImageElement*>(thisObject)->impl());
    imp->setSrc(valueToStringWithNullCheck(exec, value));
}

void setJSHTMLImageElementUseMap(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLImageElement* imp = static_cast<HTMLImageElement*>(static_cast<JSHTMLImageElement*>(thisObject)->impl());
    imp->setUseMap(valueToStringWithNullCheck(exec, value));
}

void setJSHTMLImageElementVspace(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLImageElement* imp = static_cast<HTMLImageElement*>(static_cast<JSHTMLImageElement*>(thisObject)->impl());
    imp->setVspace(value.toInt32(exec));
}

void setJSHTMLImageElementWidth(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLImageElement* imp = static_cast<HTMLImageElement*>(static_cast<JSHTMLImageElement*>(thisObject)->impl());
    imp->setWidth(value.toInt32(exec));
}

void setJSHTMLImageElementLowsrc(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLImageElement* imp = static_cast<HTMLImageElement*>(static_cast<JSHTMLImageElement*>(thisObject)->impl());
    imp->setLowsrc(valueToStringWithNullCheck(exec, value));
}

JSValue JSHTMLImageElement::getConstructor(ExecState* exec)
{
    return getDOMConstructor<JSHTMLImageElementConstructor>(exec);
}


}
