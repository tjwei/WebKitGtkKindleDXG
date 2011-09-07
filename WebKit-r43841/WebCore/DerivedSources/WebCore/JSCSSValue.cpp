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

#include "JSCSSValue.h"

#include <wtf/GetPtr.h>

#include "CSSValue.h"
#include "KURL.h"

#include <runtime/JSNumberCell.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSCSSValue);

/* Hash table */

static const HashTableValue JSCSSValueTableValues[4] =
{
    { "cssText", DontDelete, (intptr_t)jsCSSValueCssText, (intptr_t)setJSCSSValueCssText },
    { "cssValueType", DontDelete|ReadOnly, (intptr_t)jsCSSValueCssValueType, (intptr_t)0 },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsCSSValueConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSCSSValueTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 7, JSCSSValueTableValues, 0 };
#else
    { 8, 7, JSCSSValueTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSCSSValueConstructorTableValues[5] =
{
    { "CSS_INHERIT", DontDelete|ReadOnly, (intptr_t)jsCSSValueCSS_INHERIT, (intptr_t)0 },
    { "CSS_PRIMITIVE_VALUE", DontDelete|ReadOnly, (intptr_t)jsCSSValueCSS_PRIMITIVE_VALUE, (intptr_t)0 },
    { "CSS_VALUE_LIST", DontDelete|ReadOnly, (intptr_t)jsCSSValueCSS_VALUE_LIST, (intptr_t)0 },
    { "CSS_CUSTOM", DontDelete|ReadOnly, (intptr_t)jsCSSValueCSS_CUSTOM, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSCSSValueConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 7, JSCSSValueConstructorTableValues, 0 };
#else
    { 8, 7, JSCSSValueConstructorTableValues, 0 };
#endif

class JSCSSValueConstructor : public DOMObject {
public:
    JSCSSValueConstructor(ExecState* exec)
        : DOMObject(JSCSSValueConstructor::createStructure(exec->lexicalGlobalObject()->objectPrototype()))
    {
        putDirect(exec->propertyNames().prototype, JSCSSValuePrototype::self(exec, exec->lexicalGlobalObject()), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValue proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, ImplementsHasInstance)); 
    }
};

const ClassInfo JSCSSValueConstructor::s_info = { "CSSValueConstructor", 0, &JSCSSValueConstructorTable, 0 };

bool JSCSSValueConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSCSSValueConstructor, DOMObject>(exec, &JSCSSValueConstructorTable, this, propertyName, slot);
}

/* Hash table for prototype */

static const HashTableValue JSCSSValuePrototypeTableValues[5] =
{
    { "CSS_INHERIT", DontDelete|ReadOnly, (intptr_t)jsCSSValueCSS_INHERIT, (intptr_t)0 },
    { "CSS_PRIMITIVE_VALUE", DontDelete|ReadOnly, (intptr_t)jsCSSValueCSS_PRIMITIVE_VALUE, (intptr_t)0 },
    { "CSS_VALUE_LIST", DontDelete|ReadOnly, (intptr_t)jsCSSValueCSS_VALUE_LIST, (intptr_t)0 },
    { "CSS_CUSTOM", DontDelete|ReadOnly, (intptr_t)jsCSSValueCSS_CUSTOM, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSCSSValuePrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 7, JSCSSValuePrototypeTableValues, 0 };
#else
    { 8, 7, JSCSSValuePrototypeTableValues, 0 };
#endif

const ClassInfo JSCSSValuePrototype::s_info = { "CSSValuePrototype", 0, &JSCSSValuePrototypeTable, 0 };

JSObject* JSCSSValuePrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSCSSValue>(exec, globalObject);
}

bool JSCSSValuePrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSCSSValuePrototype, JSObject>(exec, &JSCSSValuePrototypeTable, this, propertyName, slot);
}

const ClassInfo JSCSSValue::s_info = { "CSSValue", 0, &JSCSSValueTable, 0 };

JSCSSValue::JSCSSValue(PassRefPtr<Structure> structure, PassRefPtr<CSSValue> impl)
    : DOMObject(structure)
    , m_impl(impl)
{
}

JSCSSValue::~JSCSSValue()
{
    forgetDOMObject(*Heap::heap(this)->globalData(), m_impl.get());
}

JSObject* JSCSSValue::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSCSSValuePrototype(JSCSSValuePrototype::createStructure(globalObject->objectPrototype()));
}

bool JSCSSValue::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSCSSValue, Base>(exec, &JSCSSValueTable, this, propertyName, slot);
}

JSValue jsCSSValueCssText(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    CSSValue* imp = static_cast<CSSValue*>(static_cast<JSCSSValue*>(asObject(slot.slotBase()))->impl());
    return jsStringOrNull(exec, imp->cssText());
}

JSValue jsCSSValueCssValueType(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    CSSValue* imp = static_cast<CSSValue*>(static_cast<JSCSSValue*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->cssValueType());
}

JSValue jsCSSValueConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    return static_cast<JSCSSValue*>(asObject(slot.slotBase()))->getConstructor(exec);
}
void JSCSSValue::put(ExecState* exec, const Identifier& propertyName, JSValue value, PutPropertySlot& slot)
{
    lookupPut<JSCSSValue, Base>(exec, propertyName, value, &JSCSSValueTable, this, slot);
}

void setJSCSSValueCssText(ExecState* exec, JSObject* thisObject, JSValue value)
{
    CSSValue* imp = static_cast<CSSValue*>(static_cast<JSCSSValue*>(thisObject)->impl());
    ExceptionCode ec = 0;
    imp->setCssText(valueToStringWithNullCheck(exec, value), ec);
    setDOMException(exec, ec);
}

JSValue JSCSSValue::getConstructor(ExecState* exec)
{
    return getDOMConstructor<JSCSSValueConstructor>(exec);
}

// Constant getters

JSValue jsCSSValueCSS_INHERIT(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(0));
}

JSValue jsCSSValueCSS_PRIMITIVE_VALUE(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(1));
}

JSValue jsCSSValueCSS_VALUE_LIST(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(2));
}

JSValue jsCSSValueCSS_CUSTOM(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(3));
}

CSSValue* toCSSValue(JSC::JSValue value)
{
    return value.isObject(&JSCSSValue::s_info) ? static_cast<JSCSSValue*>(asObject(value))->impl() : 0;
}

}
