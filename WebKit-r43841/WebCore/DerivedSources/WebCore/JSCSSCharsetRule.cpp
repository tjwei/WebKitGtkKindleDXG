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

#include "JSCSSCharsetRule.h"

#include <wtf/GetPtr.h>

#include "CSSCharsetRule.h"
#include "KURL.h"

#include <runtime/JSNumberCell.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSCSSCharsetRule);

/* Hash table */

static const HashTableValue JSCSSCharsetRuleTableValues[3] =
{
    { "encoding", DontDelete, (intptr_t)jsCSSCharsetRuleEncoding, (intptr_t)setJSCSSCharsetRuleEncoding },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsCSSCharsetRuleConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSCSSCharsetRuleTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 3, JSCSSCharsetRuleTableValues, 0 };
#else
    { 4, 3, JSCSSCharsetRuleTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSCSSCharsetRuleConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSCSSCharsetRuleConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSCSSCharsetRuleConstructorTableValues, 0 };
#else
    { 1, 0, JSCSSCharsetRuleConstructorTableValues, 0 };
#endif

class JSCSSCharsetRuleConstructor : public DOMObject {
public:
    JSCSSCharsetRuleConstructor(ExecState* exec)
        : DOMObject(JSCSSCharsetRuleConstructor::createStructure(exec->lexicalGlobalObject()->objectPrototype()))
    {
        putDirect(exec->propertyNames().prototype, JSCSSCharsetRulePrototype::self(exec, exec->lexicalGlobalObject()), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValue proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, ImplementsHasInstance)); 
    }
};

const ClassInfo JSCSSCharsetRuleConstructor::s_info = { "CSSCharsetRuleConstructor", 0, &JSCSSCharsetRuleConstructorTable, 0 };

bool JSCSSCharsetRuleConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSCSSCharsetRuleConstructor, DOMObject>(exec, &JSCSSCharsetRuleConstructorTable, this, propertyName, slot);
}

/* Hash table for prototype */

static const HashTableValue JSCSSCharsetRulePrototypeTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSCSSCharsetRulePrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSCSSCharsetRulePrototypeTableValues, 0 };
#else
    { 1, 0, JSCSSCharsetRulePrototypeTableValues, 0 };
#endif

const ClassInfo JSCSSCharsetRulePrototype::s_info = { "CSSCharsetRulePrototype", 0, &JSCSSCharsetRulePrototypeTable, 0 };

JSObject* JSCSSCharsetRulePrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSCSSCharsetRule>(exec, globalObject);
}

const ClassInfo JSCSSCharsetRule::s_info = { "CSSCharsetRule", &JSCSSRule::s_info, &JSCSSCharsetRuleTable, 0 };

JSCSSCharsetRule::JSCSSCharsetRule(PassRefPtr<Structure> structure, PassRefPtr<CSSCharsetRule> impl)
    : JSCSSRule(structure, impl)
{
}

JSObject* JSCSSCharsetRule::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSCSSCharsetRulePrototype(JSCSSCharsetRulePrototype::createStructure(JSCSSRulePrototype::self(exec, globalObject)));
}

bool JSCSSCharsetRule::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSCSSCharsetRule, Base>(exec, &JSCSSCharsetRuleTable, this, propertyName, slot);
}

JSValue jsCSSCharsetRuleEncoding(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    CSSCharsetRule* imp = static_cast<CSSCharsetRule*>(static_cast<JSCSSCharsetRule*>(asObject(slot.slotBase()))->impl());
    return jsStringOrNull(exec, imp->encoding());
}

JSValue jsCSSCharsetRuleConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    return static_cast<JSCSSCharsetRule*>(asObject(slot.slotBase()))->getConstructor(exec);
}
void JSCSSCharsetRule::put(ExecState* exec, const Identifier& propertyName, JSValue value, PutPropertySlot& slot)
{
    lookupPut<JSCSSCharsetRule, Base>(exec, propertyName, value, &JSCSSCharsetRuleTable, this, slot);
}

void setJSCSSCharsetRuleEncoding(ExecState* exec, JSObject* thisObject, JSValue value)
{
    CSSCharsetRule* imp = static_cast<CSSCharsetRule*>(static_cast<JSCSSCharsetRule*>(thisObject)->impl());
    ExceptionCode ec = 0;
    imp->setEncoding(valueToStringWithNullCheck(exec, value), ec);
    setDOMException(exec, ec);
}

JSValue JSCSSCharsetRule::getConstructor(ExecState* exec)
{
    return getDOMConstructor<JSCSSCharsetRuleConstructor>(exec);
}


}
